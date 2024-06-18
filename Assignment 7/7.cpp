#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>

class Buffer {
    std::vector<int> buffer;
    std::size_t capacity;
    std::mutex mtx;
    std::condition_variable not_empty;
    std::condition_variable not_full;

public:
    Buffer(std::size_t size) : capacity(size) {
        buffer.reserve(size);
    }

    void produce(int item) {
        std::unique_lock<std::mutex> lock(mtx);
        not_full.wait(lock, [this](){ return buffer.size() != capacity; });
        buffer.push_back(item);
        not_empty.notify_one();
    }

    int consume() {
        std::unique_lock<std::mutex> lock(mtx);
        not_empty.wait(lock, [this](){ return !buffer.empty(); });
        int item = buffer.front();
        buffer.erase(buffer.begin());
        not_full.notify_one();
        return item;
    }
};

int main(int argc, char* argv[]) {
    int num_producers = std::stoi(argv[1]);
    int num_consumers = std::stoi(argv[2]);
    std::size_t buffer_size = std::stoi(argv[3]);

    Buffer buffer(buffer_size);

    std::vector<std::thread> producers;
    for (int i = 0; i < num_producers; ++i) {
        producers.push_back(std::thread([&buffer, i](){
            for (int j = 0; j < 10; ++j) {
                buffer.produce(i * 10 + j);
            }
        }));
    }

    std::vector<std::thread> consumers;
    for (int i = 0; i < num_consumers; ++i) {
        consumers.push_back(std::thread([&buffer](){
            for (int j = 0; j < 10; ++j) {
                int item = buffer.consume();
                std::cout << "Consumed: " << item << std::endl;
            }
        }));
    }

    for (auto& t : producers) {
        t.join();
    }

    for (auto& t : consumers) {
        t.join();
    }

    return 0;
}

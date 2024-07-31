#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <chrono>

std::queue<int> buffer;
std::mutex mtx;
std::condition_variable cv;
std::mutex counter_mtx;
int total_produced = 0;
int total_consumed = 0;
int active_producers = 0;
bool all_producers_done = false;

void produce(int id, int num_producers) {
    for (int i = 0; i < 10; ++i) {
        {
            std::unique_lock<std::mutex> lock(mtx);
            buffer.push(i);
            std::cout << "Producer " << id << " produced " << i << "\n";
        }
        cv.notify_one(); // Notify one waiting consumer
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        {
            std::unique_lock<std::mutex> counter_lock(counter_mtx);
            total_produced++;
        }
    }

    {
        std::unique_lock<std::mutex> lock(mtx);
        active_producers--;
        if (active_producers == 0) {
            all_producers_done = true;
            cv.notify_all(); // Notify all consumers if all producers are done
        }
    }
}

void consume(int id) {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, []{ return !buffer.empty() || all_producers_done; });

        if (buffer.empty() && all_producers_done) {
            break;
        }

        int widget = buffer.front();
        buffer.pop();
        std::cout << "Consumer " << id << " consumed " << widget << "\n";

        lock.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        std::unique_lock<std::mutex> counter_lock(counter_mtx);
        total_consumed++;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <num_producers> <num_consumers>\n";
        return 1;
    }

    int num_producers = std::stoi(argv[1]);
    int num_consumers = std::stoi(argv[2]);
    active_producers = num_producers;

    std::vector<std::thread> producers;
    for (int i = 0; i < num_producers; ++i) {
        producers.emplace_back(produce, i, num_producers);
    }

    std::vector<std::thread> consumers;
    for (int i = 0; i < num_consumers; ++i) {
        consumers.emplace_back(consume, i);
    }

    for (auto& thread : producers) {
        thread.join();
    }

    for (auto& thread : consumers) {
        thread.join();
    }

    std::cout << "Total produced: " << total_produced << "\n";
    std::cout << "Total consumed: " << total_consumed << "\n";

    return 0;
}

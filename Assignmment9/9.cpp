#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
int reindeer = 0, elves = 0;
bool santaClause = false;

void Santa() {
    std::unique_lock<std::mutex> lck(mtx);
    while (true) {
        cv.wait(lck, [] { return reindeer == 9 || elves == 3; });
        if (reindeer == 9) {
            std::cout << "Santa Clause is helping the reindeers\n";
            reindeer = 0;
            santaClause = true;
        } else if (elves == 3 && reindeer < 9) {
            std::cout << "Santa Clause is helping the elves\n";
            elves = 0;
            santaClause = true;
        }
        cv.notify_all();
    }
}
void Reindeer() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::unique_lock<std::mutex> lck(mtx);
        reindeer++;
        if (reindeer == 9) {
            cv.notify_all();
        }
        cv.wait(lck, []{return santaClause;});
        santaClause = false;
    }
}

void Elf() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::unique_lock<std::mutex> lck(mtx);
        elves++;
        if (elves == 3) {
            cv.notify_all();
        }
        cv.wait(lck, []{return santaClause;});
        santaClause = false;
    }
}

int main() {
    std::thread santa(Santa);
    std::thread reindeers[9];
    for (int i = 0; i < 9; ++i) {
        reindeers[i] = std::thread(Reindeer);
    }
    std::thread elves[10]; // You can adjust the number of elves
    for (int i = 0; i < 10; ++i) {
        elves[i] = std::thread(Elf);
    }
    santa.join();
    for (int i = 0; i < 9; ++i) {
        reindeers[i].join();
    }
    for (int i = 0; i < 10; ++i) {
        elves[i].join();
    }
    return 0;
}

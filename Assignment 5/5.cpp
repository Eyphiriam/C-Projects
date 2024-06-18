#include <iostream>
#include <fstream>
#include <pthread.h>
#include <vector>

std::vector<int> numbers;
std::vector<int> results;
int num_threads;

void* sum(void* arg) {
    long index = (long)arg;
    int start = index * (numbers.size() / num_threads);
    int end = (index + 1) * (numbers.size() / num_threads);
    if (index == num_threads - 1) {
        end = numbers.size();
    }
    for (int i = start; i < end; i++) {
        results[index] += numbers[i];
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Usage: " << argv[0] << " <num_threads> <filename>" << std::endl;
        return 1;
    }

    num_threads = std::stoi(argv[1]);
    std::string filename = argv[2];

    std::ifstream file(filename);
    if (!file) {
        std::cout << "Could not open file " << filename << std::endl;
        return 1;
    }

    int num_numbers;
    file >> num_numbers;
    numbers.resize(num_numbers);
    for (int i = 0; i < num_numbers; i++) {
        file >> numbers[i];
    }

    results.resize(num_threads);
    std::vector<pthread_t> threads(num_threads);
    for (long i = 0; i < num_threads; i++) {
        pthread_create(&threads[i], NULL, sum, (void*)i);
    }

    int total = 0;
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
        total += results[i];
    }

    std::cout << "Total: " << total << std::endl;

    std::ofstream output("output.txt");
    output << "Total: " << total << std::endl;

    return 0;
}


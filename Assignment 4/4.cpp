#include <iostream>
#include <pthread.h>

pthread_mutex_t lock;

void* count(void* arg) {
    for (int i = 0; i <= 10; i++) {
        pthread_mutex_lock(&lock);
        std::cout << "Thread " << pthread_self() << ": " << i << std::endl;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    if (pthread_mutex_init(&lock, NULL) != 0) {
        std::cout << "Failed to initialize mutex" << std::endl;
        return 1;
    }

    pthread_create(&thread1, NULL, count, NULL);
    pthread_create(&thread2, NULL, count, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    pthread_mutex_destroy(&lock);

    return 0;
}

#include <pthread.h>
#include <unistd.h>
#include <iostream>

#define N 5
#define THINKING 2
#define HUNGRY 1
#define EATING 0
#define LEFT (phnum + 4) % N
#define RIGHT (phnum + 1) % N
#define MAX_EAT_TIMES 5

int state[N];
int phil[N] = { 0, 1, 2, 3, 4 };
int eat_counter[N] = {0, 0, 0, 0, 0};

pthread_mutex_t mutex;
pthread_cond_t condition[N];

void test(int phnum) {
    if (state[phnum] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) {
        state[phnum] = EATING;
        sleep(2);
        std::cout << "Philosopher " << phnum + 1 << " takes fork " << LEFT + 1 << " and " << phnum + 1 << std::endl;
        std::cout << "Philosopher " << phnum + 1 << " is Eating\n";
        eat_counter[phnum]++;
        pthread_cond_signal(&condition[phnum]);
    }
}

void take_fork(int phnum) {
    pthread_mutex_lock(&mutex);
    state[phnum] = HUNGRY;
    std::cout << "Philosopher " << phnum + 1 << " is Hungry\n";
    test(phnum);
    if (state[phnum] != EATING)
        pthread_cond_wait(&condition[phnum], &mutex);
    pthread_mutex_unlock(&mutex);
}

void put_fork(int phnum) {
    pthread_mutex_lock(&mutex);
    state[phnum] = THINKING;
    std::cout << "Philosopher " << phnum + 1 << " putting fork " << LEFT + 1 << " and " << phnum + 1 << " down\n";
    std::cout << "Philosopher " << phnum + 1 << " is thinking\n";
    test(LEFT);
    test(RIGHT);
    pthread_mutex_unlock(&mutex);
}

void* philospher(void* num) {
    int* i = (int*)num;
    while (eat_counter[*i] < MAX_EAT_TIMES) {
        sleep(1);
        take_fork(*i);
        sleep(0);
        put_fork(*i);
    }
    return NULL;
}

int main() {
    int i;
    pthread_t thread_id[N];
    pthread_mutex_init(&mutex, NULL);
    for (i = 0; i < N; i++)
        pthread_cond_init(&condition[i], NULL);
    for (i = 0; i < N; i++) {
        pthread_create(&thread_id[i], NULL, philospher, &phil[i]);
        std::cout << "Philosopher " << i + 1 << " is thinking\n";
    }
    for (i = 0; i < N; i++)
        pthread_join(thread_id[i], NULL);
}

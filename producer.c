// producer.c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#define MAX_ITEMS 2
#define BUFFER_SIZE 5

int table[BUFFER_SIZE];
sem_t *empty, *full, *mutex;

void *produce(void *arg) {
    int produced = 0;
    while (1) {
        sleep(rand() % 3); // Simulate production time
        sem_wait(empty);
        sem_wait(mutex);

        // Produce item and add to the table
        table[produced] = 1;
        printf("Produced: Item %d\n", produced);
        produced = (produced + 1) % BUFFER_SIZE;

        sem_post(mutex);
        sem_post(full);
    }
    pthread_exit(0);
}

int main() {
    pthread_t producer_thread;

    // Initialize semaphores
    empty = sem_open("/empty_sem", O_CREAT, 0644, BUFFER_SIZE - MAX_ITEMS);
    full = sem_open("/full_sem", O_CREAT, 0644, 0);
    mutex = sem_open("/mutex_sem", O_CREAT, 0644, 1);

    // Create producer thread
    pthread_create(&producer_thread, NULL, produce, NULL);

    // Wait for the producer thread to finish (Not necessary for an infinite loop)
    pthread_join(producer_thread, NULL);

    // Close and unlink semaphores
    sem_close(empty);
    sem_close(full);
    sem_close(mutex);
    sem_unlink("/empty_sem");
    sem_unlink("/full_sem");
    sem_unlink("/mutex_sem");

    return 0;
}

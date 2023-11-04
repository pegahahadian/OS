// consumer.c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#define BUFFER_SIZE 5

int table[BUFFER_SIZE];
sem_t *empty, *full, *mutex;

void *consume(void *arg) {
    int consumed = 0;
    while (1) {
        sleep(rand() % 3); // Simulate consumption time
        sem_wait(full);
        sem_wait(mutex);

        // Consume item from the table
        table[consumed] = 0;
        printf("Consumed: Item %d\n", consumed);
        consumed = (consumed + 1) % BUFFER_SIZE;

        sem_post(mutex);
        sem_post(empty);
    }
    pthread_exit(0);
}

int main() {
    pthread_t consumer_thread;

    // Initialize semaphores
    empty = sem_open("/empty_sem", O_CREAT, 0644, BUFFER_SIZE);
    full = sem_open("/full_sem", O_CREAT, 0644, 0);
    mutex = sem_open("/mutex_sem", O_CREAT, 0644, 1);

    // Create consumer thread
    pthread_create(&consumer_thread, NULL, consume, NULL);

    // Wait for the consumer thread to finish (Not necessary for an infinite loop)
    pthread_join(consumer_thread, NULL);

    // Close and unlink semaphores
    sem_close(empty);
    sem_close(full);
    sem_close(mutex);
    sem_unlink("/empty_sem");
    sem_unlink("/full_sem");
    sem_unlink("/mutex_sem");

    return 0;
}

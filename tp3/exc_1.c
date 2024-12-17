#include <stdio.h>
#include <pthread.h>

#define NUM_ITERATIONS 2000000

int counter = 0;

void* increment_counter(void* arg) {
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        counter++;
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    // Create two threads
    pthread_create(&thread1, NULL, increment_counter, NULL);
    pthread_create(&thread2, NULL, increment_counter, NULL);

    // Wait for both threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Print the counter value
    printf("Final counter value: %d\n", counter);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <stdbool.h>

#define BUFFER_SIZE 1024

char buffer[BUFFER_SIZE];
pthread_mutex_t lock1, lock2;
bool done = false;

void* read_file(void* arg) {
    FILE *file = fopen("textfile.txt", "r");
    if (file == NULL) {
        perror("Failed to open file");
        return NULL;
    }

    while (fscanf(file, "%s", buffer) != EOF) {
        pthread_mutex_lock(&lock1);
        pthread_mutex_unlock(&lock2);
    }

    fclose(file);
    done = true;
    pthread_mutex_unlock(&lock2);
    return NULL;
}

void* print_buffer(void* arg) {
    while (1) {
        pthread_mutex_lock(&lock2);
        if (done && strlen(buffer) == 0) {
            pthread_mutex_unlock(&lock2);
            break;
        }
        printf("%s\n", buffer);
        buffer[0] = '\0'; // Clear the buffer
        pthread_mutex_unlock(&lock1);
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    pthread_mutex_init(&lock1, NULL);
    pthread_mutex_init(&lock2, NULL);

    pthread_mutex_lock(&lock1);

    pthread_create(&thread1, NULL, read_file, NULL);
    pthread_create(&thread2, NULL, print_buffer, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    pthread_mutex_destroy(&lock1);
    pthread_mutex_destroy(&lock2);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

#define BUFFER_SIZE 100

int main() {
    int pipefd[2];
    pid_t pid;
    char buffer[BUFFER_SIZE];

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) { // Parent process
        close(pipefd[0]); // Close unused read end
        printf("Father\n");
        printf("Enter a word: ");
        scanf("%s", buffer);
        write(pipefd[1], buffer, strlen(buffer) + 1);
        close(pipefd[1]); // Close write end after writing
        
    } else { // Child process
        close(pipefd[1]); // Close unused write end
        read(pipefd[0], buffer, BUFFER_SIZE);
        printf("Son received: %s\n", buffer);
        close(pipefd[0]); // Close read end after reading
    }

    return 0;
}
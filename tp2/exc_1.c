#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int counter = 0;

    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process
        printf("Son: PID = %d, Father's PID = %d\n", getpid(), getppid());
        int wait_time;
        printf("Enter a value to make the son wait before ending: ");
        scanf("%d", &wait_time);
        sleep(wait_time);
        printf("Son end\n");
    } else {
        // Parent process
        printf("Father: PID = %d, Son's PID = %d\n", getpid(), pid);
        wait(NULL); // Wait for child process to finish
        for (int i = 0; i < 30; i++) {
            counter++;
            printf("Father counter: %d\n", counter);
            sleep(1);
        }
        printf("Father end\n");
    }

    return 0;
}
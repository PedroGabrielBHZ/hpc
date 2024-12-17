#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

volatile sig_atomic_t stop = 0;

void handle_sigusr1(int sig) {
    stop = 1;
}

int main() {
    pid_t pid;
    int counter = 0;

    // Set up signal handler
    signal(SIGUSR1, handle_sigusr1);

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
        if (wait_time == 0) {
            // Signal the parent to stop immediately
            kill(getppid(), SIGUSR1);
        } else {
            // Kill parent after waiting wait_time
            sleep(wait_time);
            kill(getppid(), SIGUSR1);
        }            
        printf("Son end\n");
    } else {
        // Parent process
        printf("Father: PID = %d, Son's PID = %d\n", getpid(), pid);
        wait(NULL); // Wait for child process to finish
        while (!stop) {
            counter++;
            printf("Father counter: %d\n", counter);
            sleep(1);
        }
        printf("Father end\n");
    }

    return 0;
}
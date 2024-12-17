#include <sys/un.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <sender_socket> <receiver_socket> <message>\n", argv[0]);
        return 1;
    }

    const char *sender_socket = argv[1];
    const char *receiver_socket = argv[2];
    const char *message = argv[3];

    int s1 = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (s1 < 0) {
        perror("socket");
        return 1;
    }

    struct sockaddr_un MyAddr;
    MyAddr.sun_family = AF_UNIX;
    strcpy(MyAddr.sun_path, sender_socket);

    unlink(sender_socket);
    if (bind(s1, (struct sockaddr *)&MyAddr, sizeof(MyAddr)) < 0) {
        perror("bind");
        return 1;
    }

    struct sockaddr_un ReceiverAddr;
    ReceiverAddr.sun_family = AF_UNIX;
    strcpy(ReceiverAddr.sun_path, receiver_socket);

    char buffer[1024];
    snprintf(buffer, sizeof(buffer), "%s PID: %d", message, getpid());

    if (sendto(s1, buffer, strlen(buffer), 0, (struct sockaddr *)&ReceiverAddr, sizeof(ReceiverAddr)) < 0) {
        perror("sendto");
        return 1;
    }

    ssize_t numBytes = recvfrom(s1, buffer, sizeof(buffer) - 1, 0, NULL, NULL);
    if (numBytes < 0) {
        perror("recvfrom");
        return 1;
    }
    buffer[numBytes] = '\0'; // Null-terminate the received data
    printf("Received response: %s\n", buffer);

    close(s1);
    unlink(sender_socket);
    return 0;
}
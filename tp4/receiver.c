#include <sys/un.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <receiver_socket>\n", argv[0]);
        return 1;
    }

    const char *receiver_socket = argv[1];

    int s1 = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (s1 < 0) {
        perror("socket");
        return 1;
    }

    struct sockaddr_un MyAddr;
    MyAddr.sun_family = AF_UNIX;
    strcpy(MyAddr.sun_path, receiver_socket);

    unlink(receiver_socket);
    if (bind(s1, (struct sockaddr *)&MyAddr, sizeof(MyAddr)) < 0) {
        perror("bind");
        return 1;
    }

    char buffer[1024];
    struct sockaddr_un senderAddr;
    socklen_t senderAddrLen = sizeof(senderAddr);
    ssize_t numBytes = recvfrom(s1, buffer, sizeof(buffer) - 1, 0, (struct sockaddr *)&senderAddr, &senderAddrLen);
    if (numBytes < 0) {
        perror("recvfrom");
        return 1;
    }
    buffer[numBytes] = '\0'; // Null-terminate the received data
    printf("Received message: %s\n", buffer);

    snprintf(buffer, sizeof(buffer), "OK PID: %d", getpid());
    if (sendto(s1, buffer, strlen(buffer), 0, (struct sockaddr *)&senderAddr, senderAddrLen) < 0) {
        perror("sendto");
        return 1;
    }

    close(s1);
    unlink(receiver_socket);
    return 0;
}
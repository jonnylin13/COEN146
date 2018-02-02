// Jonny Lin
// Lab 3
// Client

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int socketRef, port, nBytes;
    char buffer[1024];
    struct sockaddr_in serverAddress;
    socklen_t addressSize;

    if (argc != 3) {
        printf("Error: need port number and machine\n");
        return 1;
    }

    // Configure server address
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(atoi(argv[1]));
    inet_pton(AF_INET, argv[2], &serverAddress.sin_addr.s_addr);
    addressSize = sizeof(serverAddress);

    // Create socket
    socketRef = socket(PF_INET, SOCK_DGRAM, 0);

    while (1) {
        // Start communication

        // Create packet
        // Header includes seq_ack, len (of data), and cksum
        // Send initial packet with SEQ
    }

    return 0;
}
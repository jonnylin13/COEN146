// Jonny Lin
// Lab 3
// Server

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int socketRef, nBytes;
    char buffer[1024];
    struct sockaddr_in serverAddress, clientAddress;
    struct socketAddressStorage, serverAddressStorage;
    socklen_t addressSize, clientAddressSize;
    int i;

    if (argc != 2) {
        printf("Error: requires port number\n");
        return 1;
    }

    serverAddress.sin_family = AF_INET; // Family protocol
    serverAddress.sin_port = htons((short) atoi(argv[1])); // Port number from argv
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY); // Accept any interfaces

    // Init memory
    memset ((char *) serverAddress.sin_zero, '\0', sizeof(serverAddress.sin_zero));
    addressSize = sizeof(serverAddressStorage);

    // Create socket
    if ((socketRef = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        printf("Error: socket could not be created\n");
        return 1;
    }

    // Bind socket to address
    if (bind(socketRef, (struct sockaddr*) &serverAddress, sizeof(serverAddress)) != 0) {
        printf("Error: could not bind socket to address\n");
        return 1;
    }

    while (1) {
        // Listening!

        // Recv communication
    }

    return 0;
}
// Jonny Lin
// Lab 3
// Server

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include "useful.h"

int main(int argc, char *argv[]) {
    char buffer[1024];
    int socketRef, nBytes;
    struct sockaddr_in serverAddress, clientAddress;
    struct sockaddr_storage serverAddressStorage;
    socklen_t addressSize, clientAddressSize;
    int cursor = 0;
    int sequence = 0;
    FILE* output;

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

    int fileNameSize = 0;
    int fileDone = 0;
    int transferDone = 0;

    while (1) {
        // Listening!
        // Recv
        PACKET recvPacket;
        nBytes = recvfrom(socketRef, &recvPacket, (sizeof(int) * 2) + 18, 0, (struct sockaddr *) &serverAddressStorage, &addressSize);
        printf("\nReceived sequence: %d\n", recvPacket.header.seq_ack[3] - 48);
        printf("Expected sequence: %d\n", sequence);

        int isCorrupt = corrupt(recvPacket, sequence);
        int justFileDone = 0;

        if (isCorrupt == 1) {
            // Send an ACK_!sequence
            int not_sequence = 1 > sequence ? 1 : 0;
            PACKET ack = create_ack(not_sequence);
            printf("\nSending resend request ACK%d!\n", not_sequence);
            sendPacketS2C(ack, socketRef, serverAddressStorage, addressSize);
        } else if (isCorrupt == 0) {
            // Else if not corrupt and SEQ_sequence
            // Extract data
            // Send ACK_sequence
            // Increment state
            printf("Received message: ");
            for (int i = 0; i < recvPacket.header.length; i++) {
                printf("%d ", recvPacket.data[i]);
                buffer[cursor] = recvPacket.data[i];
                cursor += 1;
            }
            printf("\n");
            if (fileDone == 0) {
                if (recvPacket.data[recvPacket.header.length - 2] == '|') {
                    fileDone = 1; 
                    fileNameSize += recvPacket.header.length - 2;
                    printf("\nReceived file name\n");
                    printf("File name size: %d\n", fileNameSize);
                    justFileDone = 1;
                } else {
                    fileNameSize += recvPacket.header.length;
                }
            }   
            if (recvPacket.header.length == -1) {
                break;
            } else {    
                PACKET ack = create_ack(sequence);
                printf("\nSending ACK%d!\n", sequence);
                sendPacketS2C(ack, socketRef, serverAddressStorage, addressSize);
                sequence = 1 > sequence ? 1 : 0;   
                if (justFileDone == 1) {
                    sequence = 0;
                } 
            }
        }

    }

    printf("Done!\n");

    buffer[cursor] = '\0';
    char fileName[fileNameSize + 1];
    memcpy(fileName, &buffer, fileNameSize);
    fileName[fileNameSize] = '\0';

    printf("\nFilename: %s\n", fileName);
    printf("\nMessage: ");
    output = fopen(fileName, "wb");
    for (int i = fileNameSize + 1; i < cursor; i++) {
        printf("%c", buffer[i]);
        if(buffer[i] == '\0') continue;
        fwrite(&buffer[i], sizeof(char), 1, output);
    }
    fclose(output);
    printf("\n");
    return 0;
}
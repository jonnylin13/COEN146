// Jonny Lin
// Lab 3
// Client
// Should randomize checksum

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include "useful.h"
#include <time.h>

void sendData(char data[], int len, int socket, struct sockaddr_in address, socklen_t addressLength, struct timeval, tv, fd_set readfds, int end) {

    int cursor = 0;
    int nBytes;
    int sequence = 0;
    int resent = 0;

    // Start a main loop (while there is still data to be sent) - track this with a cursor variable
    while (cursor < len) { // cursor != eof

        int not_sequence = 1 > sequence ? 1 : 0;
        int remainingBytes = len - cursor;
        int bufferSize = 10;
        if (bufferSize > remainingBytes) {
            bufferSize = remainingBytes;
        }
        // Compute checksum
        // Construct packet with header, data, checksum
        char _data[bufferSize];
        for (int i = 0; i < bufferSize; i++) {
            _data[i] = data[cursor+i];
        }

        // Send seq packet with data
        PACKET packet = create_seq(sequence, _data, bufferSize);
        sendPacketC2S(packet, socket, address, addressLength);

        // Select timer
        rv = select(socketRef + 1, &readfds, NULL, NULL, &tv);
        if (rv == 0) {
          // Timeout
          resent++;
          if (resent == 3) {
            printf("Error: too many resend attempts, quitting");
            return;
          }
          continue;
        } else if (rv == 1) {
          // Receive data
          // Receive packet
          PACKET recvPacket;
          printf("Expected sequence: %d\n", sequence);
          nBytes = recvfrom(socket, &recvPacket, (sizeof(int) * 2) + 18, 0, NULL, NULL);
          printf("Received sequence: %d\n", recvPacket.header.seq_ack[3] - 48);

          // Is the packet corrupt? Wrong sequence or checksum
          int isCorrupt = corrupt(recvPacket, sequence);

          if (isCorrupt == 0) {
              printf("\nReceived correct ACK! Continuing...\n");

              // Update sequence and cursor
              sequence = 1 > sequence ? 1 : 0;
              cursor += bufferSize;

              resent = 0;
          } else if (isCorrupt == 1) {
              printf("\nReceived incorrect ACK! Re-sending previous message!\n");
              // Wrong ACK, do nothing to re-send the same seq packet
          }
        }


    }

    if (end == 1) {
        sendPacketC2S(create_seq_goodbye(sequence), socket, address, addressLength);
    }

    printf("Done!\n");
}

int main(int argc, char *argv[]) {

    int socketRef, port;
    struct sockaddr_in serverAddress;
    socklen_t addressSize;
    FILE *inputFile;

    // Set up timer
    struct timeval tv;
    int rv;
    fd_set readfds;

    if (argc != 5) {
        printf("Usage: %s <port> <ip> <input file> <output file>\n", argv[0]);
        return 1;
    }

    srand(time(NULL));

    inputFile = fopen(argv[3], "rb");
    char *outputFile = argv[4];
    strcat(outputFile, "|\0");

    // Configure server address
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(atoi(argv[1]));
    inet_pton(AF_INET, argv[2], &serverAddress.sin_addr.s_addr);
    addressSize = sizeof(serverAddress);

    // Create socket
    socketRef = socket(PF_INET, SOCK_DGRAM, 0);
    fcntl(socketRef, F_SETFL, O_NONBLOCK);
    FD_ZERO($readfds);
    FD_SET(socketRef, &readfds);
    tv.tv_sec = 10;
    tv.tv_usec = 0;
    sendData(outputFile, strlen(outputFile) + 1, socketRef, serverAddress, addressSize, tv, readfds, 0);

    fseek(inputFile, 0, SEEK_END);
    int fileSize = ftell(inputFile);
    rewind(inputFile);
    printf("\nFile size: %d\n", fileSize);
    char data[fileSize + 1];
    int comp = fread(&data, 1, fileSize, inputFile);
    data[fileSize] = '\0';
    printf("\nSending data: ");
    for (int i = 0; i < fileSize; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");
    fclose(inputFile);
    sendData(data, fileSize, socketRef, serverAddress, addressSize, tv, readfds, 1);

    return 0;
}

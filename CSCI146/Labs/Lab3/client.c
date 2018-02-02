// Jonny Lin
// Lab 3
// Client
// Should randomize checksum

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <useful.h>

int main(int argc, char *argv[]) {
    int socketRef, port, nBytes;
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


    return 0;
}

char* sendPacket(struct PACKET packet, int socket, struct sockaddr address, sockle_t addressLength) {
    int packetSize = 96 + packet.header.length; // Header length + length of data
    // Copy all the bits into char buffer
    char *buffer[packetSize];

    memcpy(buffer, packet.header.seq_ack, sizeof(int));
    memcpy(buffer+sizeof(int), packet.header.length, sizeof(int));
    memcpy(buffer+64, packet.header.checksum, sizeof(int));
    memcpy(buffer+96, packet.data, sizeof(char) * 10);

    sendto(socket, );
}

void sendData(char data[], int len, int socket, struct sockaddr address, socklen_t addressLength) {
    int cursor = 0;
    while (cursor != len) { // cursor != eof

        int remainingBits = len - cursor;
        int bufferSize = 10;
        if (bufferSize > remainingBits) {
            bufferSize = remainingBits;
        }

        struct HEADER initHeader;
        struct PACKET initPacket;
        initHeader.seq_ack = atoi("SEQ0");
        initHeader.length  = bufferSize;

        int checksum = initHeader.seq_ack ^ initHeader.length;
        char[bufferSize] data;
        for (int i = 0; i < bufferSize; i++) {
            checksum ^= data[cursor+i];
            data[i] = data[cursor+i];
        }
        initHeader.checksum = checksum;
        initPacket.header = initHeader;
        initPacket.data = data;

        

    }
    // Start a main loop (while there is still data to be sent) - track this with a cursor variable
    // Create packet
    // Header includes seq_ack, len (of data), and cksum
    // Compute checksum
    // Construct packet with header, data, checksum
    // Send the initial packet with SEQ0

    // Recv response
    // Start another loop here so we can keep resending the second packet if it fails
    // If checksum is wrong or returns with ACK1, resend initial packet (continue)
    // Else if checksum is correct and ACK0, proceed...
    // Compute checksum for second chunk of data
    // Construct header with SEQ1
    // Send the packet
    // Recv response
    // If checksum is wrong or returns with ACK0, resend previous packet (continue)
    // Else if checksum is correct and ACK1, proceed... (break out of the nested loop back into main loop)
}
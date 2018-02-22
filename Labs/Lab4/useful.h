#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    char seq_ack[5];
    int length;
    int checksum;
} HEADER;

typedef struct {
    HEADER header;
    char data[11];
} PACKET;

PACKET create_ack(int sequence) {
    PACKET result;
    HEADER resultHeader;
    resultHeader.seq_ack[0] = 'A';
    resultHeader.seq_ack[1] = 'C';
    resultHeader.seq_ack[2] = 'K';
    resultHeader.seq_ack[3] = sequence + 48;
    resultHeader.seq_ack[4] = '\0';
    resultHeader.length = 0;
    resultHeader.checksum = 1;
    result.header = resultHeader;
    return result;
}

PACKET create_seq(int sequence, char data[], int length) {
    PACKET result;
    HEADER resultHeader;
    resultHeader.seq_ack[0] = 'S';
    resultHeader.seq_ack[1] = 'E';
    resultHeader.seq_ack[2] = 'Q';
    resultHeader.seq_ack[3] = sequence + 48;
    resultHeader.seq_ack[4] = '\0';
    resultHeader.length = length;
    int checksum = resultHeader.length;
    for (int i = 0; i < length; i++) {
        checksum ^= data[i];
        result.data[i] = data[i];
    }
    result.data[10] = '\0';
    resultHeader.checksum = checksum;
    result.header = resultHeader;
    return result;
}

PACKET create_seq_goodbye(int sequence) {
    PACKET result;
    HEADER resultHeader;
    resultHeader.seq_ack[0] = 'S';
    resultHeader.seq_ack[1] = 'E';
    resultHeader.seq_ack[2] = 'Q';
    resultHeader.seq_ack[3] = sequence + 48;
    resultHeader.seq_ack[4] = '\0';
    resultHeader.length = -1;
    resultHeader.checksum = 1;
    result.header = resultHeader;
    return result;
}

PACKET create_ack_goodbye(int sequence) {
    PACKET result;
    HEADER resultHeader;
    resultHeader.seq_ack[0] = 'S';
    resultHeader.seq_ack[1] = 'E';
    resultHeader.seq_ack[2] = 'Q';
    resultHeader.seq_ack[3] = sequence + 48;
    resultHeader.seq_ack[4] = '\0';
    resultHeader.length = -1;
    resultHeader.checksum = 1;
    result.header = resultHeader;
    return result;
}


void sendPacketC2S(PACKET packet, int socket, struct sockaddr_in address, socklen_t addressLength) {
    int packetSize = (sizeof(int) * 2) + 18;
    int random = rand() % 101;
    if (random <= 20 && packet.header.length != -1) {
        printf("RNG: %d\n", random);
        packet.header.checksum = 0;
        printf("Sending faulty packet!\n");
    }
    printf("Sent message: ");
    for (int i = 0; i < packet.header.length; i++) {
        printf("%d ", packet.data[i]);
    }
    printf("\n");
    printf("Sending checksum: %d\n", packet.header.checksum);
    sendto(socket, &packet, packetSize, 0, (struct sockaddr*) &address, addressLength);
}

void sendPacketS2C(PACKET packet, int socket, struct sockaddr_storage address, socklen_t addressLength) {
    int packetSize = (sizeof(int) * 2) + 18;
    printf("Sending checksum: %d\n", packet.header.checksum);
    int random = rand() % 101;
        printf("RNG: %d\n", random);
    if (random <= 5) {
        printf("Packet was not sent!\n");
        return;
    }
    sendto(socket, &packet, packetSize, 0, (struct sockaddr*) &address, addressLength);
}

int corrupt(PACKET packet, int expectedSeq) {
    int checksum = packet.header.length;
    if (packet.header.length == 0 || packet.header.length == -1) {
        checksum = 1;
    } else {
        for (int i = 0; i < packet.header.length; i++) {
            checksum ^= packet.data[i];
        }
    }
    printf("\nComparing the following checksums:\n");
    printf("Calculated: %d\n", checksum);
    printf("Received: %d\n", packet.header.checksum);
    if ((packet.header.seq_ack[3] - 48) == expectedSeq && checksum == packet.header.checksum) {
        printf("Packet received was not corrupt!\n");
        return 0;
    }
    printf("Packet received was corrupt...\n");
    return 1;
}

typedef struct {
    int seq_ack;
    int length;
    int checksum;
} HEADER;

typedef struct {
    HEADER header;
    char data[10];
} PACKET;
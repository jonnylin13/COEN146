// Jonathan Lin
// Lab 2
// Client 

#include <sys/socket.h>
#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

enum {
    BUFFER_SIZE = 10
};

int main(int argc, char *argv[]) {

    int socket_ref = 0;
    char buff[BUFFER_SIZE];
    struct sockaddr_in serv_addr;
    FILE *source;

    if (argc != 3) {
        printf("\nUsage: %s <ip of server> <file name>\n", argv[0]);
        return 1;
    }

    source = fopen(argv[2], "rb");

    // Init memory
    memset(buff, '0', sizeof(buff));
    memset(&serv_addr, '0', sizeof(serv_addr));

    // Create the socket
    if (socket_ref = socket(AF_INET, SOCK_STREAM, 0) < 0) {
        printf("\nCould not create socket...\n");
        return 1;
    }

    // Set family protocol and port (big endian)
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000);

    // Convert address to numeric binary
    if (inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) <= 0) {
        printf("\ninet_pton error has occurred...\n");
        return 1;
    }

    // Connect
    if (connect(socket_ref, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection failed...\n");
        return 1;
    }

    int comp = fread(&buff, 1, BUFFER_SIZE, source);
    printf("\n");
    while(comp == BUFFER_SIZE) {
        write(socket_ref, buff, BUFFER_SIZE);
        printf("Writing: %s\n", buff);
        comp = fread(&buff, 1, BUFFER_SIZE, source);
    }
    write(socket_ref, buff, comp);
    printf("Writing: %s\n", buff);

    fclose(source);
    close(socket_ref);
    return 0;



}
// Jonathan Lin
// Lab 2 
// Server

#include <sys/socket.h> 
#include <stdio.h>
#include <string.h>
#include <netinet/in.h> // struct sockaddr_in
#include <arpa/inet.h>
#include <errno.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

enum {
    BUFFER_SIZE = 4
};

int main(int argc, char *argv[]) {

    int socket_ref = 0, accept_ref = 0, read_ref = 0;
    struct sockaddr_in serv_addr;
    char buff[BUFFER_SIZE];
    FILE *output;

    if (argc != 2) {
        printf("\nUsage: %s <output file>\n", argv[0]);
        return 1;
    }

    output = fopen(argv[1], "wb");

    // Initialize buffer and server address
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(buff, '0', sizeof(buff));

    // Family protocol
    serv_addr.sin_family = AF_INET;
    // Convert (no address in particular) to big endian
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    // Convert port to big endian
    serv_addr.sin_port = htons(5000);

    // Create socket
    socket_ref = socket(AF_INET, SOCK_STREAM, 0);
    bind(socket_ref, (struct sockaddr*) &serv_addr, sizeof(serv_addr));
    listen(socket_ref, 10); // Socket, timeout 

    printf("\nListening!\n");
    while (1) {
        accept_ref = accept(socket_ref, (struct sockaddr*) NULL, NULL);
        // While no errors
        while ((read_ref = read(accept_ref, buff, sizeof(buff))) > 0) {
            fwrite(&buff, sizeof(buff), 1, output);
        }
        break;
    }
    fclose(output);
    close(socket_ref);
    
    return 0;
}
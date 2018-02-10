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
    BUFFER_SIZE = 5
};

int main(int argc, char *argv[]) {

    int socket_ref = 0, accept_ref = 0, read_ref = 0;
    struct sockaddr_in serv_addr;
    char buff[BUFFER_SIZE];
    FILE *output;

    if (argc != 2) {
        printf("\nUsage: %s <port>\n", argv[0]);
        return 1;
    }

    // Initialize buffer and server address memory
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(buff, '0', sizeof(buff));

    // Family protocol
    serv_addr.sin_family = AF_INET;
    // Convert (no address in particular) to big endian
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); // Value accept any incoming interfaces
    // Convert port to big endian
    serv_addr.sin_port = htons(atoi(argv[1]));

    // Create socket
    socket_ref = socket(AF_INET, SOCK_STREAM, 0);
    bind(socket_ref, (struct sockaddr*) &serv_addr, sizeof(serv_addr));
    listen(socket_ref, 10); // Socket, timeout 

    printf("\nListening!\n");
    while (1) {
        accept_ref = accept(socket_ref, (struct sockaddr*) NULL, NULL);
        // If accepted a connection
        if (accept_ref > 0) {

            // Define output file
            char output_name[255];
            char selector[2];

            // While 1 bit is read by the socket
            while ((read_ref = read(accept_ref, selector, 1)) > 0) {
                if (selector[0] == '\0') {
                    // Done if we reach \0
                    printf("\nOutput file name received\n");
                    break;

                } else if (read_ref == 1){
                    int len = strlen(output_name);
                    output_name[len] = selector[0];
                    output_name[len + 1] = '\0';
                    // Else concatenate to output_name
                }
            }
            printf("%s\n", output_name);
            output = fopen(output_name, "wb");

            // While BUFFER_SIZE bits is read by the socket (5 for server)
            while ((read_ref = read(accept_ref, buff, BUFFER_SIZE)) > 0) {
                printf("%s\n", buff);
                fwrite(&buff, strlen(buff), 1, output); // Write buffer to our file
            }

            break;
        }
    }
    fclose(output);
    close(socket_ref);
    
    return 0;
}

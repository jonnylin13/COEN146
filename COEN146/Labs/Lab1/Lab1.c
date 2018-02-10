#include <stdio.h>

// Jonathan Lin

enum {
    BUFFER_SIZE = 10
};

int main(int argc, char* argv[]) {

    if (argc != 3) {
        return -1;
    }

    FILE *source;
    FILE *destination;

    char buffer[BUFFER_SIZE + 1]; 

    printf("\nOpening files...\n");
    source = fopen(argv[1], "rb");
    destination = fopen(argv[2], "wb");

    printf("Reading and copying...\n");

    int comp = fread(&buffer, 1, BUFFER_SIZE, source);
    while(comp == BUFFER_SIZE) {
        buffer[BUFFER_SIZE] = '\0';
        fwrite(&buffer, BUFFER_SIZE, 1, destination);
        comp = fread(&buffer, 1, BUFFER_SIZE, source);
    }
    buffer[comp] = '\0';
    fwrite(&buffer, comp, 1, destination);

    printf("Closing files...\n");
    fclose(source);
    fclose(destination);
    return 0;
}
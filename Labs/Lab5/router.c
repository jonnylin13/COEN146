#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void calculate(void* arg) {

}


void recv_update(void* arg) {

}

int main(int argc, char* argv[]) {

    if (argc != 5) {
        printf("Usage: %s <router id> <number of nodes> <file1> <file2>\n", argv[0]);
        return 1;
    }

    // Input validation
    char term;
    if (scanf("%d%c", &argv[1], &term) != 2 || term != '\n') {
        printf("Invalid router id\n");
        return 1;
    } 
    int rid = (int*) argv[1];

    if (scanf("%d%c", argv[2], &term) != 2 || term != '\n') {
        printf("Invalid number of nodes\n");
        return 1;
    }
    int n_nodes = (int*) argv[2];

    FILE *file1 = fopen(argv[3], "rb");
    FILE *file2 = fopen(argv[4], "rb");

    pthread_t tid;
    pthread_create(&tid, NULL, recv_update, NULL);
    pthread_create(&tid, NULL, calculate, NULL);

    // Command listener
    int done = 0;
    while (done == 0) {

    }

    pthread_exit(NULL);

} 
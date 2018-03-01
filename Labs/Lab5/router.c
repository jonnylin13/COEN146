#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Utility

struct cost_table {
    int size;
    int *data[1000][1000];
}

/** Convenience function to return cost at position p[i][j] */
int get_cost(cost_table *table, int i, int j) {
    return *table->data[i][j];
}

// Multi-threaded functions

void *calculate(void *arg) {

}


void *recv_update(void *arg) {

}

// Entrypoint

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
    int rid = *argv[1];

    if (scanf("%d%c", argv[2], &term) != 2 || term != '\n') {
        printf("Invalid number of nodes\n");
        return 1;
    }
    int n_nodes = *argv[2];

    FILE *file1 = fopen(argv[3], "rb");
    FILE *file2 = fopen(argv[4], "rb");

    // Initialize our tables
    int cost_a;
    char buff[1];
    int *data[n_nodes][n_nodes];
    int comp = fread(&buff, 1, 1, file1);
    int i, j = 0;
    while(comp == 1) {

        if (buff[0] == '\n') j++; continue;
        if (buff[0] == ' ') continue;

        data[i][j] = *buff[0];

        i++;
        comp = fread(&buff, 1, 1, file1);
    }
    cost_table *ct = {.size = n_nodes, .data = data};

    printf("cost: %d\n", ct->data[0][0]);

    pthread_t tid;
    pthread_create(&tid, NULL, recv_update, NULL);
    pthread_create(&tid, NULL, calculate, NULL);

    // Command listener
    int done = 0;
    while (done == 0) {

    }

    pthread_exit(NULL);

} 
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Utility

typedef struct {
    int size;
    int **data;
} cost_table;

/** Convenience function to return cost at position p[i][j] */
int get_cost(cost_table *table, int i, int j) {
    return table->data[i][j];
}

/** Runs Djikstra's algorithm to re-calculate least-cost paths */
void _calculate() {

}

/** Listens for commands and places them into a queue
 * Every 10-20 seconds (lifecycle of calculate thread)
 * The program will first execute the next command in the queue
 * Then it will continue with normal operation
 * This is to ensure that we are not manipulating our data struct asynchronously from two places
 */
void command_listener() {
    int done = 0;
    while (done == 0) {

    }
}

// Multi-threaded functions

/** Sleeps for a random number of seconds (10-20)
 * Runs Djikstra's Algorithm to calculate least-cost paths
 * Outputs the current least costs
*/
void *calculate(void *arg) {
    // Sleep
    // Then calculate
    _calculate();
}

/** Receives messages from other nodes 
 * When receiving an updated cost c from sender s to this node
 * c will update in both this node and the sender
 * At the end, call _calculate()
 */
void *recv_update(void *arg) {
    // Init UDP
    // Recv message in loop
    // Upon receiving a message, update the cost_table and _calculate()
}

/** Entry point */
int main(int argc, char* argv[]) {

    if (argc != 5) {
        printf("Usage: %s <router id> <number of nodes> <file1> <file2>\n", argv[0]);
        return 1;
    }

    // Inputs
    char rid_c = *argv[1];
    char n_nodes_c = *argv[2];
    int rid = rid_c - '0';
    int n_nodes = n_nodes_c - '0';

    printf("Creating cost table with %d nodes\n" , n_nodes);

    FILE *file1 = fopen(argv[3], "rb");
    FILE *file2 = fopen(argv[4], "rb");

    // Initialize our tables
    int cost_a;
    char buff[1];
    int **data = (int **) malloc(sizeof(int*) * n_nodes);

    for (int x = 0; x < n_nodes; x++) {
        data[x] = (int *) calloc(n_nodes, sizeof(int));
    }

    int comp = fread(&buff, 1, 1, file1);
    int i, j = 0;
    while(comp == 1) {

        
        printf("Test\n");

        if (buff[0] == '\n') {
            j++;
            comp = fread(&buff, 1, 1, file1);
            continue;
        }
        if (buff[0] == ' ') {
            comp = fread(&buff, 1, 1, file1);
            continue;
        }

        data[i][j] = buff[0];

        i++;
        comp = fread(&buff, 1, 1, file1);
    }

    fclose(file1);
    
    cost_table ct;
    ct.size = n_nodes;
    ct.data = data;

    printf("cost: %d\n", ct.data[0][0]);

    return 1;

    pthread_t tid;
    pthread_create(&tid, NULL, recv_update, NULL);
    pthread_create(&tid, NULL, calculate, NULL);
    command_listener();

    }

    pthread_exit(NULL);

} 
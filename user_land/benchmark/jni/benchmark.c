#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "../../common.h"

#define USE_TMALLOC
#define ACQUIRE_SIZE 4096

int main(int argc, char* argv[]) {
    int i, j, k;
    char* mem;

    assert(argc == 3);

    int process_number = atoi(argv[1]);
    int mem_allocation = atoi(argv[2]);
    int epoch = atoi(argv[3]);

    printf("process=%d mem=%d epoch=%d\n", process_number, mem_allocation, epoch);

    while (epoch-- > 0) {
        for (i = 0; i < process_number; i++) {
            int pid = fork();
            if (pid == 0) {
                for (j = 0; j < mem_allocation; j += ACQUIRE_SIZE) {
                    #ifdef USE_TMALLOC
                    mem = tmalloc(ACQUIRE_SIZE);
                    #else
                    mem = malloc(ACQUIRE_SIZE);
                    #endif
                    // printf("acquired: %d\n", j >> 12);
                    if (!mem) {
                        printf("malloc / tmalloc returns NULL on %d\n", j >> 12);
                        exit(1);
                    }
                    memset(mem, 0, ACQUIRE_SIZE);
                }
                printf("malloc complete\n");
                exit(0);
            }
            if (pid < 0) {
                printf("fork failed\n");
            }
        }
        while (wait(NULL) > 0) printf("child process exit\n");
    }
    return 0;
}

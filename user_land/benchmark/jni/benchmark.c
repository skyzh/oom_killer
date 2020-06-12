#include <stdio.h>
#include <assert.h>
#include <string.h>

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
            if (fork() == 0) {
                mem = malloc(mem_allocation);
                memset(mem, 0, mem_allocation);
                free(mem);
                return 0;
            }
        }
        while (wait(NULL) > 0);
    }

    return 0;
}

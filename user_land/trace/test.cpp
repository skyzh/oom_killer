#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;

const int ALLOC_SIZE = 1024 * 1024;
int main() {
    for (int k = 0; k < 16; k++) {
        if (fork() == 0) {
            for (int i = 0; i < 128; i++) {
                char* x = new char[ALLOC_SIZE];
                memset(x, 0, ALLOC_SIZE);
            }
            return 0;
        }
    }
    printf("uid=%d", getuid());
    while (wait(NULL) > 0);
    return 0;
}

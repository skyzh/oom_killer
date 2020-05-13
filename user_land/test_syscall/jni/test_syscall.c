#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int uid = atoi(argv[1]);
    int limit = atoi(argv[2]);
    syscall(380, uid, limit);
    return 0;
}

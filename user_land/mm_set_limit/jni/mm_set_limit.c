#include <stdio.h>
#include <stdlib.h>
#include "../../common.h"

int main(int argc, char* argv[]) {
    int uid = atoi(argv[1]);
    int limit = atoi(argv[2]);
    if (set_mm_limit(uid, limit) < 0) {
        printf("failed to set limit\n");
        return 1;
    }
    return 0;
}

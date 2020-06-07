#include <sys/stat.h> 
#include <sys/syscall.h> 
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "../../common.h"

#define LIMIT_BUFFER 128

void read_limit() {
    int size;
    uid_t uid[LIMIT_BUFFER];
    unsigned long mm_max[LIMIT_BUFFER];
    int i;

    if ((size = get_mm_limit(uid, mm_max, LIMIT_BUFFER)) > 0) {
        printf("limit buffer updated %d\n", size);
        for (i = 0; i < size; i++) {
            printf("%d: %ld\n", uid[i], mm_max[i]);
        }
    } else {
        printf("failed to update limit buffer %d\n", size);
    }
}

int main() {
    read_limit();
}

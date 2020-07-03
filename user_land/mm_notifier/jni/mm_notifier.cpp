#include <iostream>
#include <fstream>
#include <unordered_map>
#include <set>
#include <sys/stat.h> 
#include <sys/syscall.h> 
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#include <thread>

#include "../../common.h"

using namespace std;

const bool AGGRESSIVE = true;

const int BUFFER_SIZE = 1024;
unordered_map<int, int> pid_to_user;
unordered_map<int, long> pid_allocation;
unordered_map<int, long> user_allocation;
unordered_map<int, long> user_limit;
int trigger = 0;

const int LIMIT_BUFFER = 128;

inline long get_soft_limit(long limit) {
    return limit * 0.9;
}

void read_limit() {
    int size;
    uid_t uid[LIMIT_BUFFER];
    unsigned long mm_max[LIMIT_BUFFER];

    user_limit.clear();
    if ((size = get_mm_limit(uid, mm_max, LIMIT_BUFFER)) > 0) {
        printf("limit buffer updated %d\n", size);
        for (int i = 0; i < size; i++) {
            user_limit[uid[i]] = get_soft_limit(mm_max[i]);
        }
    } else {
        // printf("failed to update limit buffer %d\n", size);
    }
}

inline int read_uid(int pid) {
    if (pid_to_user.count(pid) == 0) {
        char file_path[BUFFER_SIZE];
        sprintf(file_path, "/proc/%d/status", pid);
        FILE* fd = fopen(file_path, "r");

        if (!fd) return 0;

        char buf[BUFFER_SIZE];
        int uid = 0;

        while (fgets(buf, BUFFER_SIZE, fd)) {
            sscanf(buf, "Uid:%d", &uid);
        }

        fclose(fd);

        pid_to_user[pid] = uid;
        return uid;
    } else {
        return pid_to_user[pid];
    }
}

void check_allocation(int uid, long prev_allocation, long allocation) {
    long limit = user_limit[uid];
    if (limit != 0) {
        if (prev_allocation <= limit && allocation > limit) {
            trigger += 1;
            printf("triggered as %d exceed %ld (%ld)\n", uid, limit, allocation);
            run_oom_killer();
        }
        if (prev_allocation > limit && allocation <= limit) {
            trigger -= 1;
        }
    }
}

inline void process_event(int pid, const char* type, int member, long size) {
    int transformed_pid = pid * 2 + member;
    if (strcmp(type, "rss_stat") == 0) {
        long delta = size - pid_allocation[transformed_pid];
        pid_allocation[transformed_pid] = size;
        int uid = read_uid(pid);

        long prev_allocation = user_allocation[uid];
        long next_allocation = prev_allocation + delta;
        user_allocation[uid] = next_allocation;

        check_allocation(uid, prev_allocation, next_allocation);
    }
}

void stat() {
    printf("stat\n");
    for (auto v: user_allocation) {
        printf("%d: %ld\n", v.first, v.second);
    }
}

int main() {
    const char* pipe_path = "/sys/kernel/debug/tracing/trace_pipe";
    // const char* pipe_path = "test_file.in";
    FILE* pipe_file = fopen(pipe_path, "r");
    char buffer[BUFFER_SIZE];
    char event_name[BUFFER_SIZE];
    int pid;
    int member;
    long size;
    int count = 0;
    int oom_count = 0;
    printf("mm_notifier running...\n");
    read_limit();
    while (fgets(buffer, BUFFER_SIZE, pipe_file)) {
        sscanf(&buffer[17], "%d", &pid);
        sscanf(&buffer[48], "%[a-zA-Z_]: member=%d size=%ld", event_name, &member, &size);
        process_event(pid, event_name, member, size);
        if (++count > 1000) {
            read_limit();
            stat();
            count = 0;
            pid_to_user.clear();
            pid_allocation.clear();
            user_allocation.clear();
            trigger = 0;
        }
        
        if (++oom_count > 10) {
            oom_count = 0;
            if (trigger > 0) {
                if (AGGRESSIVE) {
                    std::thread (run_oom_killer).detach();
                } else {
                    run_oom_killer();
                }
            }
        }
    }
    fclose(pipe_file);
    return 0;
}

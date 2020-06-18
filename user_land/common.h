inline long set_mm_limit(uid_t uid, unsigned long mm_max) {
    return syscall(380, uid, mm_max);
}

inline long get_mm_limit(uid_t *uid, unsigned long *mm_max, 
                unsigned int max_element) {
    return syscall(381, uid, mm_max, max_element);
}

inline long run_oom_killer(void) {
    return syscall(382);
}

inline long transaction_reserve(unsigned long mm_transaction) {
    return syscall(378, mm_transaction);
}

inline long transaction_commit(unsigned long mm_transaction) {
    return syscall(379, mm_transaction);
}

inline void* tmalloc(size_t size) {
    void* space = NULL;
    size_t commit_size = (size + 4095) << 12 + 10;
    if (!transaction_reserve(commit_size)) {
        return NULL;
    }
    space = malloc(size);
    transaction_commit(commit_size);
    return space;
}

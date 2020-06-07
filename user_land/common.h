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

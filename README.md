# OS Project 2

## TL;DR

First of all, you need to patch the original kernel. Here I provide 2 ways.

1. Use `kernel_space/patch.diff`. Apply it on goldfish-3.4 from AOSP project.
2. Copy all files from `kernel_space/archive.zip`. They are kept to have the same structure as in Linux kernel.

Then, you may build and run the kernel. After the emulator is boot with new kernel, use Makefile in user_land to run tests.

```bash
make notifier # run user-space daemon
make test
```

This will automatically build test program, push it to `/data/local`, and run it with 10070 user.

## Project Structure

```
.
├── kernel_space                files modified in Linux Kernel
│   ├── archive.zip             all modified files in original folder structure
│   ├── patch.diff              patch file, should be applied on git repo
│   └── patch.sh                script used to generate patch file
└── user_land
    ├── Makefile
    ├── benchmark               benchmark program
    │   ├── jni
    │   │   ├── Android.mk
    │   │   └── benchmark.c
    │   ├── out
    │   │   └── dummy.txt
    │   └── result              benchmark raw result
    │       ├── goldfish_3.4.out
    │       ├── kernel_log.txt
    │       ├── kernel_log_notifier.txt
    │       ├── kernel_log_timer.txt
    │       ├── kernel_log_trivial.txt
    │       ├── oom_killer_disabled.out
    │       ├── oom_killer_enabled.out
    │       ├── oom_killer_trivial.out
    │       ├── oom_killer_with_limit.out
    │       └── original.out
    ├── benchmark_analysis      benchmark analysis scripts
    │   ├── analysis.Rmd
    │   ├── analysis_overcommit.Rmd
    │   ├── kernel_log_parser.py
    │   ├── parse.sh
    │   ├── parser.py
    │   ├── result.csv
    │   └── result_overcommit.csv
    ├── common.h                contains all syscall wrapper and tmalloc
    ├── mm_get_limit            program to get all limit in system
    │   └── jni
    │       ├── Android.mk
    │       └── mm_get_limit.c
    ├── mm_notifier             the user-space daemon
    │   └── jni
    │       ├── Android.mk
    │       ├── Application.mk
    │       └── mm_notifier.cpp
    ├── mm_set_limit            program to set a user limit
    │   └── jni
    │       ├── Android.mk
    │       └── mm_set_limit.c
    ├── project2_test           test program provided by TA
    │   └── jni
    │       ├── Android.mk
    │       └── project2_test.c
    └── trace                   debug scripts for event tracing
        ├── Makefile
        ├── enable_trace.sh
        └── test.cpp
```

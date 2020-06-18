INSTALL_PATH=/data/local
ARCH=armeabi
SHELL:=/bin/bash
TESTCASE_COLOR=\033[1;34m
NO_COLOR=\033[0m
LIMIT=10070 10000

all: run

build_%:
	@echo -e "$(TESTCASE_COLOR)building $*...$(NO_COLOR)"
	cd $* && ndk-build

push_%: build_%
	@echo -e "$(TESTCASE_COLOR)pushing $*...$(NO_COLOR)"
	@adb push ./$*/obj/local/$(ARCH)/$* $(INSTALL_PATH)

set_limit: push_mm_set_limit
	@echo -e "$(TESTCASE_COLOR)running mm_set_limit...$(NO_COLOR)"
	@adb shell "cd $(INSTALL_PATH) && ./mm_set_limit $(LIMIT)"

test: set_limit push_project2_test
	@echo -e "$(TESTCASE_COLOR)running project2 test...$(NO_COLOR)"
	@adb shell "su 10070 $(INSTALL_PATH)/project2_test u0_a70 100000000 160000000 160000000 160000000 160000000 160000000"

get_limit: push_mm_get_limit
	@echo -e "$(TESTCASE_COLOR)running mm_get_limit...$(NO_COLOR)"
	@adb shell "cd $(INSTALL_PATH) && ./mm_get_limit"

clean_%: FORCE
	cd $* && ndk-build clean

clean: clean_mm_get_limit clean_mm_notifier clean_mm_set_limit clean_benchmark

notifier: push_mm_notifier
	@echo -e "$(TESTCASE_COLOR)running mm_notifier...$(NO_COLOR)"
	@adb shell "echo 1 > /sys/kernel/debug/tracing/events/kmem/rss_stat/enable"
	@echo -e "$(TESTCASE_COLOR)event tracing enabled...$(NO_COLOR)"
	@adb shell "(cd $(INSTALL_PATH) && nohup nice -n -20 ./mm_notifier) &"
	@echo -e "$(TESTCASE_COLOR)mm_notifier is running as background service$(NO_COLOR)"

notifier_foreground: push_mm_notifier
	@echo -e "$(TESTCASE_COLOR)running mm_notifier...$(NO_COLOR)"
	@adb shell "echo 1 > /sys/kernel/debug/tracing/events/kmem/rss_stat/enable"
	@echo -e "$(TESTCASE_COLOR)event tracing enabled...$(NO_COLOR)"
	@adb shell "cd $(INSTALL_PATH) && nice -n -20 ./mm_notifier"

check_notifier:
	@adb shell "ps | grep mm_notifier"

benchmark_overcommit: push_benchmark push_mm_set_limit
	@echo -e "$(TESTCASE_COLOR)running benchmark...$(NO_COLOR)"
	@rm benchmark/out/*.out; true
	adb shell "echo 2 > /proc/sys/vm/overcommit_memory"
	adb shell "cd $(INSTALL_PATH) && ./mm_set_limit 10070 16384"
	adb shell "cd $(INSTALL_PATH) && su 10070 ./benchmark 1 200000000 10"
	adb shell "cd $(INSTALL_PATH) && ./mm_set_limit 10070 32768"
	adb shell "cd $(INSTALL_PATH) && su 10070 ./benchmark 1 200000000 10"
	adb shell "cd $(INSTALL_PATH) && ./mm_set_limit 10070 16384"
	adb shell "cd $(INSTALL_PATH) && su 10070 ./benchmark 4 200000000 1"
	adb shell "cd $(INSTALL_PATH) && ./mm_set_limit 10070 16384"
	adb shell "cd $(INSTALL_PATH) && su 10070 ./benchmark 4 200000000 1"
	adb shell "cd $(INSTALL_PATH) && ./mm_set_limit 10070 16384"
	adb shell "cd $(INSTALL_PATH) && su 10070 ./benchmark 4 200000000 1"
	adb shell "cd $(INSTALL_PATH) && ./mm_set_limit 10070 16384"
	adb shell "cd $(INSTALL_PATH) && su 10070 ./benchmark 4 200000000 1"
	adb shell "cd $(INSTALL_PATH) && ./mm_set_limit 10070 16384"
	adb shell "cd $(INSTALL_PATH) && su 10070 ./benchmark 4 200000000 1"
	adb shell "cd $(INSTALL_PATH) && ./mm_set_limit 10070 32768"
	adb shell "cd $(INSTALL_PATH) && su 10070 ./benchmark 4 200000000 1"
	adb shell "cd $(INSTALL_PATH) && ./mm_set_limit 10070 32768"
	adb shell "cd $(INSTALL_PATH) && su 10070 ./benchmark 4 200000000 1"
	adb shell "cd $(INSTALL_PATH) && ./mm_set_limit 10070 32768"
	adb shell "cd $(INSTALL_PATH) && su 10070 ./benchmark 4 200000000 1"
	adb shell "cd $(INSTALL_PATH) && ./mm_set_limit 10070 32768"
	adb shell "cd $(INSTALL_PATH) && su 10070 ./benchmark 4 200000000 1"
	adb shell "cd $(INSTALL_PATH) && ./mm_set_limit 10070 32768"
	adb shell "cd $(INSTALL_PATH) && su 10070 ./benchmark 4 200000000 1"


benchmark_evaluation: push_benchmark
	@echo -e "$(TESTCASE_COLOR)running benchmark...$(NO_COLOR)"
	@rm benchmark/out/*.out; true
	adb shell "cd $(INSTALL_PATH) && ./mm_set_limit 10070 0"
	adb shell "cd $(INSTALL_PATH) && ./mm_set_limit 10071 2000000"
	adb shell "cd $(INSTALL_PATH) && ./mm_set_limit 10072 2000000"
	adb shell "cd $(INSTALL_PATH) && ./mm_set_limit 10073 2000000"
	adb shell "cd $(INSTALL_PATH) && ./mm_set_limit 10074 2000000"
	adb shell "cd $(INSTALL_PATH) && ./mm_set_limit 10075 2000000"
	adb shell "cd $(INSTALL_PATH) && ./mm_set_limit 10076 2000000"
	adb shell "cd $(INSTALL_PATH) && time su 10070 ./benchmark 1 4194304 100" >> benchmark/out/result.out
	adb shell "cd $(INSTALL_PATH) && time su 10070 ./benchmark 1 33554432 50" >> benchmark/out/result.out
	adb shell "cd $(INSTALL_PATH) && time su 10070 ./benchmark 1 67108864 20" >> benchmark/out/result.out
	adb shell "cd $(INSTALL_PATH) && time su 10070 ./benchmark 1 134217728 10" >> benchmark/out/result.out
	adb shell "cd $(INSTALL_PATH) && time su 10070 ./benchmark 4 1048576 100" >> benchmark/out/result.out
	adb shell "cd $(INSTALL_PATH) && time su 10070 ./benchmark 4 4194304 50" >> benchmark/out/result.out
	adb shell "cd $(INSTALL_PATH) && time su 10070 ./benchmark 4 16777216 20" >> benchmark/out/result.out
	adb shell "cd $(INSTALL_PATH) && time su 10070 ./benchmark 4 67108864 10" >> benchmark/out/result.out
	adb shell "cd $(INSTALL_PATH) && time su 10070 ./benchmark 8 1048576 50" >> benchmark/out/result.out
	adb shell "cd $(INSTALL_PATH) && time su 10070 ./benchmark 8 4194304 20" >> benchmark/out/result.out
	adb shell "cd $(INSTALL_PATH) && time su 10070 ./benchmark 8 16777216 10" >> benchmark/out/result.out

build_kernel:
	make -C $(KID)

emulator: build_kernel
	cd ~/android-sdk-linux/tools && ./emulator -no-window @OsPrj-518021910395 -show-kernel -kernel $(KERNEL_PATH)

emulator_log: build_kernel
	(cd ~/android-sdk-linux/tools && ./emulator -no-window @OsPrj-518021910395 -show-kernel -kernel $(KERNEL_PATH)) | tee -a kernel_log.txt

emulator_prebuilt:
	cd ~/android-sdk-linux/tools && ./emulator -no-window @OsPrj-518021910395 -show-kernel

FORCE:

.PHONY: FORCE

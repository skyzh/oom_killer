INSTALL_PATH=/data/local
ARCH=armeabi
SHELL:=/bin/bash
TESTCASE_COLOR=\033[1;34m
NO_COLOR=\033[0m
LIMIT=10070 10000

all: run

build_syscall_test: FORCE
	@echo -e "$(TESTCASE_COLOR)building syscall test...$(NO_COLOR)"
	cd test_syscall && ndk-build

build_project2_test: FORCE
	@echo -e "$(TESTCASE_COLOR)building project test...$(NO_COLOR)"
	cd test_project2 && ndk-build

build_notifier: FORCE
	@echo -e "$(TESTCASE_COLOR)building mm_notifier..$(NO_COLOR)"
	cd mm_notifier && ndk-build

build_get_limit: FORCE
	@echo -e "$(TESTCASE_COLOR)building mm_get_limit..$(NO_COLOR)"
	cd mm_get_limit && ndk-build

push: build_syscall_test build_project2_test build_get_limit
	@echo -e "$(TESTCASE_COLOR)pushing executables...$(NO_COLOR)"
	@adb push ./test_syscall/obj/local/$(ARCH)/test_syscall $(INSTALL_PATH)
	@adb push ./test_project2/obj/local/$(ARCH)/project2_test $(INSTALL_PATH)
	@adb push ./mm_get_limit/obj/local/$(ARCH)/mm_get_limit $(INSTALL_PATH)
	@adb shell "chmod 777 $(INSTALL_PATH)/project2_test"

push_notifier: build_notifier
	@adb push ./mm_notifier/obj/local/$(ARCH)/mm_notifier $(INSTALL_PATH)

set_limit: push
	@echo -e "$(TESTCASE_COLOR)running syscall test...$(NO_COLOR)"
	@adb shell "cd $(INSTALL_PATH) && ./test_syscall $(LIMIT)"

test: push
	@echo -e "$(TESTCASE_COLOR)running project2 test...$(NO_COLOR)"
	@adb shell "su 10070 $(INSTALL_PATH)/project2_test u0_a70 100000000 160000000"

get_limit: push
	@echo -e "$(TESTCASE_COLOR)running mm_get_limit...$(NO_COLOR)"
	@adb shell "cd $(INSTALL_PATH) && ./mm_get_limit"

clean: FORCE
	cd test_syscall && ndk-build clean
	cd test_project2 && ndk-build clean
	cd mm_notifier && ndk-build clean
	cd mm_get_limit && ndk-build clean

notifier: push_notifier
	adb shell "echo 1 > /sys/kernel/debug/tracing/events/kmem/rss_stat/enable"
	@adb shell "cd $(INSTALL_PATH) && ./mm_notifier"

emulator: FORCE
	make -C $(KID)
	cd ~/android-sdk-linux/tools && ./emulator -no-window @OsPrj-518021910395 -show-kernel -kernel $(KERNEL_PATH)
FORCE:

.PHONY: FORCE

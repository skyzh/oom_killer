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
	@adb shell "su 10070 $(INSTALL_PATH)/project2_test u0_a70 100000000 160000000"

get_limit: push_mm_get_limit
	@echo -e "$(TESTCASE_COLOR)running mm_get_limit...$(NO_COLOR)"
	@adb shell "cd $(INSTALL_PATH) && ./mm_get_limit"

clean_%: FORCE
	cd $* && ndk-build clean

clean: clean_mm_get_limit clean_mm_notifier clean_mm_set_limit

notifier: push_mm_notifier
	@echo -e "$(TESTCASE_COLOR)running mm_notifier...$(NO_COLOR)"
	adb shell "echo 1 > /sys/kernel/debug/tracing/events/kmem/rss_stat/enable"
	@adb shell "cd $(INSTALL_PATH) && nice -n -20 ./mm_notifier"

emulator: FORCE
	make -C $(KID)
	cd ~/android-sdk-linux/tools && ./emulator -no-window @OsPrj-518021910395 -show-kernel -kernel $(KERNEL_PATH)

FORCE:

.PHONY: FORCE

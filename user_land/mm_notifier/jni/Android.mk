LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := mm_notifier.cpp
LOCAL_MODULE := mm_notifier
LOCAL_CFLAGS += -pie -fPIE -O2
LOCAL_LDFLAGS += -pie -fPIE
LOCAL_FORCE_STATIC_EXECUTABLE := true

include $(BUILD_EXECUTABLE)

LOCAL_PATH := $(call my-dir)

$(info "LOCAL_PATH = $(LOCAL_PATH)")  
$(info "TARGET_ARCH_ABI = $(TARGET_ARCH_ABI)")  

#--------------------------------------------------------------
include $(CLEAR_VARS)
LOCAL_MODULE := pocoFoundation
LOCAL_SRC_FILES := ${LOCAL_PATH}/../../libs/Android/$(TARGET_ARCH_ABI)/libPocoFoundationd.a
include $(PREBUILT_STATIC_LIBRARY)
#--------------------------------------------------------------

include $(CLEAR_VARS)

LOCAL_MODULE := xlog

SDK_BASE_PATH := ${LOCAL_PATH}/../../BASE
SDK_DEPS_PATH := ${LOCAL_PATH}/../../deps

LOCAL_CPP_EXTENSION := .cpp .cc .cxx

LOCAL_SRC_FILES := \
${SDK_BASE_PATH}/src/utility/autobuffer.cc \
${SDK_BASE_PATH}/src/utility/ptrbuffer.cc \
${SDK_BASE_PATH}/src/log/EncryptLog.cpp \
${SDK_BASE_PATH}/src/log/LogBuffer.cpp \
${SDK_BASE_PATH}/src/log/LogFile.cpp \
${SDK_BASE_PATH}/src/log/BaseLog.cpp \
${SDK_BASE_PATH}/src/log/MarsLog.cpp \
${LOCAL_PATH}/com_example_XLog.cpp

LOCAL_C_INCLUDES := \
${SDK_BASE_PATH}/include \
${SDK_BASE_PATH}/src \
${SDK_DEPS_PATH}/poco/Foundation/include

# LOCAL_STATIC_LIBRARIES 后面静态库的顺序有严格讲究，被包含的lib需要放在包含的后面
LOCAL_STATIC_LIBRARIES := pocoFoundation
LOCAL_LDLIBS += -L$(SYSROOT)/usr/lib -llog

NDK_APP_DST_DIR := ${LOCAL_PATH}/../xlog/libs/${TARGET_ARCH_ABI}

include $(BUILD_SHARED_LIBRARY)

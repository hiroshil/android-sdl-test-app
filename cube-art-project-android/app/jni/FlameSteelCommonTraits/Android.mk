LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
APP_STL := c++_static
APP_CPPFLAGS := -fexceptions
APP_PLATFORM := android-16
LOCAL_MODULE := FlameSteelCommonTraits
LOCAL_C_INCLUDES := $(LOCAL_PATH)/src $(LOCAL_PATH)/../include
LOCAL_EXPORT_C_INCLUDES = $(LOCAL_PATH)/src/

#traverse all the directory and subdirectory
define walk
  $(wildcard $(1)) $(foreach e, $(wildcard $(1)/*), $(call walk, $(e)))
endef
#find all the file recursively under jni/
ALLFILES = $(call walk, $(LOCAL_PATH)/src)
FILE_LIST := $(filter %.cpp, $(ALLFILES))
$(info CubeArtProject source code files list)
$(info $(FILE_LIST))
LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)

LOCAL_SHARED_LIBRARIES += FlameSteelCore
LOCAL_SHARED_LIBRARIES += SDL2

LOCAL_LDFLAGS := -static-libstdc++
include $(BUILD_SHARED_LIBRARY)

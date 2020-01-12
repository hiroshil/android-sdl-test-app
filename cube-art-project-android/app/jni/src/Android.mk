LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main


SDL_PATH := ../SDL

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include $(LOCAL_PATH)/../FlameSteelCore/src $(LOCAL_PATH)/../CubeArtProject/src $(LOCAL_PATH)/../FlameSteelCommonTraits/src $(LOCAL_PATH)/../FlameSteelEngineGameToolkit/src $(LOCAL_PATH)/../include $(LOCAL_PATH)/../FlameSteelEngineGameToolkitFSGL/src $(LOCAL_PATH)/../FSGL/src

# Add your application source files here...
LOCAL_SRC_FILES := YourSourceHere.cpp

LOCAL_SHARED_LIBRARIES += SDL2
LOCAL_SHARED_LIBRARIES += FlameSteelCore
LOCAL_SHARED_LIBRARIES += CubeArtProject
LOCAL_SHARED_LIBRARIES += FlameSteelCommonTraits
LOCAL_SHARED_LIBRARIES += FlameSteelEngineGameToolkitFSGL

LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -llog

include $(BUILD_SHARED_LIBRARY)

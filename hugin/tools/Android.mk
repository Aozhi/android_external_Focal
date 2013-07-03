
LOCAL_PATH := $(my-dir)

######################################################
###                      ptclean                    ##
######################################################

include $(CLEAR_VARS)

LOCAL_SRC_FILES := cpclean.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH) \
	$(LOCAL_PATH)/../../vigra/include \
	$(LOCAL_PATH)/../../boost-1_53/ \
	$(LOCAL_PATH)/../../exiv2/include \
	$(LOCAL_PATH)/../../libpano13 \
	$(LOCAL_PATH)/..

LOCAL_SHARED_LIBRARIES := libhugin

LOCAL_MODULE := ptclean

include $(BUILD_EXECUTABLE)

######################################################
###                autooptimiser                    ##
######################################################

include $(CLEAR_VARS)

LOCAL_SRC_FILES := autooptimiser.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH) \
	$(LOCAL_PATH)/../../vigra/include \
	$(LOCAL_PATH)/../../boost-1_53/ \
	$(LOCAL_PATH)/../../exiv2/include \
	$(LOCAL_PATH)/../../libpano13 \
	$(LOCAL_PATH)/..

LOCAL_SHARED_LIBRARIES := libhugin libvigraimpex libpano13

LOCAL_MODULE := autooptimiser

include $(BUILD_EXECUTABLE)

######################################################
###                  pano_modify                    ##
######################################################

include $(CLEAR_VARS)

LOCAL_SRC_FILES := pano_modify.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH) \
	$(LOCAL_PATH)/../../vigra/include \
	$(LOCAL_PATH)/../../boost-1_53/ \
	$(LOCAL_PATH)/../../exiv2/include \
	$(LOCAL_PATH)/../../libpano13 \
	$(LOCAL_PATH)/..

LOCAL_SHARED_LIBRARIES := libhugin libvigraimpex libpano13

LOCAL_MODULE := pano_modify

include $(BUILD_EXECUTABLE)

######################################################
###                    pto_gen                      ##
######################################################

include $(CLEAR_VARS)

LOCAL_SRC_FILES := pto_gen.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH) \
	$(LOCAL_PATH)/../../vigra/include \
	$(LOCAL_PATH)/../../boost-1_53/ \
	$(LOCAL_PATH)/../../exiv2/include \
	$(LOCAL_PATH)/../../libpano13 \
	$(LOCAL_PATH)/../../lensfun/include/lensfun \
	$(LOCAL_PATH)/..

LOCAL_SHARED_LIBRARIES := libhugin libvigraimpex libpano13

LOCAL_MODULE := pto_gen

include $(BUILD_EXECUTABLE)

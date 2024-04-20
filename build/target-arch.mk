ANDROID_TEMPLATE_TARGETS := ANDROID_GENERIC

OS_TARGETS += $(ANDROID_TEMPLATE_TARGETS)

TARGET ?= $(DEFAULT_TARGET)

ifneq ($(filter $(TARGET),$(ANDROID_TEMPLATE_TARGETS)),)
TARGET_DIR = $(ANDROID_NDK_ROOT)/sysroot/

PLATFORM := android
VENDOR := android-template

# By default, search through all service-provider directories
# starting with "local"
SERVICE_PROVIDERS ?= local ALL

# Default image deployment profile which must be defined in one of the cloned
# service-provider directories. The "local" profile is found in the "local"
# service provider repository.
export IMAGE_DEPLOYMENT_PROFILE ?= local

KCONFIG_TARGET ?= $(VENDOR_DIR)/kconfig/targets/$(TARGET)
ARCH_MK = $(PLATFORM_DIR)/build/$(PLATFORM).mk
endif

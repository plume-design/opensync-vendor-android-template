##############################################################################
#
# OSP layer library override
#
##############################################################################

UNIT_CFLAGS += -I$(OVERRIDE_DIR)/inc
UNIT_SRC_TOP += $(if $(CONFIG_OSP_UNIT_ANDROID), $(OVERRIDE_DIR)/src/osp_unit_android.c)
ifdef CONFIG_MANAGER_BLEM
UNIT_SRC_TOP += $(if $(CONFIG_OSP_BLE_ANDROID), $(OVERRIDE_DIR)/src/ble/osp_ble_android.c)
endif # CONFIG_MANAGER_BLEM

UNIT_SRC := $(filter-out src/osp_sec_key.c,$(UNIT_SRC))
UNIT_SRC_TOP += $(OVERRIDE_DIR)/src/osp_sec_key.c

UNIT_LDFLAGS := -lzmq
UNIT_EXPORT_LDFLAGS := $(UNIT_LDFLAGS)

UNIT_DEPS += platform/android/src/lib/osandroid

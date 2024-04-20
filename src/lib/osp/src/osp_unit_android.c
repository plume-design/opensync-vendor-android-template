#include <stdalign.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <zmq.h>

#include "build_version.h"
#include "json_util.h"
#include "log.h"
#include "os_nif.h"
#include "util.h"

#include "osandroid_ipc.h"
#include "osp_unit.h"

static bool osp_common_req(const char *fun, char *buff, size_t buffsz)
{
    char recv_buf[ZMQ_MSG_MAX_LEN];
    json_t *req_msg = NULL;
    json_t *root = NULL;
    bool ret = false;

    static bool has_ipc_initialized = false;
    if (!has_ipc_initialized)
    {
        osandroid_ipc_requester_init();
        has_ipc_initialized = true;
    }

    req_msg = osandroid_ipc_build_header(fun);
    if (req_msg == NULL)
    {
        LOGE("OSP: build IPC request JSON failed");
        goto error;
    }

    ret = osandroid_ipc_request(req_msg, recv_buf, ZMQ_MSG_MAX_LEN);
    if (!ret)
    {
        LOGE("OSP: IPC request error");
        goto error;
    }

    LOGI("OSP: IPC output: %s", recv_buf);

    json_error_t error;

    root = json_loads(recv_buf, 0, &error);
    if (!root)
    {
        LOGE("OSP: JSON parsing error");
        goto error;
    }

    json_t *params_array = json_object_get(root, "params");
    json_t *first_element = json_array_get(params_array, 0);
    json_t *json_buff = json_object_get(first_element, "buff");
    if (json_buff == NULL)
    {
        LOGE("OSP: object 'buff' not found");
        goto error;
    }
    if (!json_is_string(json_buff))
    {
        LOGE("OSP: object 'buff' is not a string");
        goto error;
    }

    strscpy(buff, json_string_value(json_buff), buffsz);
    ret = true;

end:
    if (req_msg != NULL) json_decref(req_msg);
    if (root != NULL) json_decref(root);

    return ret;

error:
    ret = false;
    goto end;
}

bool osp_unit_serial_get(char *buff, size_t buffsz)
{
    return osp_common_req(__func__, buff, buffsz);
}

bool osp_unit_id_get(char *buff, size_t buffsz)
{
    return osp_common_req(__func__, buff, buffsz);
}

bool osp_unit_model_get(char *buff, size_t buffsz)
{
    return osp_common_req(__func__, buff, buffsz);
}

bool osp_unit_sku_get(char *buff, size_t buffsz)
{
    return osp_common_req(__func__, buff, buffsz);
}

bool osp_unit_hw_revision_get(char *buff, size_t buffsz)
{
    return osp_common_req(__func__, buff, buffsz);
}

bool osp_unit_platform_version_get(char *buff, size_t buffsz)
{
    return osp_common_req(__func__, buff, buffsz);
}

bool osp_unit_sw_version_get(char *buff, size_t buffsz)
{
    return osp_common_req(__func__, buff, buffsz);
}

bool osp_unit_vendor_name_get(char *buff, size_t buffsz)
{
    return osp_common_req(__func__, buff, buffsz);
}

bool osp_unit_vendor_part_get(char *buff, size_t buffsz)
{
    return osp_common_req(__func__, buff, buffsz);
}

bool osp_unit_manufacturer_get(char *buff, size_t buffsz)
{
    return osp_common_req(__func__, buff, buffsz);
}

bool osp_unit_factory_get(char *buff, size_t buffsz)
{
    return osp_common_req(__func__, buff, buffsz);
}

bool osp_unit_mfg_date_get(char *buff, size_t buffsz)
{
    return osp_common_req(__func__, buff, buffsz);
}

bool osp_unit_dhcpc_hostname_get(void *buff, size_t buffsz)
{
    return osp_common_req(__func__, buff, buffsz);
}

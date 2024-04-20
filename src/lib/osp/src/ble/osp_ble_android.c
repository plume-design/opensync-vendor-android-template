#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "json_util.h"
#include "log.h"
#include "util.h"

#include "osandroid_ipc.h"
#include "osp_ble.h"
#include "osp_unit.h"

bool osp_ble_init(
        struct ev_loop *loop,
        osp_ble_on_device_connected_cb_t on_device_connected_cb,
        osp_ble_on_device_disconnected_cb_t on_device_disconnected_cb,
        osp_ble_on_pairing_status_cb_t on_pairing_status_cb,
        osp_ble_on_gatt_json_cb_t on_gatt_json_cb)
{
    (void)loop;
    (void)on_device_connected_cb;
    (void)on_device_disconnected_cb;
    (void)on_pairing_status_cb;
    (void)on_gatt_json_cb;

    return true;
}

void osp_ble_close(void)
{
}

bool osp_ble_get_service_uuid(uint16_t *uuid)
{
    (void)uuid;

    return true;
}

bool osp_ble_set_device_name(const char *device_name)
{
    (void)device_name;

    return true;
}

bool osp_ble_set_scan_response_data(const uint8_t payload[31], uint8_t len)
{
    (void)payload;
    (void)len;

    return true;
}

bool osp_ble_set_connectable(bool enabled)
{
    (void)enabled;

    return true;
}

bool osp_ble_calculate_pairing_passkey(const uint8_t token[4], uint32_t *passkey)
{
    (void)token;
    (void)passkey;

    return true;
}

bool osp_ble_set_pairing_passkey(uint32_t passkey)
{
    (void)passkey;

    return true;
}

bool osp_ble_set_gatt_json(const char *value, uint16_t len)
{
    (void)value;
    (void)len;

    return true;
}

bool osp_ble_set_advertising_params(bool enabled, bool sr_enabled, uint16_t interval_ms)
{
    int ret;
    char recv_buf[ZMQ_MSG_MAX_LEN] = "";

    json_t *js = NULL;
    js = json_pack(
            "{s:s, s:b, s:b, s:i}",
            "api",
            __func__,
            "mode",
            enabled,
            "connectable",
            sr_enabled,
            "interval_millis",
            interval_ms);

    ret = osandroid_ipc_request(js, recv_buf, ZMQ_MSG_MAX_LEN);

    if (js)
    {
        json_decref(js);
    }

    return ret;
}

bool osp_ble_set_advertising_data(const uint8_t payload[31], uint8_t len)
{
    int ret;
    char recv_buf[ZMQ_MSG_MAX_LEN] = "";

    /* Get BLE Advertising MsgType & Msg, only support for OpenSync 4.4+ */
    uint8_t msg_type[1];
    uint8_t msg[6];

    char msg_type_hex[sizeof(msg_type) * 2 + 1] = "";
    char msg_hex[sizeof(msg) * 2 + 1] = "";

    msg_type[0] = payload[len - 7];
    for (size_t i = len - 6, j = 0; i < len; i++, j++)
    {
        msg[j] = payload[i];
    }

    /* Convert to hex */
    bin2hex((uint8_t *)&msg_type, sizeof(msg_type), msg_type_hex, sizeof(msg_type_hex));
    bin2hex((uint8_t *)&msg, sizeof(msg), msg_hex, sizeof(msg_hex));

    json_t *js = NULL;
    js = json_pack("{s:s, s:s, s:s}", "api", __func__, "msgType", msg_type_hex, "msg", msg_hex);

    ret = osandroid_ipc_request(js, recv_buf, ZMQ_MSG_MAX_LEN);

    if (js)
    {
        json_decref(js);
    }

    return ret;
}

#include "bluetooth.h"
#include "esp_bt.h"
#include "esp_bt_main.h"
#include "esp_log.h"

#define TAG "BLUETOOTH_SNIFFER"

void bluetooth_sniffer_init(esp_gap_ble_cb_t callback)
{
    esp_bt_controller_mem_release(ESP_BT_MODE_CLASSIC_BT);
    esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
    esp_bt_controller_init(&bt_cfg);
    esp_bt_controller_enable(ESP_BT_MODE_BLE);

    esp_bluedroid_init();
    esp_bluedroid_enable();
    esp_ble_gap_register_callback(callback);

    esp_ble_scan_params_t ble_scan_params = {
        .scan_type = BLE_SCAN_TYPE_PASSIVE,
        .own_addr_type = BLE_ADDR_TYPE_PUBLIC,
        .scan_filter_policy = BLE_SCAN_FILTER_ALLOW_ALL,
        .scan_interval = 0x50,
        .scan_window = 0x30};
    esp_ble_gap_set_scan_params(&ble_scan_params);
}

void bluetooth_sniffer_default_callback_handler(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param)
{
    if (event == ESP_GAP_BLE_SCAN_PARAM_SET_COMPLETE_EVT)
    {
        esp_ble_gap_start_scanning(0);
        return;
    }

    if (event == ESP_GAP_BLE_SCAN_RESULT_EVT)
    {
        if (param->scan_rst.search_evt == ESP_GAP_SEARCH_INQ_RES_EVT)
        {
            ESP_LOGI(TAG, "Device found: Addr %02x:%02x:%02x:%02x:%02x:%02x, RSSI %d",
                     param->scan_rst.bda[0], param->scan_rst.bda[1], param->scan_rst.bda[2],
                     param->scan_rst.bda[3], param->scan_rst.bda[4], param->scan_rst.bda[5],
                     param->scan_rst.rssi);
        }
    }
}

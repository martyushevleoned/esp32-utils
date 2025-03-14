#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include "esp_gap_ble_api.h"

void bluetooth_sniffer_init(esp_gap_ble_cb_t callback);

void bluetooth_sniffer_default_callback_handler(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param);

#endif
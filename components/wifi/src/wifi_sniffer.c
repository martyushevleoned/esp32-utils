#include "wifi.h"
#include "esp_log.h"

#define TAG "WIFI_SNIFFER"

void wifi_sniffer_init(wifi_promiscuous_cb_t handler)
{
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_NULL));
    ESP_ERROR_CHECK(esp_wifi_set_promiscuous(true));
    ESP_ERROR_CHECK(esp_wifi_set_promiscuous_rx_cb(handler));
    ESP_ERROR_CHECK(esp_wifi_start());
}

void wifi_sniffer_default_packet_handler(void *buff, wifi_promiscuous_pkt_type_t type)
{
    if (type == WIFI_PKT_MGMT || type == WIFI_PKT_DATA || type == WIFI_PKT_CTRL)
    {
        const wifi_promiscuous_pkt_t *pkt = (wifi_promiscuous_pkt_t *)buff;
        const uint8_t *mac_src = pkt->payload + 10;
        const uint8_t *mac_dst = pkt->payload + 4;
        ESP_LOGI(TAG, "Packet received: len=%d, RSSI=%d, timestamp: %u",
                 pkt->rx_ctrl.sig_len, pkt->rx_ctrl.rssi, pkt->rx_ctrl.timestamp);
        ESP_LOGI(TAG, "Src MAC: %02X:%02X:%02X:%02X:%02X:%02X -> Dst MAC: %02X:%02X:%02X:%02X:%02X:%02X",
                 mac_src[0], mac_src[1], mac_src[2], mac_src[3], mac_src[4], mac_src[5],
                 mac_dst[0], mac_dst[1], mac_dst[2], mac_dst[3], mac_dst[4], mac_dst[5]);
    }
}

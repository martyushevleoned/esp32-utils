#include "wifi_sniffer.h"
#include "esp_log.h"

static const char *TAG = "wifi_sniffer";

void wifi_sniffer_packet_handler(void *buff, wifi_promiscuous_pkt_type_t type)
{
    if (type == WIFI_PKT_MGMT || type == WIFI_PKT_DATA || type == WIFI_PKT_CTRL)
    {
        const wifi_promiscuous_pkt_t *pkt = (wifi_promiscuous_pkt_t *)buff;
        const uint8_t *mac_src = pkt->payload + 10; // MAC-адрес отправителя
        const uint8_t *mac_dst = pkt->payload + 4;  // MAC-адрес получателя
        ESP_LOGI(TAG, "Packet received: len=%d, RSSI=%d, Type=%d, Channel=%d, Rate=%d, Aggregation=%d",
                 pkt->rx_ctrl.sig_len, pkt->rx_ctrl.rssi, type,
                 pkt->rx_ctrl.channel, pkt->rx_ctrl.rate, pkt->rx_ctrl.aggregation);
        ESP_LOGI(TAG, "Src MAC: %02X:%02X:%02X:%02X:%02X:%02X -> Dst MAC: %02X:%02X:%02X:%02X:%02X:%02X",
                 mac_src[0], mac_src[1], mac_src[2], mac_src[3], mac_src[4], mac_src[5],
                 mac_dst[0], mac_dst[1], mac_dst[2], mac_dst[3], mac_dst[4], mac_dst[5]);
        ESP_LOGI(TAG, "Timestamp: %u", pkt->rx_ctrl.timestamp);
    }
}

void app_main()
{
    wifi_hardware_init();
    wifi_sniffer_init(&wifi_sniffer_packet_handler);
}
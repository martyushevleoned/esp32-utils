#include <stdio.h>
#include "utils.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#define TAG "UTILS"

void delay(unsigned long long millis) {
    vTaskDelay(pdMS_TO_TICKS(millis));
}
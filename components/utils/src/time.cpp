#include "time.h"

void delay_millis(unsigned long long millis) {
    vTaskDelay(pdMS_TO_TICKS(millis));
}

void delay_seconds(unsigned long long seconds) {
    delay_millis(seconds * 1000);
}
#include "esp_sleep.h"

void setup() {
  esp_sleep_enable_timer_wakeup(60 * 1000000);
  esp_deep_sleep_start();
}

void loop() {
}
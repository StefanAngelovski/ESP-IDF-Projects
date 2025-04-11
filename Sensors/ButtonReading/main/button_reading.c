#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define BUTTON_GPIO 4  // Button connected to GPIO 4

void app_main() {
  gpio_config_t io_conf;
  io_conf.intr_type = GPIO_INTR_DISABLE;      // Disable interrupt
  io_conf.mode = GPIO_MODE_INPUT;             // Set as input
  io_conf.pin_bit_mask = (1ULL << BUTTON_GPIO); // Configure GPIO 4
  io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE; // Disable pull-down
  io_conf.pull_up_en = GPIO_PULLUP_ENABLE;    // Enable pull-up resistor
  gpio_config(&io_conf);

  while (1) {
    int buttonState = gpio_get_level(BUTTON_GPIO);  // Read the button state

    if (buttonState == 0) {
      printf("Button pressed!\n");  // Print message if button is pressed
    } else {
      printf("Button not pressed.\n");  // Print message if button is not pressed
    }

    vTaskDelay(100 / portTICK_PERIOD_MS);  // Add a small delay to debounce the button
  }
}
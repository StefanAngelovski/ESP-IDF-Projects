#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

void app_main(void)
{
    int counter = 0;
    while (true) {
        printf("Hello World! Counter: %d\n", counter++);
        vTaskDelay(1000 / portTICK_PERIOD_MS); // Delay for 1 second
    }
}
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "../components/Servo_360/include/Servo_360.h"

void app_main() {
    servo_init();

    while(true) {
        printf("Full speed clockwise\n");
        set_servo_speed(-100);  // Full speed clockwise
        vTaskDelay(2000 / portTICK_PERIOD_MS);
        
        printf("Stop\n");
        set_servo_speed(0);     // Stop
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        
        printf("Full speed counter-clockwise\n");
        set_servo_speed(100);   // Full speed counter-clockwise
        vTaskDelay(2000 / portTICK_PERIOD_MS);
        
        printf("Stop\n");
        set_servo_speed(0);     // Stop
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "driver/adc.h"

unsigned int humidity_value = 0;

void app_main(void)
{
    adc1_config_channel_atten(ADC1_CHANNEL_3, ADC_ATTEN_DB_12); //GPIO4
    adc1_config_width(ADC_WIDTH_BIT_12);

    while(true)
    {
        humidity_value = adc1_get_raw(ADC1_CHANNEL_3); 
        printf("Humidity Value is %d\n", humidity_value); // Goes inverse

        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}
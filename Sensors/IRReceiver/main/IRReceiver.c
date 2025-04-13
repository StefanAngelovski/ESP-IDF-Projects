#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/rmt.h"

#define RMT_RX_CHANNEL  RMT_CHANNEL_0
#define RMT_RX_GPIO     GPIO_NUM_4
#define NEC_DECODE_MARGIN 200  // Tolerance for pulse timing

void app_main(void)
{
    // Configure RMT receiver
    rmt_config_t rmt_rx_config = RMT_DEFAULT_CONFIG_RX(RMT_RX_GPIO, RMT_RX_CHANNEL);
    rmt_rx_config.clk_div = 80;  // 1 MHz clock (80 MHz / 80)
    
    rmt_config(&rmt_rx_config);
    rmt_driver_install(RMT_RX_CHANNEL, 1000, 0);

    // Set NEC protocol decoding
    rmt_nec_rx_config_t nec_config = {
        .filter_en = true,
        .filter_ticks_thresh = 100,
        .idle_threshold = rmt_rx_config.rx_config.idle_threshold
    };
    rmt_nec_rx_channel_config(RMT_RX_CHANNEL, &nec_config);

    printf("KY-022 Infrared Receiver Ready\n");

    while(1) {
        rmt_rx_start(RMT_RX_CHANNEL, true);
        
        RingbufHandle_t rb = NULL;
        rmt_get_ringbuf_handle(RMT_RX_CHANNEL, &rb);
        
        rmt_item32_t* items = NULL;
        size_t rx_size = 0;
        
        // Wait for IR data (max 1 second)
        items = (rmt_item32_t*) xRingbufferReceive(rb, &rx_size, pdMS_TO_TICKS(1000));
        
        if(items) {
            // Decode NEC protocol
            uint16_t addr = 0;
            uint16_t cmd = 0;
            
            if(rmt_nec_decode(RMT_RX_CHANNEL, items, rx_size / 4, &addr, &cmd) == ESP_OK) {
                printf("Received NEC code: 0x%04X (Addr: 0x%04X)\n", cmd, addr);
            }
            
            vRingbufferReturnItem(rb, (void*) items);
        }
        
        rmt_rx_stop(RMT_RX_CHANNEL);
    }
}
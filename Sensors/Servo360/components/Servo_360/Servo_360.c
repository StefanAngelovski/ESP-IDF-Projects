#include "include/Servo_360.h"
#include "driver/ledc.h"
#include "esp_err.h"
#include "sdkconfig.h"

// Duty cycle limits
#define DUTY_MIN       410
#define DUTY_NEUTRAL   614
#define DUTY_MAX       819

void servo_init(void) {
    // Timer configuration 
    ledc_timer_config_t timer_cfg = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .duty_resolution = LEDC_TIMER_13_BIT,
        .timer_num = LEDC_TIMER_0,
        .freq_hz = 50,
        .clk_cfg = LEDC_AUTO_CLK
    };
    ESP_ERROR_CHECK(ledc_timer_config(&timer_cfg));

    // Channel configuration
    ledc_channel_config_t ch_cfg = {
        .gpio_num = GPIO_NUM_4,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = LEDC_CHANNEL_0,
        .timer_sel = LEDC_TIMER_0,
        .duty = 0,
        .hpoint = 0
    };
    ESP_ERROR_CHECK(ledc_channel_config(&ch_cfg));
}

void set_servo_speed(int speed_percent) {
    uint32_t duty = DUTY_NEUTRAL;

    if (speed_percent > 0) {
        // Counterclockwise (increase duty)
        duty = DUTY_NEUTRAL + (speed_percent * (DUTY_MAX - DUTY_NEUTRAL) / 100);
    } else if (speed_percent < 0) {
        // Clockwise (decrease duty)
        duty = DUTY_NEUTRAL + (speed_percent * (DUTY_NEUTRAL - DUTY_MIN) / 100);
    }

    // Clamp duty value to safe limits
    duty = (duty < DUTY_MIN) ? DUTY_MIN : (duty > DUTY_MAX) ? DUTY_MAX : duty;

    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, duty);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
}
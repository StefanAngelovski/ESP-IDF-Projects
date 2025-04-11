#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void servo_init(void);
void set_servo_speed(int speed_percent);

#ifdef __cplusplus
}
#endif
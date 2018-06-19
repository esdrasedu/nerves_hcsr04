#ifndef SYS_COMMON_H
#define SYS_COMMON_H

#include <stdint.h>

#define SUCCESS 0
#define ERROR_INIT_GPIO -1
#define TIMEOUT_PING -2
#define TIMEOUT_PONG -3

void delay_micro(uint32_t micro);
uint32_t micros(void);
uint32_t diff_micros(uint32_t millis_left);

#endif

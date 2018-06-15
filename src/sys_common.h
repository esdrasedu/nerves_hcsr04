#ifndef SYS_COMMON_H
#define SYS_COMMON_H

#include <stdint.h>

#define SUCCESS 0
#define ERROR_INIT_GPIO -1
#define TIMEOUT_PING -2
#define TIMEOUT_PONG -3

void busy_wait_milliseconds(uint32_t millis);
void sleep_milliseconds(uint32_t millis);
void set_max_priority(void);
void set_default_priority(void);
void initialiseEpoch(void);
extern unsigned int micros(void);

#endif

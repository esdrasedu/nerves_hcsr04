#ifndef SYS_COMMON_H
#define SYS_COMMON_H

#include <stdint.h>

#define SUCCESS 0
#define ERROR_INIT_GPIO -1
#define TIMEOUT_PING -2
#define TIMEOUT_PONG -3

uint32_t micros(void);

#endif

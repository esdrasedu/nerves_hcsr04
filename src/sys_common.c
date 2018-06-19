#include <errno.h>
#include <sched.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

#include "sys_common.h"

void delay_micro(uint32_t micro) {
  struct timespec sleep;
  sleep.tv_sec = micro / 1000000;
  sleep.tv_nsec = (micro % 1000000) * 1000000L;
  while (clock_nanosleep(CLOCK_MONOTONIC, 0, &sleep, &sleep) && errno == EINTR);
}

uint32_t micros(void) {
  return (((double)clock()) / CLOCKS_PER_SEC) * 1000000;
}

uint32_t diff_micros(uint32_t micros_left) {
  return micros() - micros_left;
}

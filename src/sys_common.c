#include <errno.h>
#include <sched.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

#include "sys_common.h"

uint32_t micros(void) {
  return (((double)clock()) / CLOCKS_PER_SEC) * 1000000;
}

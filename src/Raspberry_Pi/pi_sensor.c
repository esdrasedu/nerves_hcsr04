#include "pi_sensor.h"
#include "pi_mmio.h"

#include <time.h>

int pi_sensor(int echo, int trig, float* distance) {

  time_t ping, pong;

  *distance = 0.0f;

  if (pi_mmio_init() < 0) {
    return ERROR_INIT_GPIO;
  }

  pi_mmio_set_input(echo);
  pi_mmio_set_output(trig);

  set_max_priority();

  pi_mmio_set_low(trig);
  sleep_milliseconds(1000);

  pi_mmio_set_high(trig);

  busy_wait_milliseconds(10);

  pi_mmio_set_low(trig);

	while (pi_mmio_input(echo) == 0) {}

  ping = time(NULL);

	while (pi_mmio_input(echo) == 1) {}

	pong = time(NULL);

  set_default_priority();

	*distance = (float) difftime(pong, ping) * 0.017150;

	return SUCCESS;
}

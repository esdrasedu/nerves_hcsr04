#include "pi_sensor.h"
#include "pi_mmio.h"

int pi_sensor(int echo, int trig, float* distance) {

	long ping = 0;
	long pong = 0;
  long timeout = 500000; // 0.5 sec ~ 171 m

  *distance = 0.0f;

  initialiseEpoch();

  if (pi_mmio_init() < 0) {
    return ERROR_INIT_GPIO;
  }

  pi_mmio_set_input(echo);
  pi_mmio_set_output(trig);

  set_max_priority();

  pi_mmio_set_low(trig);
  sleep_milliseconds(500);

  pi_mmio_set_high(trig);

  busy_wait_milliseconds(10);

  pi_mmio_set_low(trig);

	while (pi_mmio_input(echo) == 0 && micros() < timeout) {}

	if (micros() > timeout) {
    set_default_priority();
		return TIMEOUT_PING;
	}

  ping = micros();

	while (pi_mmio_input(echo) == 1 && micros() < timeout) {}

	if (micros() > timeout) {
    set_default_priority();
		return TIMEOUT_PONG;
	}

	pong = micros();

  set_default_priority();

	*distance = (float) (pong - ping) * 0.017150;

	return SUCCESS;
}

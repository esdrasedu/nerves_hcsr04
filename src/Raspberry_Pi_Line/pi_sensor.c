#include <stdio.h>
#include "pi_sensor.h"
#include "pi_mmio.h"

int pi_sensor(int echo, int trig, float* distance) {

  uint32_t started, ping, pong;
  uint32_t timeout = 500000; // 0.5 sec = 171m

  *distance = 0.0f;

  printf("Init.\n");
  if (pi_mmio_init() != MMIO_SUCCESS) {
    return ERROR_INIT_GPIO;
  }
  printf("Setup pins.\n");

  pi_mmio_set_input(echo);
  pi_mmio_set_output(trig);
  printf("Low trig.\n");
  pi_mmio_set_low(trig);
  delay_micro(2);

  printf("High trig.\n");
  pi_mmio_set_high(trig);

  delay_micro(10);

  printf("Low trig again.\n");
  pi_mmio_set_low(trig);

  started = micros();
  printf("Started: %d.\n", started);

	while (pi_mmio_input(echo) == 0 && diff_micros(started) < timeout) {}

  uint32_t diff = diff_micros(started);
  printf("Call Ping %d.\n", diff);
	if (diff > timeout) { return TIMEOUT_PING; }

  ping = micros();

  printf("Ping: %d.\n", ping);
	while (pi_mmio_input(echo) == 1 && diff_micros(ping) < timeout) {}

  printf("Call Pong.\n");
	if (diff_micros(ping) > timeout) { return TIMEOUT_PONG; }

	pong = micros();

  printf("Pong: %d.\n", pong);
  //set_default_priority();

	*distance = (float) (pong - ping) * 0.00170145; // (((340.29 / 2) / 1000) / 100)

	return SUCCESS;
}

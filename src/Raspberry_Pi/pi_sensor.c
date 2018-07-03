#include <stdio.h>
#include "pi_sensor.h"
#include "bcm2835.h"
#include "gpio_pin.h"

int pi_sensor(int echo_number, int trig_number, float* distance) {

  uint32_t started, ping, pong;
  uint32_t timeout = 500000; // 0.5 sec = 85m

  *distance = 0.0f;

  int echo = gpio_number(echo_number);
  int trig = gpio_number(trig_number);

  if (!bcm2835_init())
    return ERROR_INIT_GPIO;

  bcm2835_gpio_fsel(echo, BCM2835_GPIO_FSEL_INPT);
  bcm2835_gpio_fsel(trig, BCM2835_GPIO_FSEL_OUTP);
  bcm2835_gpio_write(trig, LOW);
  bcm2835_delay(2);

  bcm2835_gpio_write(trig, HIGH);

  bcm2835_delay(10);

  bcm2835_gpio_write(trig, LOW);

  started = micros();

	while (bcm2835_gpio_lev(echo) == 0 && (micros() - started) < timeout) {}

  uint32_t diff = micros() - started;

  if (diff > timeout) { return TIMEOUT_PING; }

  ping = micros();

	while (bcm2835_gpio_lev(echo) == 1 && (micros() - ping) < timeout) {}

	if ((micros() - ping) > timeout) { return TIMEOUT_PONG; }

	pong = micros();

  bcm2835_close();

	*distance = ((float) (pong - ping)) * 0.0170145;
	// (((( (pong - ping)  / 2 ) / 1000) / 1000) * 340.29) * 100

	return SUCCESS;
}

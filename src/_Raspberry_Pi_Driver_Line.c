#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "Raspberry_Pi_Line/pi_sensor.h"

typedef unsigned char byte;

int main(int argc, char *argv[]) {

  if (argc != 3) {
    fprintf(stderr, "Usage: %s [GPIO_ECHO] [GPIO_TRIG] \n", argv[0]);
    exit(EXIT_FAILURE);
  }

  int echo = atoi(argv[1]);
  int trig = atoi(argv[2]);

  float distance = 0;

  printf("Echo: %i .\n", echo);
  printf("Trig: %i .\n", trig);

  int result = pi_sensor(echo, trig, &distance);

  if(result == 0){
    printf("Distance: %.2f cm.\n", distance);
  } else {
    printf("Error %i.\n", result);
  }

  return 0;
}

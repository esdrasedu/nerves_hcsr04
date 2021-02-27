#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "erl_common.c"
#include "ei.h"

#include "Raspberry_Pi/pi_sensor.h"

typedef unsigned char byte;

int main(int argc, char *argv[])
{

  if (argc != 3)
  {
    fprintf(stderr, "Usage: %s [GPIO_ECHO] [GPIO_TRIG] \n", argv[0]);
    exit(EXIT_FAILURE);
  }

  ei_init();

  int echo = atoi(argv[1]);
  int trig = atoi(argv[2]);

  byte input[100];
  ei_x_buff output;

  while (read_cmd(input) > 0)
  {
    float distance = 0;
    int result = pi_sensor(echo, trig, &distance);

    ei_x_new(&output);

    if (result == SUCCESS)
    {
      ei_x_format(&output,
                  "{~a,~i,~i,~f}",
                  "ok",
                  echo,
                  trig,
                  distance);
    }
    else
    {
      ei_x_format(&output,
                  "{~a,~i,~i,~i}",
                  "error",
                  echo,
                  trig,
                  result);
    }

    write_cmd(output.buff, output.index);

    ei_x_free(&output);
  }

  return 1;
}

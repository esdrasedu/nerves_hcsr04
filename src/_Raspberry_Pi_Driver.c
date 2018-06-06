#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "erl_comm.c"
#include "erl_interface.h"
#include "ei.h"

#include "Raspberry_Pi/pi_sensor.h"

typedef unsigned char byte;

int main(int argc, char *argv[]) {

  if (argc != 3) {
    fprintf(stderr, "Usage: %s [GPIO_ECHO] [GPIO_TRIG] \n", argv[0]);
    exit(EXIT_FAILURE);
  }

  int echo = atoi(argv[1]);
  int trig = atoi(argv[2]);

  ETERM * arr[4], *tuple;
  unsigned char buf[BUFSIZ];

  erl_init(NULL, 0);

  for(;;){

    float distance = 0;
    int result = pi_sensor(echo, trig, &distance);

    if(result == 0){

      arr[0] = erl_mk_atom("ok");
      arr[1] = erl_mk_int(echo);
      arr[2] = erl_mk_int(trig);
      arr[3] = erl_mk_float(distance);

      tuple  = erl_mk_tuple(arr, 4);

      erl_encode(tuple, buf);

      write_cmd(buf, erl_term_len(tuple));

      erl_free_term(tuple);
    } else {
      arr[0] = erl_mk_atom("error");
      arr[1] = erl_mk_int(result);

      tuple  = erl_mk_tuple(arr, 2);

      erl_encode(tuple, buf);

      write_cmd(buf, erl_term_len(tuple));

      erl_free_term(tuple);
    }
  }

  return 1;
}

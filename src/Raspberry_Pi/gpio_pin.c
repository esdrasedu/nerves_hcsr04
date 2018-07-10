#include "bcm2835.h"

int gpio_number( int pin ) {

  switch ( pin ) {
  case 2:
    return RPI_V2_GPIO_P1_03;
  case 3:
    return RPI_V2_GPIO_P1_05;
  case 4:
    return RPI_V2_GPIO_P1_07;
  case 14:
    return RPI_V2_GPIO_P1_08;
  case 15:
    return RPI_V2_GPIO_P1_10;
  case 17:
    return RPI_V2_GPIO_P1_11;
  case 18:
    return RPI_V2_GPIO_P1_12;
  case 27:
    return RPI_V2_GPIO_P1_13;
  case 22:
    return RPI_V2_GPIO_P1_15;
  case 23:
    return RPI_V2_GPIO_P1_16;
  case 24:
    return RPI_V2_GPIO_P1_18;
  case 10:
    return RPI_V2_GPIO_P1_19;
  case 9:
    return RPI_V2_GPIO_P1_21;
  case 25:
    return  RPI_V2_GPIO_P1_22;
  case 11:
    return RPI_V2_GPIO_P1_23;
  case 8:
    return RPI_V2_GPIO_P1_24;
  case 7:
    return RPI_V2_GPIO_P1_26;
  case 5:
    return RPI_V2_GPIO_P1_29;
  case 6:
    return RPI_V2_GPIO_P1_31;
  case 12:
    return RPI_V2_GPIO_P1_32;
  case 13:
    return RPI_V2_GPIO_P1_33;
  case 19:
    return RPI_V2_GPIO_P1_35;
  case 16:
    return RPI_V2_GPIO_P1_36;
  case 26:
    return RPI_V2_GPIO_P1_37;
  case 20:
    return RPI_V2_GPIO_P1_38;
  case 21:
    return RPI_V2_GPIO_P1_40;
  }

  return 0;
}

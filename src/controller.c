/*
  RaspberryPi Radicon with Xively

  Coded by Yasuhiro ISHII

  This software is distributed under the license of Apache2.0
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <libfirmata.h>
#include <port_list.h>
#include "controller.h"

#define PIN_GAMEPAD_ANALOG_X 14
#define PIN_GAMEPAD_ANALOG_Y 15

#if 0
int main(int argc, char *argv[]){
    struct GAMEPAD gp;
   
    init_gamepad();
    
    while(1){
	capture_gamepad(&gp);
	printf("x = %d,y = %d\n",gp.analog_x,gp.analog_y);
    }
    

    firmata_close();
    return 0;
}
#endif

int init_gamepad(char* device)
{
    firmata_pre_init();
    firmata_init(device,57600);

    set_pin_mode(PIN_GAMEPAD_ANALOG_X,MODE_ANALOG);
    set_pin_mode(PIN_GAMEPAD_ANALOG_Y,MODE_ANALOG);

    return(1);
}

int capture_gamepad(struct GAMEPAD* pad)
{
    pad->analog_x = get_pin_value(PIN_GAMEPAD_ANALOG_X);
    pad->analog_y = get_pin_value(PIN_GAMEPAD_ANALOG_Y);

    return(1);
}

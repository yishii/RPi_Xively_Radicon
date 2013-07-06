#include <stdio.h>              // printf(), fgets()
#include <stdlib.h>             // exit()
#include <string.h>             // strtok() and strcmp()
#include <unistd.h>             // usleep();

#include <libfirmata.h>         // firmata_functions.
#include <port_list.h>          // port list

#define PIN_GAMEPAD_ANALOG_X 14
#define PIN_GAMEPAD_ANALOG_Y 15

struct GAMEPAD {
    int analog_x;
    int analog_y;
};

int init_gamepad(void);
int capture_gamepad(struct GAMEPAD* pad);


int main(int argc, char *argv[]){
    struct GAMEPAD gp;

    if(argc != 2)
        argv[1] = "/dev/ttyACM0";
    
    firmata_pre_init();

    /* Open the device */
    int status = firmata_init(argv[1], 57600);
    if(status == 1) {
	printf("error!\n");
        firmata_close();
        exit(status);
    }
    
    init_gamepad();
    
    while(1){
	capture_gamepad(&gp);
	printf("x = %d,y = %d\n",gp.analog_x,gp.analog_y);
    }
    

    firmata_close();
    return 0;
}

int init_gamepad(void)
{
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

/*
  RaspberryPi Radicon with Xively

  Coded by Yasuhiro ISHII

  This software is distributed under the license of Apache2.0
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <xively.h>
#include <xi_helpers.h>
#include <xi_err.h>
#include "conf_xively.h"
#include "controller.h"

bool open_xively(char* api_key,char* feed_id,xi_context_t** xi_context);
bool update_xively(xi_context_t* xi_context,char* api_key,char* feed_id,char* datastream_id,int val);
bool close_xively(xi_context_t* xi_context);

int main(void)
{
  xi_context_t* xi_ctx = NULL;
  struct GAMEPAD pad;
  bool result;

  // need to modify if the device name is wrong with the target you using
  init_gamepad("/dev/ttyACM0");

  result = open_xively(XIVELY_API_KEY,XIVELY_FEED_ID,&xi_ctx);
  if(result == false){
    printf("open xively failed\n");
    return(-1);
  }

  while(1){
    capture_gamepad(&pad);
    printf("x = %d,y = %d\n",pad.analog_x,pad.analog_y);
    update_xively(xi_ctx,XIVELY_API_KEY,XIVELY_FEED_ID,"AN_X",pad.analog_x);
    update_xively(xi_ctx,XIVELY_API_KEY,XIVELY_FEED_ID,"AN_Y",pad.analog_y);
  }
}

bool open_xively(char* api_key,char* feed_id,xi_context_t** xi_context)
{
    *xi_context = xi_create_context(XI_HTTP,api_key,atoi(feed_id));

    if(*xi_context == 0){
        return false;
    }
    return(true);
}

bool update_xively(xi_context_t* xi_context,char* api_key,char* feed_id,char* datastream_id,int val)
{
    xi_datapoint_t datapoint;

    if(xi_context == 0){
      printf("FAIL!\n");
      return false;
    }

    xi_set_value_i32( &datapoint,val);

    {
        time_t timer = 0;
        time( &timer );
        datapoint.timestamp.timestamp = timer;
    }

    xi_datastream_update( xi_context
            , atoi( feed_id ), datastream_id
			  , &datapoint/*.value*/ );

    printf( "err: %d - %s\n", ( int ) xi_get_last_error(), xi_get_error_string( xi_get_last_error() ) );


    return(true);
}

bool close_xively(xi_context_t* xi_context)
{
    xi_delete_context(xi_context);

    return(true);
}



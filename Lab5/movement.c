/*
 *  Movement control for the roomba.  Enables forward movement in centimeters, left and right control in degrees, and bump
 *
 *  @author: Jacob Vaughn, Nick Lorenz
 *  @date:  Feb 7, 2019
 */

#include "open_interface.h"
#include "lcd.h"

void move_forward(oi_t *sensor_data, int millimeter)
{

    int sum = 0;
    oi_setWheels(500, 450); //move forward full speed
    while (sum < millimeter) //Runs till distance in cm is reached
    {
        oi_update(sensor_data);
        sum += sensor_data -> distance;

       // lcd_printf("%d", sum);  //Prints distance moved to lcd
    }
    oi_setWheels(0, 0); //stop
}

void turn_right(oi_t *sensor_data, int degrees){

    int sum = 0;
    oi_setWheels(-100, 100); //move forward full speed
    while (sum > -(degrees - 5)) //Runs till distance in cm is reached
    {
        oi_update(sensor_data);
        sum += sensor_data -> angle;

    }
    oi_setWheels(0, 0); //stop
}

void turn_left(oi_t *sensor_data, int degrees){

    int sum = 0;
    oi_setWheels(100, -100); //move forward full speed
    while (sum < (degrees - 5)) //Runs till distance in cm is reached
    {
        oi_update(sensor_data);
        sum += sensor_data -> angle;

    }
    oi_setWheels(0, 0); //stop
}

void back_up(oi_t *sensor_data, int millimeter){

    int sum = 0;
       oi_setWheels(-500, -450); //move backwards at full speed
       while (sum > -millimeter) //Runs till distance in cm is reached
       {
           oi_update(sensor_data);
           sum += sensor_data -> distance;

          // lcd_printf("%d", sum);  //Prints distance moved to lcd
       }
       oi_setWheels(0, 0); //stop
}



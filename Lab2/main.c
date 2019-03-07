#include "lcd.h"
#include "movement.h"
#include "open_interface.h"

/**
 * main.c
 *
 * Simple 'Hello, world program'.
 * This program prints "Hello, world" to the LCD screen
 * @author 
 * @date 
 */
int main(void)
{
    //Initialize the LCD. This also clears the screen
    //lcd_init();
    oi_t *sensor_data = oi_alloc();

    oi_init(sensor_data);

    int millimeter = 2000;

    int totalDistance = 0;
    oi_setWheels(500, 450); //move forward full speed
    while (totalDistance < millimeter) //Runs till distance in cm is reached
    {
        oi_update(sensor_data);
        totalDistance += sensor_data->distance;

        if (sensor_data->bumpLeft == 1) //
        {
            oi_setWheels(0, 0);
            back_up(sensor_data, 150);
            totalDistance -= 15;
            turn_right(sensor_data, 90);
            move_forward(sensor_data, 250);
            turn_left(sensor_data, 90);
            oi_setWheels(500, 450);
        }

        if (sensor_data->bumpRight == 1)
        {
            oi_setWheels(0, 0);
            back_up(sensor_data, 150);
            totalDistance -= 15;
            turn_left(sensor_data, 90);
            move_forward(sensor_data, 250);
            turn_right(sensor_data, 90);
            oi_setWheels(500, 450);
        }


    }
    oi_setWheels(0, 0); //stop

    oi_free(sensor_data);

    return 0;
}

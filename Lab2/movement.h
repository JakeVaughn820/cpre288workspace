/*
 * movement.h
 *
 *  @author: Jacob Vaughn, Nick Lorenz
 *  @date:  Feb 7, 2019
 */

#ifndef MOVEMENT_H_
#define MOVEMENT_H_

#include "open_interface.h"
#include "lcd.h"

//Moves forward a distance in centimeters
void move_forward(oi_t*sensor, int millimeter);

//Turns the robot right the number of degrees you give it.
void turn_right(oi_t *sensor_data, int degrees);

//Turns the robot left the number of degrees you give it.
void turn_left(oi_t *sensor_data, int degrees);

//Backs up the robot so many millimeters
void back_up(oi_t *sensor_data, int millimeter);

#endif

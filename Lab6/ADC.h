/*
 * lcd.h
 *
 *  @author: nbergman
 *  @date:  Mar 1, 2016
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <inc/tm4c123gh6pm.h>
#include "timer.h"

void init_ADC();

int adc_read(void);

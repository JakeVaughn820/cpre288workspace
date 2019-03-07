/**
 * main.c
 * @author: Jacob Vaughn, Nick Lorenz
 * @date: 2/21/2019
 */

#include "uart.h"
#include "lab5_scan_data.h"
#include <stdint.h>
#include <stdbool.h>
#include "timer.h"
#include "lcd.h"
#include <inc/tm4c123gh6pm.h>
#include "driverlib/interrupt.h"


extern volatile char putty_char = 0;
extern volatile int putty_event = 0;

/**
 * main.c
 *
 */
int main(void)
{
    uart_init();
    lcd_init();
    init_ADC();

    lcd_printf("%d", adc_read());



}

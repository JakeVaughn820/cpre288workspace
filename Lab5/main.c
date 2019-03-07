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

    struct reading reading_array[181];

    get_reading("dataset3.csv", reading_array);

    char sendstr[100];
    // prepare the header
    sprintf(sendstr, "%-20s%-20s%-20s\r\n", "Degrees", "IR Distance (cm)", "Sonar Distance(cm)");
    // send the header
    uart_sendStr(sendstr);

    int i = 0;
    while(i < 181){

        sprintf(sendstr, "%-20d%-20f%-20f\r\n", i, reading_array[i].ir_distance, reading_array[i].sonar_distance);
        uart_sendStr(sendstr);
        i++;
    }
//    uart_sendChar('o');
}

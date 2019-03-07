/**
 * main.c
 * @author: Jacob Vaughn, Nick Lorenz
 * @date: 2/21/2019
 */

#include "uart.h"


extern volatile char putty_char = 0;
extern volatile int putty_event = 0;

/**
 * main.c
 *
 */
int main(void)
{

    //Initialize the LCD. This also clears the screen
    lcd_init();
    uart_init();

    int count = 0;
    char str[21];
    char data;
    int i;

    while (1)
    {
        if (putty_event == 1)
        {
            data = putty_char;
            if (data == '\r') //Prints buffer to lcd and sends a return to putty
            {
                uart_sendChar('\n');  //return to putty
                uart_sendChar(data);

                lcd_printf("%s", str); // print on lcd
                count = -1;
                for (i = 0; i < 21; i++)  //clearing str
                {
                    str[i] = '\0';
                }

            }
            str[count] = data;

            count++;
            if (data != '\r') //counts up on lcd and sends char to putty
            {
                uart_sendChar(data);
                lcd_printf("%d", count);
            }

            if (count == 20) //Prints buffer if 20 char are input and moves ln down in putty
            {
                uart_sendChar('\n');
                uart_sendChar('\r');

                lcd_printf("%s", str);
                count = 0;

                for (i = 0; i < 21; i++)
                {
                    str[i] = '\0';
                }
            }
            putty_event = 0;
        }

    }

}

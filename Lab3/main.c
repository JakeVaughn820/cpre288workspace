/**
 * main.c
 * @author: Jacob Vaughn, Nick Lorenz
 * @date: 2/14/2019
 */

#include "lcd.h"
#include "button.h"

// These variables are declared in button.h for your use in the interrupt handler.
//extern volatile int button_event = 0; // Boolean to keep track of whether a hardware event has happened (button pressed)
//extern volatile int button_num = 0; // keeps track of button pressed

/**
 * main.c
 * Prints the button that has been pressed
 */
int main(void)
{
    // Hint: You may need to use pointers to return the button that has been pressed

    //Initialize the LCD. This also clears the screen
    lcd_init();

    int x = 1;
    button_init();

    init_button_interrupts();

    while (1)
    {
       // gpioe_handler();
        x += 1;
    }

}

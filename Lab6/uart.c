/*
 * uart.c
 * @author: Jacob Vaughn, Nick Lorenze
 * @date: Feb 21, 2019
 */

#include "uart.h"

// Initialize UART
void uart_init(void)
{

    //Enable the UART module using the RCGCUART register
    SYSCTL_RCGCUART_R |= 0b00000010;
    //Enable the clock to the appropriate GPIO module via the RCGCGPIO register
    SYSCTL_RCGCGPIO_R |= 0b00000010;

    //Enable alternate function for PB0,PB1 and set functionality
    GPIO_PORTB_AFSEL_R |= 0x03;
    GPIO_PORTB_PCTL_R |= 0x00000011;

    // Set digital or analog mode, and pin directions
    GPIO_PORTB_DEN_R |= 0x03; //Set pins 0, 1 digital mode
    GPIO_PORTB_DIR_R &= ~0x1;
//            0xF; // Set pin 0 (Rx) to input (0)
    GPIO_PORTB_DIR_R |= 0x2;

//    |= 0xF; // Set pin 1 (Tx) to output (1)

    // 2. Set up UART device
    // A. Configure UART functionality, frame format and Baud speed

    //Disable the UART by clearing the UARTEN bit in the UARTCTL register
    UART1_CTL_R &= 0xFFFFFFFE; // search tm4c123gh6pm.h

    //Set baud rate
    //Write the integer portion of the BRD to the UARTIBRD register
    UART1_IBRD_R = 8;
            //104;
    //Write the fractional portion of the BRD to the UARTFBRD register.
    UART1_FBRD_R = 44;
            //11;
    //Write the desired serial parameters to the UARTLCRH register
    UART1_LCRH_R = 0x60;
    //Configure the UART clock source by writing to the UARTCC register
    UART1_CC_R = 0x0;

    // B. Setup UART1 interrupts
    UART1_ICR_R |= 0b00010000; // Clear RX interrupt status flag
    UART1_IM_R |= 0b00010000; // Enable RX interrupts

    // 3. NVIC setup
    // A. Configure NVIC to allow UART interrupts
    NVIC_PRI1_R |= 0x00200000; //Set UART? IRQ pri to 1 (bits 15-13)
    NVIC_EN0_R |= 0x00000040; //Enable UART? IRQ (IRQ 5)

    // B. Bind UART1 interrupt requests to user’s Interrupt Handler
    IntRegister(INT_UART1, UART1_Handler);
    IntMasterEnable(); //Globally allows CPU to service interrupt

    //Enable the UART by setting the UARTEN bit in the UARTCTL register
    UART1_CTL_R |= 0x301;


}
/**
 * @brief sends an entire string of characters over UART1 module
 * @param data pointer to the first index of the string to be sent
 */
void uart_sendStr(const char *data)
{
    //until we reach a null character
    while (*data != '\0')
    {
        //send the current character
        uart_sendChar(*data);
        // increment the pointer.
        data++;
    }

}
void uart_sendChar(char data)
{
    while ((UART1_FR_R & 0x20) != 0);
    UART1_DR_R = data;
}

//
char uart_receive(void)
{
    char rdata;

    while ((UART1_FR_R & 0x10) != 0)
        ;
    rdata = (char) (UART1_DR_R & 0xFF);
    return rdata;
}

//UART1 ISR
void UART1_Handler()
{
    // 1) Check if handler called due to a Rx event
    if (UART1_MIS_R & 0b00010000)
    {
        UART1_ICR_R & 0b00010000; //clear interrupt flag
        putty_char = uart_receive(); // receives char
        putty_event = 1;
    }
}



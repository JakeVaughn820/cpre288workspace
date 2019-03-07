/*
 * uart.h
 * @author: Jacob Vaughn, Nick Lorenze
 * @date: Feb 21, 2019
 */

#ifndef UART_H_
#define UART_H_

#include <stdint.h>
#include <stdbool.h>
#include "timer.h"
#include "lcd.h"
#include <inc/tm4c123gh6pm.h>
#include "driverlib/interrupt.h"



extern volatile char putty_char;
extern volatile int putty_event;

// Initialize UART
void uart_init(void);

void uart_sendStr(const char *data);

//
void uart_sendChar(char data);

//
char uart_receive(void);

//
void UART1_Handler(void);

#endif /* UART_H_ */

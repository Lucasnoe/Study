/*
 * uart.h
 *
 *  Created on: 1 de mar de 2023
 *      Author: Lucas
 */

#ifndef UART_H_
#define UART_H_
#include <stdint.h>
#include "stm32f4xx.h"

void uart2_tx_init(void);
char uart2_read(void);
void uart2_rxtx_init(void);
void uart2_rxtx_Interrupt_init(void);
#define CR1_RXNEIE			5
#define SR_RXNE				(1U<<5)




#endif /* UART_H_ */

/*
 * uart.c
 *
 *  Created on: 1 de mar de 2023
 *      Author: Lucas
 */
#include "uart.h"

#define GPIOAEN 			0
#define USART2EN			17
#define MODER_PA2_0         4
#define MODER_PA2_1         5
#define MODER_PA3_0         6
#define MODER_PA3_1         7
#define AP2_AF7_0			8
#define AP2_AF7_1			9
#define AP2_AF7_2			10
#define AP2_AF7_3			11
#define AP3_AF7_0			12
#define AP3_AF7_1			13
#define AP3_AF7_2			14
#define AP3_AF7_3			15
#define SYS_FREQ			16000000U
#define APB1_CLK			SYS_FREQ
#define UART_BAUDRATE		115200
#define CR1_TE				(1U<<3)
#define CR1_UE				13
#define CR1_RE				2

#define SR_TXE				(1U<<7)
#define SR_RXNE				(1U<<5)


/* ----Macros---- */

//set bit

#define set_bit(Y,bit_x) (Y|=(1<<bit_x))

//clear bit

#define clr_bit(Y,bit_x) (Y&=~(1<<bit_x))

//toggle bit

#define tog_bit(Y,bit_x) (Y^=(1<<bit_x))

static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate);
static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate);

void uart2_write(int ch);

int __io_putchar(int ch)
{
	uart2_write(ch);
	return ch;
}
void uart2_rxtx_init(void){
	/*--Configurar o pino PA3 para usar a UART--*/
	/*Habilita o clock à GPIOA*/

		set_bit(RCC->AHB1ENR,GPIOAEN);
	/*Definir o pino PA2 com ALTERNATE FUNCTION MODE */
		set_bit(GPIOA->MODER,MODER_PA2_1);
		clr_bit(GPIOA->MODER,MODER_PA2_0);

	/*Definir o pino PA2 como alternate function type uart_tx (AF7)*/
		set_bit(GPIOA->AFR[0],AP2_AF7_0);
		set_bit(GPIOA->AFR[0],AP2_AF7_1);
		set_bit(GPIOA->AFR[0],AP2_AF7_2);
		clr_bit(GPIOA->AFR[0],AP2_AF7_3);

	/*Definir o pino PA3 com ALTERNATE FUNCTION MODE */
		set_bit(GPIOA->MODER,MODER_PA3_1);
		clr_bit(GPIOA->MODER,MODER_PA3_0);

	/*Definir o pino PA3 como alternate function type uart_rx (AF7)*/
		set_bit(GPIOA->AFR[0],AP3_AF7_0);
		set_bit(GPIOA->AFR[0],AP3_AF7_1);
		set_bit(GPIOA->AFR[0],AP3_AF7_2);
		clr_bit(GPIOA->AFR[0],AP3_AF7_3);
	/*--Configurar o módulo UART--*/

	/*Habilita o clock à USART1*/
		set_bit(RCC->APB1ENR,USART2EN);
	/*Define o Baudrate*/
		uart_set_baudrate(USART2, APB1_CLK, UART_BAUDRATE);
	/* Configurar a direção de transferência e recepção*/
		USART2->CR1=CR1_TE;
		set_bit(USART2->CR1,CR1_RE);

	/* Enable UART module*/
		set_bit(USART2->CR1,CR1_UE);


}



void uart2_tx_init(void){
	/*--Configurar o pino PA2 para usar a UART--*/
	/*Habilita o clock à GPIOA*/

		set_bit(RCC->AHB1ENR,GPIOAEN);

	/*Definir o pino PA2 com ALTERNATE FUNCTION MODE */
		set_bit(GPIOA->MODER,MODER_PA2_1);
		clr_bit(GPIOA->MODER,MODER_PA2_0);


	/*Definir o pino PA2 como alternate function type uart_tx (AF7)*/
		set_bit(GPIOA->AFR[0],AP2_AF7_0);
		set_bit(GPIOA->AFR[0],AP2_AF7_1);
		set_bit(GPIOA->AFR[0],AP2_AF7_2);
		clr_bit(GPIOA->AFR[0],AP2_AF7_3);
	/*--Configurar o módulo UART--*/

	/*Habilita o clock à USART1*/
		set_bit(RCC->APB1ENR,USART2EN);
	/*Define o Baudrate*/
		uart_set_baudrate(USART2, APB1_CLK, UART_BAUDRATE);
	/* Configurar a direção de transferência*/
		USART2->CR1=CR1_TE;
	/* Enable UART module*/
		set_bit(USART2->CR1,CR1_UE);


}

static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate){

	return ((PeriphClk + (BaudRate/2U))/BaudRate);

}


static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate){
	USARTx->BRR = compute_uart_bd(PeriphClk,BaudRate);

}

char uart2_read(void){
	/*certifique-se de que o registro de dados de transmissão não esteja vazio*/
	while(!(USART2->SR & SR_RXNE)){
		}
	return USART2->DR;
}

void uart2_write(int ch){
	/*certifique-se de que o registro de dados de transmissão esteja vazio*/
	while(!(USART2->SR & SR_TXE)){

	}

	/*Escrever oq esta no registrador*/
	USART2->DR = (ch & 0xFF);

}


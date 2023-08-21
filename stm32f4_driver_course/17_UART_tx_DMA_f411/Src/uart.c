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
#define DMAEN				(1U<<21)
#define DMA_S_EN			(1U<<0)
#define DMA_S_CR_CNH4		(1U<<27)
#define DMA_S_CR_MINC	    (1U<<10)
#define DMA_S_CR_DIR		(1U<<6)
#define DMA_S_CR_TCIE		(1U<<4)
#define DMA_S_FCR_DMDIS		(1U<<2)
#define DMA_S_CR_EN			(1U<<0)
#define UART_CR3_DMAT		(1U<<7)


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

void uart2_rxtx_Interrupt_init(void){
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

	// Habilita a interrupção RXNEIE
		set_bit(USART2->CR1,CR1_RXNEIE);

	// Habilita a interrupção no NVIC
		NVIC_EnableIRQ(USART2_IRQn);

	/* Enable UART module*/
		set_bit(USART2->CR1,CR1_UE);


}

void dma1_stream6_init(uint32_t src, uint32_t dst, uint32_t len)
{
	//Enable clock access to DMA1
	RCC->AHB1ENR |= DMAEN;

	//Disable DMA1 Stream6
	DMA1_Stream6->CR &= ~DMA_S_EN;

	//Clear all interrupts flags of stream6
	DMA1->HIFCR |= ((1U<<16) 	 //CFEIFx: Stream x clear FIFO error interrupt flag
				| (1U<<18) 		 //CDMEIFx: Stream x clear direct mode error interrupt flag
				| (1U<<19) 		 //CTEIFx: Stream x clear transfer error interrupt flag
				| (1U<<20) 		 //CHTIFx: Stream x clear half transfer interrupt flag
				| (1U<<21));	 //CTCIFx: Stream x clear transfer complete interrupt flag

	//Set the destination buffer
	DMA1_Stream6->PAR = dst;  // Peripheral address

	//Set the source buffer
	DMA1_Stream6->M0AR = src; // Memory 0 address

	//Set Length
	DMA1_Stream6->NDTR = len;

	//ESelect Stream6 Channel 4
	DMA1_Stream6->CR = DMA_S_CR_CNH4; //CHSEL[2:0]: Channel selection

	//Enable memory increment
	DMA1_Stream6->CR |= DMA_S_CR_MINC; //Memory Increment

	//Configure transfer direction
	DMA1_Stream6->CR |= DMA_S_CR_DIR;  //Data transfer direction - Memory-to-peripheral

	//Enable DMA transfer complete interrupt
	DMA1_Stream6->CR |= DMA_S_CR_TCIE;	//TCIE: Transfer complete interrupt enable

	//Enable direct mode and disable FIFO
	DMA1_Stream6->FCR &= ~DMA_S_FCR_DMDIS; // DMDIS: Direct mode disable if set bit

	//Enable DMA1 Steam6
	DMA1_Stream6->CR |=DMA_S_CR_EN; //EN: Stream enable / flag stream ready when read low

	//Enable UART2 transmitter DMA
	USART2->CR3 |= UART_CR3_DMAT	//DMA enable transmitter

	//DMA interrupt enable in NVIC
	NVIC_EnableIRQ(DMA1_Stream6_IRQn);
}


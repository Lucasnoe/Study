// Placa STM32WL Nucleo-64 board (MB1389)
// LED ON Board:
// LED user 1 - PB15
// LED user 2 - PB9
// LED user 3 - PB11
// Botôes On board
// B1 user - 	PA0
// B2 user - 	PA1
// B3 user - 	PC6

// -- USART1 TX - PB6
// -- USART1 RX - PB7


#include "stm32wl55xx.h"
#include <stdint.h>

#define GPIOAEN 			0
#define GPIOBEN 			1
#define USART1EN			14
#define MODER_PA2_0         4
#define MODER_PA2_1         5
#define MODER_PB6_0         12
#define MODER_PB6_1         13
#define AF7_0				24
#define AF7_1				25
#define AF7_2				26
#define AF7_3				27
#define SYS_FREQ			16000000U
#define APB2_CLK			SYS_FREQ
#define UART_BAUDRATE		115200
#define CR1_TE				(1U<<3)
#define CR1_UE				0
#define ISR_TXE				(1U<<7)
#define PIN11 				11


/* ----Macros---- */

//set bit

#define set_bit(Y,bit_x) (Y|=(1<<bit_x))

//clear bit

#define clr_bit(Y,bit_x) (Y&=~(1<<bit_x))

//toggle bit

#define tog_bit(Y,bit_x) (Y^=(1<<bit_x))

static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate);
static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate);
void uart_tx_init(void);
void uart1_write(int ch);



int main(void){



	uart_tx_init();

	while(1){
		tog_bit(GPIOB->ODR,PIN11); 			//using odr register
		for(int i=0; i<100000; i++){}
		uart1_write('Y');

	}


}

void uart_tx_init(void){
	/*--COnfigurar o pino GPIO par usar a UART--*/
	/*Habilita o clock à GPIOA*/

		set_bit(RCC->AHB2ENR,GPIOAEN);
		set_bit(RCC->AHB2ENR,GPIOBEN);

	/*Define o Pino PB11 como saida*/
		set_bit(GPIOB->MODER,22);
		clr_bit(GPIOB->MODER,23);

	/*Definir o pino PB6 com ALTERNATE FUNCTION MODE */
//		set_bit(GPIOA->MODER,MODER_PA2_1);
//		clr_bit(GPIOA->MODER,MODER_PA2_0);
		set_bit(GPIOB->MODER,MODER_PB6_1);
		clr_bit(GPIOB->MODER,MODER_PB6_0);

	/*Definir o pino PB6 como alternate function type uart_tx (AF7)*/
		set_bit(GPIOB->AFR[0],AF7_0);
		set_bit(GPIOB->AFR[0],AF7_1);
		set_bit(GPIOB->AFR[0],AF7_2);
		clr_bit(GPIOB->AFR[0],AF7_3);
	/*--Configurar o módulo UART--*/

	/*Habilita o clock à USART1*/
		set_bit(RCC->APB2ENR,USART1EN);
	/*Define o Baudrate*/
		uart_set_baudrate(USART1, APB2_CLK, UART_BAUDRATE);
	/* Configurar a direção de transferência*/
		USART1->CR1=CR1_TE;
	/* Enable UART module*/
		set_bit(USART1->CR1,CR1_UE);


}

static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate){

	return ((PeriphClk + (BaudRate/2U))/BaudRate);

}


static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate){
	USARTx->BRR = compute_uart_bd(PeriphClk,BaudRate);

}

void uart1_write(int ch){
	/*certifique-se de que o registro de dados de transmissão esteja vazio*/
	while(!(USART1->ISR & ISR_TXE)){

	}

	/*Escrever oq esta no registrador*/
	USART1->TDR = (ch & 0xFF);

}

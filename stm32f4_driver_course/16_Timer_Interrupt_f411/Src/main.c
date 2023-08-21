#include "stm32f4xx.h"
#include <stdio.h>
#include <stdint.h>
#include "uart.h"
#include "adc.h"
#include "systick.h"
#include "tim.h"

#define GPIOCEN 		2


/* ----Macros---- */

//set bit

#define set_bit(Y,bit_x) (Y|=(1<<bit_x))

//clear bit

#define clr_bit(Y,bit_x) (Y&=~(1<<bit_x))

//toggle bit

#define tog_bit(Y,bit_x) (Y^=(1<<bit_x))

static void timer2_callback(void);


int main(void)
{

	/*Habila o clocl às GPIOS A e B*/
		set_bit(RCC->AHB1ENR,GPIOCEN);

		/*Define o Pino PB11 como saida*/
		set_bit(GPIOC->MODER,26);
		clr_bit(GPIOC->MODER,27);

	uart2_tx_init();
	tim2_1hz_interrupt_init();


	while(1){

			}

}

static void timer2_callback(void)
{
	printf("A second passed: \n\r");
	tog_bit(GPIOC->ODR,13);
}
void TIM2_RQHandler(void)
{
	//Limpa a flag de interrupção de atualização
	TIM2->SR &= ~SR_UIF;
	timer2_callback();
}






#include "stm32f4xx.h"
#include <stdio.h>
#include <stdint.h>
#include "uart.h"
#include "adc.h"
#include "systick.h"
#include "tim.h"
#include "exti.h"


#define GPIOCEN 		2

/* ----Macros---- */

//set bit

#define set_bit(Y,bit_x) (Y|=(1<<bit_x))

//clear bit

#define clr_bit(Y,bit_x) (Y&=~(1<<bit_x))

//toggle bit

#define tog_bit(Y,bit_x) (Y^=(1<<bit_x))

static void exti_callback(void);

int timestamp = 0;
int main(void){

	/*Habilita o clocl à GPIO C*/
	set_bit(RCC->AHB1ENR,GPIOCEN);

	/*Define o Pino PC13 como saida*/
	set_bit(GPIOC->MODER,26);
	clr_bit(GPIOC->MODER,27);

	pa0_exti_init();
	uart2_tx_init();

	while(1){

			}

}

static void exti_callback(void){

	printf("BTN pressed...\n\r");
	tog_bit(GPIOC->ODR,13);

}

void EXTI0_IRQHandler(void){
	if((EXTI->PR & LINE0)!=0){
		//Clear  PR flag
		EXTI->PR |= LINE0;
		exti_callback();
	}
}



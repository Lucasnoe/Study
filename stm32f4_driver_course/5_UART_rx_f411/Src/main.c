#include "stm32f4xx.h"
#include <stdio.h>
#include <stdint.h>
#include "uart.h"

#define GPIOCEN 		2
#define PIN13 			13
#define MODER_PC13_0	26
#define MODER_PC13_1	27

/* ----Macros---- */

//set bit

#define set_bit(Y,bit_x) (Y|=(1<<bit_x))

//clear bit

#define clr_bit(Y,bit_x) (Y&=~(1<<bit_x))

//toggle bit

#define tog_bit(Y,bit_x) (Y^=(1<<bit_x))

char key;


int main(void){

	// Acesso do clock ao PORTC
	set_bit(RCC->AHB1ENR, GPIOCEN);

	// Definir o pino PC13 como saida
	set_bit(GPIOC->MODER, MODER_PC13_0);
	clr_bit(GPIOC->MODER, MODER_PC13_1);


	uart2_rxtx_init();

	while(1){

			key = uart2_read();
			if (key != '1')
			{
				set_bit(GPIOC->ODR, PIN13);
			}
			else{
				clr_bit(GPIOC->ODR, PIN13);
			}

	}
}






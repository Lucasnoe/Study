// Placa STM32WL Nucleo-64 board (MB1389)
// LED ON Board:
// LED user 1 - PB15
// LED user 2 - PB9
// LED user 3 - PB11
// Botôes On board
// B1 user - 	PA0
// B2 user - 	PA1
// B3 user - 	PC6


#include "stm32wl55xx.h"

#define GPIOBEN 			1
#define PIN15 				15
#define PIN11 				11
#define PIN9  				9
/* ----Macros---- */

//set bit

#define set_bit(Y,bit_x) (Y|=(1<<bit_x))

//clear bit

#define clr_bit(Y,bit_x) (Y&=~(1<<bit_x))

//toggle bit

#define tog_bit(Y,bit_x) (Y^=(1<<bit_x))

int main(void){

	/*Habila o clocl às GPIOS A e B*/
	set_bit(RCC->AHB2ENR,GPIOBEN);

	/*Define o Pino PB11 como saida*/
	set_bit(GPIOB->MODER,22);
	clr_bit(GPIOB->MODER,23);

	while(1){


//		tog_bit(GPIOB->ODR,PIN11); 			using odr register
		set_bit(GPIOB->BSRR,PIN11); 			//using BSRR register
		for(int i=0; i<100000; i++){}

		set_bit(GPIOB->BSRR,(PIN11+16));
		for(int i=0; i<100000; i++){}

	}


}

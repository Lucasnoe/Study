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
#define GPIOAEN 			0
#define GPIOCEN 			2
#define PIN15 				15
#define PIN11 				11
#define PIN9  				9
#define PIN1				1
#define BTN					(1U<<6)

/* ----Macros---- */

//set bit

#define set_bit(Y,bit_x) (Y|=(1<<bit_x))

//clear bit

#define clr_bit(Y,bit_x) (Y&=~(1<<bit_x))

//toggle bit

#define tog_bit(Y,bit_x) (Y^=(1<<bit_x))

int main(void){

	/*Habilita o clock à GPIOs A, B e C*/
	set_bit(RCC->AHB2ENR,GPIOBEN);
	set_bit(RCC->AHB2ENR,GPIOAEN);
	set_bit(RCC->AHB2ENR,GPIOCEN);

	/*Define o Pino PB11 como saida*/
	set_bit(GPIOB->MODER,22);
	clr_bit(GPIOB->MODER,23);

	/*Define o Pino PA1 como entrada*/
	clr_bit(GPIOC->MODER,12);
	clr_bit(GPIOC->MODER,13);

	while(1){

			if(GPIOC->IDR & BTN){
				set_bit(GPIOB->BSRR, PIN11);
			}
			else{
				set_bit(GPIOB->BSRR,(PIN11+16));
			}
	}


}

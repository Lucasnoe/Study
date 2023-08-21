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

int timestamp = 0;
int main(void){

	tim2_pa5_output_Compare();
	tim3_pa6_intput_Capture();


	while(1){

		//Aguardar até a borda ser detectada:
		while(!(TIM3->SR & SR_CC1IF)){}

		//Ler o valor capturado
		timestamp = TIM3->CCR1;
			}

}






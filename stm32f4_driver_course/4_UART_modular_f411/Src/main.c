#include "stm32f4xx.h"
#include <stdio.h>
#include <stdint.h>
#include "uart.h"

/* ----Macros---- */

//set bit

#define set_bit(Y,bit_x) (Y|=(1<<bit_x))

//clear bit

#define clr_bit(Y,bit_x) (Y&=~(1<<bit_x))

//toggle bit

#define tog_bit(Y,bit_x) (Y^=(1<<bit_x))


int main(void){

	uart2_tx_init();

	while(1){

		printf("hello, world!!!\n\r");

	}
}






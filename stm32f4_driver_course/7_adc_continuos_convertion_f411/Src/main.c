#include "stm32f4xx.h"
#include <stdio.h>
#include <stdint.h>
#include "uart.h"
#include "adc.h"

/* ----Macros---- */

//set bit

#define set_bit(Y,bit_x) (Y|=(1<<bit_x))

//clear bit

#define clr_bit(Y,bit_x) (Y&=~(1<<bit_x))

//toggle bit

#define tog_bit(Y,bit_x) (Y^=(1<<bit_x))

uint32_t sensor_value;

int main(void){

	uart2_tx_init();
	pa1_adc_init();
	start_convertion();


	while(1){

		sensor_value = adc_read();
		printf("sensor value is: %ld \n\r", sensor_value);

	}
}






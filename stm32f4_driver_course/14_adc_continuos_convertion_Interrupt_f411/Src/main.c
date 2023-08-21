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
static void ADC_callback(void);


int main(void)
{

	uart2_tx_init();
	pa1_adc_Interrupt_init();
	start_convertion();

	while(1){

			}
}

static void ADC_callback(void)
{
	sensor_value = ADC1->DR;
	printf("sensor value is: %ld \n\r", sensor_value);
}

void ADC_IRQHandler(void)
{
	if((ADC1->SR & SR_EOC)!=0)
	{
		//Limpar o EOC
		ADC1->SR &= ~(SR_EOC);

		ADC_callback();
	}
}




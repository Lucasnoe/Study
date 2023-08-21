#include "stm32f4xx.h"
#include "adc.h"

#define ADC1EN 				(1U<<8)
#define GPIOAEN 			(1U<<0)
#define PA1_MODER_ANALOG_0 	(1U<<2)
#define PA1_MODER_ANALOG_1 	(1U<<3)
#define ADC_CH1				(1U<<0)
#define ADC_SEQ_LEN_1 		0x00
#define CR2_ADON			(1U<<0)
#define CR2_SWSTART			(1U<<30)
#define SR_EOC				(1U<<1)
#define CR2_CONT			(1U<<1)


void pa1_adc_init(void){

	/*** Configurar a GPIO para usar o ADC1 ***/

	/* Habilitar o acesso do clock ao GPIOA */
	RCC->APB1ENR |= GPIOAEN;

	/*Definir o Pino A! como analogico*/

	GPIOA->MODER |= PA1_MODER_ANALOG_0;
	GPIOA->MODER |= PA1_MODER_ANALOG_1;

	/*** Configurar o modulo ADC1 ***/

	/* Habilitar o acesso ao clock para o ADC1*/
	RCC->APB2ENR |= ADC1EN;

	/* Configurar os paramentros do ADC*/
	/*Configurar a inicio da sequencia de converçãp*/

	ADC1->SQR3 = ADC_CH1;
	/*Configurar o comprimento da sequencia de amostragem*/
	ADC1->SQR1 = ADC_SEQ_LEN_1;
	/*Habiitar o modulo ADC*/
	ADC1->CR2 |= CR2_ADON;


}

void start_convertion(void){
	/*Habilitar o modo de conversão contínua*/
	ADC1->CR2 |= CR2_CONT;

	/*Start ADC convertion*/
	ADC1->CR2 |= CR2_SWSTART;

}

uint32_t adc_read(void){
	/*Aguarda a conclusão da conversão*/
	while(!(ADC1->SR & SR_EOC)){
	}

	/*Lê o valor convertido*/
	return (ADC1->DR);
}

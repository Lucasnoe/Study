#include "stm32f4xx.h"
#include "tim.h"

#define TIM2EN			(1U<<0)
#define CR1_CEN			(1U<<0)
#define OC_TOGGLE		((1U<<4)|(1U<<5))
#define CCER_CC1E		(1U<<0)
#define	GPIOAEN			(1U<<0)
#define	GPIOCEN			(1U<<2)


void tim2_1hz_init(void){

	// Habilitar o clock ao timer2

		RCC->APB1ENR |= TIM2EN;

	// definir o valor do prescaler
		TIM2->PSC = 1600-1;  // 16MHz/1600 = 10 000

	// definir o valor do auto-reload
		TIM2->ARR = 10000-1; // 10000/10000 = 1

	// Limpar o contador
		TIM2->CNT = 0;

	// Habilitar o clock
		TIM2->CR1 = CR1_CEN;
}

void tim2_pa5_output_Compare(void){

	//Habilitar o acesso do clock ao GPIOA e GPIOC
		RCC->AHB1ENR |= GPIOAEN;
		RCC->AHB1ENR |= GPIOCEN;

	// Definir os modos de operação dos pinos PC13 e PA5

	/*Define o Pino PC13 como Entrada*/
		GPIOC->MODER |=  (1U<<26);
		GPIOC->MODER &= ~(1U<<27);

	/*Define o Pino PA5 como alternate function*/
		GPIOA->MODER &= ~(1U<<10);
		GPIOA->MODER |=  (1U<<11);

	// Determina o alternate function de PA5 (AF01)
		GPIOA->AFR[0] |=  (1U<<20);
		GPIOA->AFR[0] &= ~(1U<<21);
		GPIOA->AFR[0] &= ~(1U<<22);
		GPIOA->AFR[0] &= ~(1U<<23);

	// Habilitar o clock ao timer2
		RCC->APB1ENR |= TIM2EN;

	// definir o valor do prescaler
		TIM2->PSC = 1600-1;  // 16MHz/1600 = 10 000

	// definir o valor do auto-reload
		TIM2->ARR = 10000-1; // 10000/10000 = 1

	// Define o modo de alternacia da saida
		TIM2->CCMR1 = OC_TOGGLE;

	//Enable Tim2 ch1 em modo de comparação
		TIM2->CCER |= CCER_CC1E;

	// Limpar o contador
		TIM2->CNT = 0;

	// Habilitar o clock
		TIM2->CR1 = CR1_CEN;
}


#include "stm32f4xx.h"

#define TIM2EN			(1U<<0)
#define CR1_CEN			(1U<<0)
#define DIER_UIE		(1U<<0)

void tim2_1hz_interrupt_init(void){

	// Habilitar o clock ao timer2

		RCC->APB1ENR |= TIM2EN;

	// definir o valor do prescaler
		TIM2->PSC = 1600-1;  // 16MHz/1600 = 10 000

	// definir o valor do auto-reload
		TIM2->ARR = 10000-1; // 10000/10000 = 1

	// Limpar o contador
		TIM2->CNT = 0;

	// Habilita o timer
		TIM2->CR1 = CR1_CEN;

	// Habilitar a interrupção do timer
		TIM2->DIER |= DIER_UIE;

	/// Habilitar a interrupção do timer no NVIC
		NVIC_EnableIRQ(TIM2_IRQn);
}

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

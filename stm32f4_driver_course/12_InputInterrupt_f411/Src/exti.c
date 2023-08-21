

#include "stm32f4xx.h"
#define GPIOAEN 		(1U<<0)
#define SYSCFGEN		(1U<<14)
#define EXTI_IMR_0 		(1U<<0)
#define EXTI_FTSR_0		(1U<<0)

void pa0_exti_init(void){

	//Disable global interrupts
		__disable_irq();  // Função intrinseca do arquivo cortexm4.h

	// Enable clock access for GPIOA
		RCC->AHB1ENR |= GPIOAEN;

	//Enable clock access to SYSCONF
		RCC->APB2ENR |= SYSCFGEN;

	// set PC13 as INPUT
		GPIOA->MODER &= ~(1U<<0);
		GPIOA->MODER &= ~(1U<<1);

	//Select PORTA for EXTI0
		//Por padrão EXTI habilita o pino 0 para interrupção
		SYSCFG->EXTICR[0] = 0;

	//Unmask EXTI13
		EXTI->IMR |= EXTI_IMR_0;
	// Select falling edge trigger

		EXTI->FTSR |=EXTI_FTSR_0;

	//Enable EXTI line in NVIC
		NVIC_EnableIRQ(EXTI0_IRQn);

	//Enable global interrupts
		__enable_irq();  // Função intrinseca do arquivo cortexm4.h

}

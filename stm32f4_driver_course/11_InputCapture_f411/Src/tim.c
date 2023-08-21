#include "stm32f4xx.h"
#include "tim.h"

#define TIM2EN			(1U<<0)
#define TIM3EN			(1U<<1)
#define CR1_CEN			(1U<<0)
#define OC_TOGGLE		((1U<<4)|(1U<<5))
#define	GPIOAEN			(1U<<0)
#define	GPIOCEN			(1U<<2)
#define CCMR_CC1S		(1U<<0)   // definir o registrador capture/compare mode rm modo de captura de entrada
#define CCER_CC1E		(1U<<0)

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
//		RCC->AHB1ENR |= GPIOCEN;

	// Definir os modos de operação dos pinos PC13 e PA5

//	/*Define o Pino PC13 como Entrada*/
//		GPIOC->MODER |=  (1U<<26);
//		GPIOC->MODER &= ~(1U<<27);

	/*Define o Pino PA5 como alternate function*/
		GPIOA->MODER &= ~(1U<<10);
		GPIOA->MODER |=  (1U<<11);

	// Determina o alternate function de PA5 (AF01)
		GPIOA->AFR[0] |=  (1U<<20);
		GPIOA->AFR[0] &= ~(1U<<21);
		GPIOA->AFR[0] &= ~(1U<<22);
		GPIOA->AFR[0] &= ~(1U<<23);

	// Habilitar o clock ao timer2
		RCC->APB1ENR |= TIM3EN;

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

	// Habilita o timer2
		TIM2->CR1 = CR1_CEN;
}

void tim3_pa6_intput_Capture(void){

	//Habilitar o acesso do clock ao GPIOA e GPIOC
		RCC->AHB1ENR |= GPIOAEN;
//		RCC->AHB1ENR |= GPIOCEN;

	// Definir os modos de operação dos pinos PC13 e PA6

	/*Define o Pino PC13 como saída*/
//		GPIOC->MODER |=  (1U<<26);
//		GPIOC->MODER &= ~(1U<<27);

	/*Define o Pino PA6 como alternate function*/
		GPIOA->MODER &= ~(1U<<12);
		GPIOA->MODER |=  (1U<<13);

	// Determina o alternate function de PA6 (AF02) TIM3_CH1
		GPIOA->AFR[0] &= ~(1U<<24);
		GPIOA->AFR[0] |=  (1U<<25);
		GPIOA->AFR[0] &= ~(1U<<26);
		GPIOA->AFR[0] &= ~(1U<<27);

	// Habilita o clock ao timer3
		RCC->APB1ENR |= TIM3EN;

	// definir o valor do prescaler
		TIM3->PSC = 16000-1;  // 16MHz/16000 = 1000

	//Define CH1 em modo de captura de entrada
		TIM3->CCMR1 = CCMR_CC1S;

	//Definir o CH1 para capturar a borda de subida
		TIM3->CCER = CCER_CC1E;

	// Habilitar o timer3
		TIM3->CR1 = CR1_CEN;
}


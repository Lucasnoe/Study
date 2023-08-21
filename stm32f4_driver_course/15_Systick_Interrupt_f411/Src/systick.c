#include "stm32f4xx.h"


#define SYSTICK_LOAD_VAL			16000
#define CTRL_ENABLE					(1U<<0)
#define CTRL_CLKSRC					(1U<<2)
#define CTRL_COUNTFLAG				(1U<<16)
#define ONE_SEC_LOAD				16000000
#define CTRL_TICKINT				(1U<<1)



void systick_DelayMS(int delay)
{

	/*Recarregar com o numeor de ciclos por milisegundos*/

	SysTick->LOAD = SYSTICK_LOAD_VAL;

	/*Limpa o valor atual do systick*/

	SysTick->VAL = 0;

	// Habilita o systick e seleciona a fonte de clock interno

	SysTick->CTRL = CTRL_ENABLE | CTRL_CLKSRC;

	for(int i=0; i<delay; i++){
		//espera a COUNTFLAG seja ativada
		while(!(SysTick->CTRL & CTRL_COUNTFLAG)){}
		}

	SysTick->CTRL = 0;
}

void systick_1hz_interrupt(void)
{
	/*Recarregar com o numeor de ciclos por milisegundos*/
		SysTick->LOAD = ONE_SEC_LOAD-1;

	/*Limpa o valor atual do systick*/
		SysTick->VAL = 0;

	// Habilita o systick e seleciona a fonte de clock interno
		SysTick->CTRL = CTRL_ENABLE | CTRL_CLKSRC;

	//Habilitar a interrupção do Systick

		SysTick->CTRL |= CTRL_TICKINT;

	//

}

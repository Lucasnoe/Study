/*
 * adc.h
 *
 *  Created on: 6 de mar de 2023
 *      Author: Lucas
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>
#define SR_EOC				(1U<<1)

void pa1_adc_init(void);
uint32_t adc_read(void);
void start_convertion(void);
void pa1_adc_Interrupt_init(void);



#endif /* ADC_H_ */

/*
 * adc.h
 *
 *  Created on: 15 Jul. 2023
 *      Author: amaral
 */

#ifndef ADC_H_
#define ADC_H_
#include <stdint.h>

void pa1_adc_init(void);
uint32_t adc_read(void);
void start_conversion(void);


#endif /* ADC_H_ */

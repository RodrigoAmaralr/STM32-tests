#include "stm32f4xx.h"
#include "adc.h"

#define GPIOAEN			(1U<<0)
#define ADC1EN			(1U<<8)			//RCC_APB2ENR
#define ADC_CH1			(1U<<0)
#define ADC_SEQ_LEN_1	0x00
#define CR2_ADON		(1U<<0)
#define CR2_SWSTART		(1U<<30)

#define CR2_CONT		(1U<<1)
#define CR1_EOCIE		(1U<<5)

void pa1_adc_interrupt_init(void)
{
	/******* Configure the ADC GPIO pin ********/
	/*Enable clock access to GPIOA*/
	RCC->AHB1ENR |= GPIOAEN;

	/*Set the mode of PA1 to analog */
	GPIOA->MODER |= (1U<<2);
	GPIOA->MODER |= (1U<<3);

	/******* configure the ADC module ********/
	/*Enable clock access to ADC*/
	RCC->APB2ENR |= ADC1EN;

	/*Enable ADC end-of-conversion interrupt*/
	ADC1->CR1 |= CR1_EOCIE;

	/*Enable ADC interrupt in NVIC*/
	NVIC_EnableIRQ(ADC_IRQn);

	/*Conversion sequence start*/
	ADC1->SQR3 = ADC_CH1;

	/*Conversion sequence length*/
//	ADC1->SQR1 = ADC_SEQ_LEN_1;
	ADC1->SQR1 &= ~(1U<<20);
	ADC1->SQR1 &= ~(1U<<21);
	ADC1->SQR1 &= ~(1U<<22);
	ADC1->SQR1 &= ~(1U<<23);

	/*Enable ADC module*/
	ADC1->CR2 |= CR2_ADON;
}

void pa1_adc_init(void)
{
	/******* Configure the ADC GPIO pin ********/
	/*Enable clock access to GPIOA*/
	RCC->AHB1ENR |= GPIOAEN;

	/*Set the mode of PA1 to analog */
	GPIOA->MODER |= (1U<<2);
	GPIOA->MODER |= (1U<<3);

	/******* configure the ADC module ********/
	/*Enable clock access to ADC*/
	RCC->APB2ENR |= ADC1EN;

	/*Conversion sequence start*/
	ADC1->SQR3 = ADC_CH1;

	/*Conversion sequence length*/
//	ADC1->SQR1 = ADC_SEQ_LEN_1;
	ADC1->SQR1 &= ~(1U<<20);
	ADC1->SQR1 &= ~(1U<<21);
	ADC1->SQR1 &= ~(1U<<22);
	ADC1->SQR1 &= ~(1U<<23);

	/*Enable ADC module*/
	ADC1->CR2 |= CR2_ADON;
}

void start_conversion(void)
{
	/*Enable continuous conversion*/
	ADC1->CR2 |= CR2_CONT;
	/*Start ACD conversion*/
	ADC1->CR2 |= CR2_SWSTART;
}

uint32_t adc_read(void)
{
	/*Wait for conversion to be complete*/
	while(!(ADC1->SR & SR_EOC)){}

	/*Read converted result*/
	return (ADC1->DR);
}
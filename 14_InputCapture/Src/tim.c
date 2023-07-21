#include "stm32f4xx.h"

#define TIM2EN 			(1U<<0)
#define TIM3EN 			(1U<<1)

#define CR1_CEN			(1U<<0)
#define OC_TOGGLE		(1U<<4) | (1U<<5)
#define CCER_CC1E		(1U<<0)

#define GPIOAEN			(1U<<0)
#define AFR5_TIM		(1U<<20)
#define AFR6_TIM		(1U<<25)
#define CCER_CC1S		(1U<<0)

void tim2_1hz_init(void) {
	/*Enable clock access to TIMER2*/
	RCC->APB1ENR |= TIM2EN;

	/*Set prescaler value*/
	TIM2->PSC = 1600 - 1; // 16000000/1600=10000

	/*Set auto-reload value*/
	TIM2->ARR = 10000 - 1; //10000/10000=1

	/*Clear counter*/
	TIM2->CNT = 0;

	/*Enable timer*/
//	TIM2->CR1 = CR1_CEN;
	TIM2->CR1 |= CR1_CEN;		//TIMx_CR1
}

void tim2_pa5_output_compare(void) {
	/*Enable clock access to GPIOA*/
	RCC->AHB1ENR |= GPIOAEN;

	/*Set PA5 mode to alternate function*/
	GPIOA->MODER &= ~(1U << 10);
	GPIOA->MODER |= (1U << 11);

	/*Set PA5 alternate function type to TIM2_CH1 (AF01)*/
	GPIOA->AFR[0] |= AFR5_TIM;

	/*Enable clock access to TIMER2*/
	RCC->APB1ENR |= TIM2EN;

	/*Set prescaler value*/
	TIM2->PSC = 1600 - 1; // 16000000/1600=10000

	/*Set auto-reload value*/
	TIM2->ARR = 10000 - 1; //10000/10000=1

	/*Set output compare toggle mode*/
	TIM2->CCMR1 = OC_TOGGLE;

	/*Enable TIMER2 ch1 in compare mode*/
	TIM2->CCER |= CCER_CC1E;

	/*Clear counter*/
	TIM2->CNT = 0;

	/*Enable timer*/
//	TIM2->CR1 = CR1_CEN;
	TIM2->CR1 |= CR1_CEN;		//TIMx_CR1
}

void tim3_pa6_input_capture(void) {
	/*In this case we will measure the period of pa5*/

	/*Enable clock access to GPIOA*/
	RCC->AHB1ENR |= GPIOAEN;

	/*Set PA6 mode to alternate function*/
	GPIOA->MODER &= ~(1U << 12);
	GPIOA->MODER |= (1U << 13);

	/*Set PA6 alternate function type to TIM3_CH1 (AF02)*/
	GPIOA->AFR[0] |= AFR6_TIM;

	/*Enable clock access to TIMER3*/
	RCC->APB1ENR |= TIM3EN;

	/*Set prescaler*/
	TIM3->PSC = 16000 -1;		//16000000 / 16000

	/*Set CH1 to input capture*/
	TIM3->CCMR1 = CCER_CC1S;

	/*Set CH1 to capture at rising edge*/
	TIM3->CCER = CCER_CC1E;

	/*Enable TIMER3*/
	TIM3->CR1 = CR1_CEN;
}

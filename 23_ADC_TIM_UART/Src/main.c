
#include "stm32f4xx.h"

#include <stdio.h>
#include <stdint.h>
#include "uart.h"
#include "adc.h"


int data;
double voltage;
double celsius;

int main(void) {

    RCC->AHB1ENR |=  1;

    RCC->APB1ENR |= 1;
    TIM2->PSC = 1600 - 1;
    TIM2->ARR = 10000 - 1;
    TIM2->CNT = 0;
    TIM2->CCMR1 = 0x6800;
    TIM2->CCER = 0x0010;
    TIM2->CCR2 = 50 - 1;
    TIM2->CR1 = 1;


    RCC->APB2ENR |= 0x100;
    ADC->CCR |= 0x800000;
    ADC->CCR &= ~0x400000;          // VBATE must be disabled for temp sensor

    ADC1->SMPR1 = 0x4000000;        // sampling time minimum 10 us
    ADC1->SQR3 = 18;
    ADC1->CR2 = 0x13000000;
    ADC1->CR2 |= 1;



	uart2_tx_init();


	printf("STM32F4 Temperature \r\n");

	while (1) {
        while(!(ADC1->SR & 2)) {}
        data = ADC1->DR;

        voltage = (double)data / 4095 * 3.3;   /* convert ADC output to voltage */
        celsius = (voltage - 0.76) / 0.0025 + 25; /* convert voltage to temperature C */
        //printf("%d, %.2f\370C\r\n", data, celsius);    /* octal 370 is degree sign in extended ASCII */
	}
}


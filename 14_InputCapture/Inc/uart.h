/*
 * uart.h
 *
 *  Created on: 13 Jul. 2023
 *      Author: amaral
 */

#ifndef UART_H_
#define UART_H_
#include "stm32f4xx.h"
#include <stdint.h>

void uart2_tx_init(void);
void uart2_rxtx_init(void);
char uart2_read(void);

#endif /* UART_H_ */

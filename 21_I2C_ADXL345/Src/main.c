#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "adxl345.h"

/*
 * PB8/SCL/D15 ----- SCL
 * PB9/SDA/D14 ----- SDA
 * 5V 		   ----- VCC
 * GND 		   ----- GND
 */


int16_t x,y,z;
double xg, yg, zg;

extern uint8_t data_rec[6];
void i2c_bus_scan(void);
void delay(int ms);

int main(void)
{

//	uart2_rxtx_init();
//	printf("Test");
//
//	i2c_bus_scan();
	adxl_init();


	while(1)
	{
		adxl_read_values (DATA_START_ADDR);

		 x = ((data_rec[1]<<8)|data_rec[0]);
		 y = ((data_rec[3]<<8)|data_rec[2]);
		 z = ((data_rec[5]<<8)|data_rec[4]);

		xg = (x * 0.0078);
		yg = (y * 0.0078);
		zg = (z * 0.0078);

	}

}


void i2c_bus_scan(void) {
	I2C1_init();
	int a = 0; //address variable
	for (uint8_t i = 0; i < 128; i++) //go through all 127 address
			{
		I2C1->CR1 |= I2C_CR1_START; //generate start
		while (!(I2C1->SR1 & I2C_SR1_SB))
			; // wait to start to be generated
		I2C1->DR = (i << 1 | 0); // transmit the address
		while (!(I2C1->SR1) | !(I2C1->SR2)) {
		}; //clear status register
		I2C1->CR1 |= I2C_CR1_STOP; //generate stop condition
		delay(100); //minium wait time is 40 uS, but for sure, leave it 100 uS
		a = (I2C1->SR1 & I2C_SR1_ADDR); //read the status register address set
		if (a == 2) //if the address is valid
				{
			//print the address
			printf(
					"Found I2C device at adress 0x%X (hexadecimal), or %d (decimal)\r\n",
					i, i);
		}
	}
}

void delay(int ms) {
	SysTick->LOAD = 16000 - 1;
	SysTick->VAL = 0;
	SysTick->CTRL = 0x5;
	for (int i = 0; i < ms; i++) {
		while (!(SysTick->CTRL & 0x10000)) {
		}
	}
	SysTick->CTRL = 0;
}






#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "adxl345.h"

/*
 * PA5/CLK/D13	----- SCL
 * PA7/MOSI/D11	----- SDA
 * PA6/MISO/D12	----- SDO
 * PA9/SS/D8 	----- CS
 * 5V 		 	----- VCC
 * GND 		 	----- GND
 */


int16_t x,y,z;
double xg, yg, zg;

uint8_t data_rec[6];

void delay(int ms);

int main(void)
{


	adxl_init();


	while(1)
	{
		adxl_read(DATA_START_ADDR, data_rec);

		 x = ((data_rec[1]<<8)|data_rec[0]);
		 y = ((data_rec[3]<<8)|data_rec[2]);
		 z = ((data_rec[5]<<8)|data_rec[4]);

		xg = (x * 0.0078);
		yg = (y * 0.0078);
		zg = (z * 0.0078);

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






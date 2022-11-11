#include "input.h"
#include "stm32f4xx.h"
void nes_joy_input(unsigned int* button)
{
	volatile unsigned int i;
	unsigned int j;
	GPIOD->BSRR |= 1 << (13 + 16); //CLK_DOWN
	GPIOD->BSRR |= 1 << 11; //LATCH UP
	IN_DELAY
	GPIOD->BSRR |= 1 << (11 + 16);  //LATCH_DOWN
	IN_DELAY
	for(j = 0; j < 8; j++){
		if (GPIOD->IDR & (1 << 15)) *button |= 1 << j; //DATA READ
		else *button &=~(1 << j);	//DATA READ
		GPIOD->BSRR |= 1 << 13;		//CLK UP
		IN_DELAY
		GPIOD->BSRR |= 1 << (13 + 16); //CLK DOWN
		IN_DELAY		
	}	
}

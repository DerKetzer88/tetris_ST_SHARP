#include "stm32f4xx.h"
void GPIOInit(void)
{
		RCC->AHB1ENR |= 0x1F; //ALL ports on
			/* SPI2
		 * PB10 SCK2
		 * PB13 NSS2
		 * PB15 MOSI2
		 */
		RCC->APB1ENR |= 1 << 14; //SPI4 enable;
		RCC->AHB1ENR |= 1 << 4; //GPIOE enable;
		//PB10
		GPIOB->MODER |= 2 << 20; //PE2 AF
		GPIOB->OSPEEDR |= 3 << 20; //high speed
		GPIOB->AFR[1] |= 5 << 8; // AF n 5
		//PB13
		GPIOE->OSPEEDR |= 3 << 26; //high speed
		GPIOB->MODER |= 1 << 26; // GPO
		
		GPIOB->MODER |= 2 << 30; //
		GPIOB->OSPEEDR |= 3 << 30; //high speed
		GPIOB->AFR[1] |= 5 << 28; // AF n 5
		/*	DISPLAY_ON
		* PB14
		*/
		GPIOB->MODER |= 1 << 28; //GPO
		
		//PD0 = disp
		//PD1 = MISO
		//PD2 = SCK
		//PD3 = CS
		
		GPIOD->MODER |= 1 | (1 << 2) | (1 << 4) | (1 << 6);
	
		
		
}
void test(void)
{
	unsigned short fg[20] = {0x00FF,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
		volatile int i, j,k;
		unsigned short sh = 0x0803;
		GPIOD->BSRR |= 1; //DISP
		for (k = 0; k < 1000; k++){}
		GPIOD->BSRR |= 1 << 3; //CS_up
		for (k = 0; k < 1000; k++){}	
		for(i = 0; i < 16; i++)
		{
			if(sh & (1 << i)) GPIOD->BSRR |= 1 << 1;
			else GPIOD->BSRR |=  1 << (1 + 16);
			for (k = 0; k < 1000; k++){}
			GPIOD->BSRR |= 1 << 2;
			for (k = 0; k < 1000; k++){}
			GPIOD->BSRR |= 1 << (2+16);
			for (k = 0; k < 1000; k++){}
		}
		for(j = 0 ;j < 20; j++){
		sh = fg[j];		
			for(i = 0; i < 16; i++)
			{				
				if(sh & (1 << i)) GPIOD->BSRR |= 1 << 1;
				else GPIOD->BSRR |=  1 << (1 + 16);
				for (k = 0; k < 1000; k++){}
				GPIOD->BSRR |= 1 << 2;
				for (k = 0; k < 1000; k++){}
				GPIOD->BSRR |= 1 << (2+16);
				for (k = 0; k < 1000; k++){}
			}
			
		}
		//16ck dummy
		for(i = 0; i < 16; i++)
			{				
				if(sh & (1 << i)) GPIOD->BSRR |= 1 << 1;
				else GPIOD->BSRR |=  1 << (1 + 16);
				for (k = 0; k < 1000; k++){}
				GPIOD->BSRR |= 1 << 2;
				for (k = 0; k < 1000; k++){}
				GPIOD->BSRR |= 1 << (2+16);
				for (k = 0; k < 1000; k++){}
			}
		
		GPIOD->BSRR |= 1 << (3 + 16); //CS_up
		
}
void test1()
{
	unsigned int k = 0,j=0;
	GPIOD->BSRR |= 1; //DISP
	for (k = 0; k < 1000; k++){}
	GPIOD->BSRR |= 1 << 3; //CS_up
	for (k = 0; k < 1000; k++){}	
		
	GPIOD->BSRR |= 1 << 2;
	for (k = 0; k < 1000; k++){}
	GPIOD->BSRR |= 1 << (2+16);
	for (k = 0; k < 1000; k++){}
		
		
	GPIOD->BSRR |= 1 << 1;
	for (k = 0; k < 1000; k++){}	
	GPIOD->BSRR |= 1 << 2;
	for (k = 0; k < 1000; k++){}
	GPIOD->BSRR |= 1 << (2+16);
	for (k = 0; k < 1000; k++){}
	GPIOD->BSRR |=  1 << (1 + 16);
	GPIOD->BSRR |= 1 << 1;	
					
	GPIOD->BSRR |= 1 << 2;
	for (k = 0; k < 1000; k++){}
	GPIOD->BSRR |= 1 << (2+16);
	for (k = 0; k < 1000; k++){}
					
	GPIOD->BSRR |= 1 << 2;
	for (k = 0; k < 1000; k++){}
	GPIOD->BSRR |= 1 << (2+16);
	for (k = 0; k < 1000; k++){}
		
	for(j = 0; j < 12; j++)
		{
			GPIOD->BSRR |= 1 << 2;
			for (k = 0; k < 1000; k++){}
			GPIOD->BSRR |= 1 << (2+16);
			for (k = 0; k < 1000; k++){}
		}
		
	for (k = 0; k < 1000; k++){}
	GPIOD->BSRR |= 1 << (3 + 16); //CS_down
		
}
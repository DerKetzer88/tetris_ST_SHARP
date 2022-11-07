#include "stm32f4xx.h"
#include "disp.h"
extern char g_buf[];
extern const unsigned char rawData[];
//extern const unsigned char hor[];
unsigned short g_line[20] = {1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0};
int main()
{
	volatile int i =0;
	RCC->AHB1ENR |= 1 << 3;
	GPIOD->MODER |= 1 << 30;
	
	for (i = 0; i < 9600 ; i++) g_buf[i] = 0xFF;
	for (i = 0; i < 40; i++) g_buf[i] = 0x00;
	//for (i = 4800; i < 20; i++) g_buf[i] = 0x00;
	

	GPIOInit();
	spi2Init();
	sh_dispEnable();
	//test1();
	//test();
	sh_clearDisp();
	//sh_sendLine(g_line, 100);
	//
	//sh_showData();
	//sh_sendData((short*)g_buf);
	sh_sendDataBMP((short*)(rawData + 62));
	
	
	while(1){
		//for (i = 0; i < 500000; i++) {};
		//	GPIOD->BSRR |= 1 << 15;
		//	for (i = 0; i < 500000; i++) {};
			//	GPIOD->BSRR |= 1 << 31;
				//sh_clearDisp();
		//for (i = 0; i < 500000; i++) {};
		//		sh_sendData((short*)g_buf);
		//	for (i = 0; i < 500000; i++) {};
		
	}
	return (0);
}

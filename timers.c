#include "timers.h"
#include "stm32f4xx.h"
void startTimer3(void)
{
	RCC->APB1ENR |= 1 << 1;
	TIM3->CR1 &= ~1;
	TIM3->PSC = 42000 - 1; //таймер тактируется 42М. поделим на 42000 получим 1 кГЦ
	TIM3->ARR = 0x0000FFFE; //16 bit
	TIM3->CNT = 0;
	//TIM3->DIER |=0x01; //прерывание по апдейту.
	//NVIC_EnableIRQ(TIM3_DAC_IRQn);
	TIM3->CR1 |=1;
}

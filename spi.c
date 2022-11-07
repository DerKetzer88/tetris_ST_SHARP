#include "stm32f4xx.h"
#include "spi.h"

void spi2Init(void)
{
	/*
	 * PB10 SCK2
	 * PB13 NSS2
	 * PB15 MOSI2
	 */

	RCC->APB1ENR |= 1 << 14; //SPI2 enable;

/*	
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
	*/

	SPI2->CR1 &= ~(1 << 6);
	SPI2->CR1 |= 3 << 3 ; // divider = 32 (1MHZ)
	SPI2->CR1 |= 3 << 8; //SSI and SSM bit for software slave select
	SPI2->CR1 |= 1 << 2; //MASTER mode
	SPI2->CR1 |= 1 << 11; //16 bit
	//SPI2->CR1 |= 1 << 7; //LSB first
	SPI2->CR1 |= 1 << 6; //SPI EN
}
void SPIsendByte (SPI_TypeDef* spi, char ch, unsigned int wait_flag, int msb_lsb)
{
	volatile int i = 0;
	while (!(spi->SR & 0x07)){}; //spi not busy
	if(msb_lsb) spi->CR1|= 1 << 7; //LSB_first->
	while(!(spi->SR & 0x02)){}; //tx_buf is empty
	spi->DR = ch;
	if(wait_flag){
		for (i = 0; i < 2000; i++) {};
	}
}
void SPIsend16Bite (SPI_TypeDef* spi, unsigned short sh, unsigned int wait_flag, unsigned int msb_lsb)
{
	int i;
	unsigned short v = 0;
	spi->CR1 |= 1 << 11; //16 bit
	while (!(spi->SR & 0x07)){} //spi not busy
	if(msb_lsb) spi->CR1|= 1 << 7; //LSB_first
	else spi->CR1 &= ~(1 << 7); //LSB_first
	while(!(spi->SR & 0x02)){} //tx_buf is empty
	v = sh;
	spi->DR = sh;
		
	if(wait_flag){
		for(i = 0; i < 30; i++){}
		while(spi->SR & ( 1 << 7)){}
	}
}
void SPIsendBuf(SPI_TypeDef* spi,char* buf,unsigned int len, unsigned int wait_flag)
{
	if(len >0){
		while(len){
			SPIsendByte (spi, *buf, wait_flag,0);
			buf++;
			len--;
		}
	}

}
void SPI1_IRQHandler(void)
{

}
void SPI2_IRQHandler(void)
{

}
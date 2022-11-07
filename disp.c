#include "disp.h"
#include "spi.h"
#include "stm32f4xx.h"

unsigned char g_buf[9600]; //буфер графики. (320 * 240) /8
unsigned int q_sel[8];

int sh_sendLine(unsigned short* data, unsigned int linenum)
{
	int i;
	if(linenum > D_H) return 0;
	unsigned short sh = ((linenum + 1) << 8) | 0x01;
	SH_CS_UP;
	sh_delay(100);
	SPIsend16Bite (SPI2, sh, SPI_nWAIT, SPI_LSB);
	for (i = 0; i < 20; i++) SPIsend16Bite (SPI2, data[i], SPI_nWAIT, SPI_LSB);
	SPIsend16Bite (SPI2, 0x0000, SPI_nWAIT, SPI_LSB);
	sh_delay(100);
	SH_CS_DOWN;
	sh_delay(200);
	return 320;
}
void sh_sendData(short* data)
{
	unsigned short row = 0;
	unsigned int i;
	unsigned short sh;
	
	SH_CS_UP;
	sh_delay(20);
	sh = 0x0001;
	//SPIsend16Bite (SPI2, sh, SPI_WAIT, SPI_LSB); //mode
	for (row = 1; row < 241; row++){
		sh = 0x0001 | (row << 8);
		SPIsend16Bite (SPI2, sh, SPI_WAIT, SPI_LSB);
		for (i = 0; i < 20; i++){
			sh = data[i + 20* (row - 1)];
			SPIsend16Bite (SPI2, sh, SPI_WAIT, SPI_LSB);
		}
	}

	SPIsend16Bite (SPI2, 0x0000, SPI_WAIT, SPI_LSB); //dummy 16 ck
	sh_delay(20);
	SH_CS_DOWN;
}
void sh_sendDataBMP(unsigned short* data)
{
	unsigned short row = 0;
	unsigned short nrow = 240;
	unsigned int i;
	unsigned short sh;
	unsigned short swap;
	
	SH_CS_UP;
	sh_delay(20);
	sh = 0x0001;
	//SPIsend16Bite (SPI2, sh, SPI_WAIT, SPI_LSB); //mode
	for (row = 1; row < 241; row++){
		sh = 0x0001 | (nrow << 8);
		SPIsend16Bite (SPI2, sh, SPI_WAIT, SPI_LSB);
		for (i = 0; i < 20; i++){
			sh = data[i + 20* (row - 1)];
			swap = (sh << 8) | ((sh >> 8) & 0xFF);
			SPIsend16Bite (SPI2, swap, SPI_WAIT, SPI_MSB);
		}
		nrow--;
	}

	SPIsend16Bite (SPI2, 0x0000, SPI_WAIT, SPI_LSB); //dummy 16 ck
	sh_delay(20);
	SH_CS_DOWN;
}
void sh_sendLineSel(short* data, unsigned int* sel)
{
	unsigned int row;
	unsigned int i;
	short sh;
	SH_CS_UP;
	sh = 0x00001;
	SPIsend16Bite (SPI2, sh, SPI_nWAIT, SPI_LSB);
	for (row = 0; row < D_H; row++){
		if(sel[row/32] & (1 << row%32)) continue; 
		sh = ( (row + 1)<< 8) | 0x01;
		SPIsend16Bite (SPI2, sh, SPI_nWAIT, SPI_LSB);
		for (i = 0; i < (D_W/2); i++)
			SPIsend16Bite (SPI2, data[i * row], SPI_nWAIT, SPI_LSB);
	}
	SPIsend16Bite (SPI2, 0x0000, SPI_nWAIT, SPI_LSB);
	SH_CS_DOWN;
}
void sh_showData(void)
{
	SH_CS_UP;
	sh_delay(10);
	SPIsend16Bite (SPI2, 0x0000, SPI_WAIT, SPI_MSB);
	sh_delay(10);
	SH_CS_DOWN;
}
void sh_clearDisp()
{
	SH_CS_UP;
	sh_delay(100);
	SPIsend16Bite (SPI2, 0x0004, SPI_WAIT, SPI_LSB);
	sh_delay(100);
	SH_CS_DOWN;
}
void sh_delay(int cyc)
{
	while(cyc--){}
}
void sh_dispEnable()
{
	GPIOB->BSRR |= 1 << 14;
	
}
void sh_dispDisable(void)
{
	GPIOB->BSRR |= 1 << (14 + 16);
	
}
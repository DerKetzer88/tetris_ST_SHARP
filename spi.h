#ifndef SPI_H
#define SPI_H
#include "stm32f4xx.h"

#define SPI2_LEN
#define SPI2_CON

#define SPI_WAIT 1
#define SPI_nWAIT 0
#define SPI_LSB 1
#define SPI_MSB 0
void spi4Init(void);
void SPIsend16Bite (SPI_TypeDef* spi, unsigned short sh, unsigned int wait_flag, unsigned int msb_lsb);
#endif
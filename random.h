#ifndef RANDOM_H_
#define RANDOM_H_
/*
	random funtions used GPIOC0 and ADC1
*/
void randomInit(void);
unsigned int random(unsigned int capacity);
#endif

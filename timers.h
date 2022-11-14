#ifndef TIMERS_H_
#define TIMERS_H_
#include "stm32f4xx.h"

#define SYS_TIME TIM2->CNT
void startTimer3(void);

#endif
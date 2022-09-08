#ifndef _TIMER_H
#define _TIMER_H
#include "stm8s_tim1.h"
#include "stm8s_tim2.h"
#include "stm8s_tim4.h"
#include "Arduino.h"

typedef void(*Timer_CallbackFunction_t)(void);


void TIM4_Init(void);
uint32_t millis(void);

void Timer_SetInterrupt(uint32_t Time, Timer_CallbackFunction_t Function);




#endif
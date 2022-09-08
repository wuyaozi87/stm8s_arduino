#ifndef _ENCODER_H
#define _ENCODER_H

#include "stm8s_tim1.h"
#include "stm8s_gpio.h"

void Encode_Init(void);
uint16_t Encoder_GetCounter(void);
void Encoder_SetCounter(uint16_t Counter);
uint8_t Encoder_Dir();



#endif



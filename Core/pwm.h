#ifndef _PWM_H
#define _PWM_H

#include "stm8s_tim2.h"
#include "stm8s_tim1.h"
#include "Arduino.h"

int PWM_Init(uint8_t pin,uint16_t PWM_DutyCycle, uint32_t PWM_Frequency);
void pwmWrite(uint8_t pin, uint16_t val);


#endif
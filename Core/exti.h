#ifndef _EXTI_H
#define _EXTI_H


#include "stm8s_exti.h"
#include "arduino.h"

typedef void(*EXTI_CallbackFunction_t)(void);


void attachInterrupt(uint8_t pin,EXTI_CallbackFunction_t Function, EXTI_Sensitivity_TypeDef SensitivityValue = EXTI_SENSITIVITY_FALL_ONLY);


#endif
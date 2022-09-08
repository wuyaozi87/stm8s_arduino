#ifndef __ARDUINO_H
#define __ARDUINO_H

#include "stm8s.h"
#include "exti.h"
#include "gpio.h"
#include "uart.h"
#include "pwm.h"
#include "timer.h"
#include "spi.h"

#include "TMT.h"
#include "SSD1306.h"
#include "BM8563.h"
#include "mini-printf.h"
#include "menu.h"
#include "HAL_Encoder.h"
#include "ds18b20.h"
#include "IRremote.h"


#define LOW                     0x0
#define HIGH                    0x1



#define PWM_RESOLUTION_DEFAULT        1000
#define PWM_FREQUENCY_DEFAULT         10000

void pinMode(uint8_t pin, PinMode_TypeDef mode);
uint8_t analogWrite(uint8_t pin, uint16_t val);

void delay_us(unsigned int xus);
void delay_ms(unsigned int time);
int xsprintf(char * str, const char *fmt, ...);


#endif
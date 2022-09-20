#ifndef __DS18B20_H
#define __DS18B20_H

#include "Arduino.h"


#define DS18B20_GPIO    GPIOA
#define DS18B20_PIN     GPIO_PIN_3


#define set_dq_low      DS18B20_GPIO->ODR &= (uint8_t)(~DS18B20_PIN)
#define set_dq_high     DS18B20_GPIO->ODR |= (uint8_t)DS18B20_PIN

#define dq_out          DS18B20_GPIO->DDR |= (uint8_t)DS18B20_PIN
#define dq_in           DS18B20_GPIO->CR1 |= (uint8_t)DS18B20_PIN

#define dq_read         DS18B20_GPIO->IDR & (uint8_t)DS18B20_PIN




uint16_t get_temp();





#endif

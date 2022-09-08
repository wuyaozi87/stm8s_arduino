#ifndef _GPIO_H
#define _GPIO_H

#include "stm8s_gpio.h"
#include "stm8s_adc1.h"


#define ADC1_CHANNEL_X ((uint8_t)0xFF)

#define NOT_A_PIN                    0x00
#define NOT_A_PORT                   0x00

#ifndef NULL
#  define NULL 0
#endif

typedef enum {
    PA1, PA2, PA3, 
    PB4, PB5, 
    PC3, PC4, PC5, PC6, PC7,
    PD1, PD2, PD3, PD4, PD5, PD6,
    PIN_MAX
} Pin_TypeDef;

typedef struct STM8_PinInfo {
   
    GPIO_TypeDef* GPIOx;
    TIM1_struct* TIM1x;
    TIM2_struct* TIM2x;    
    ADC1_TypeDef* ADCx;

    GPIO_Pin_TypeDef GPIO_PIN_x;
    uint8_t TimerChannel;
    uint8_t ADC_Channel;
    uint8_t GPIOGroupNum;
} PinInfo_TypeDef;


extern const PinInfo_TypeDef PIN_MAP[PIN_MAX];

typedef enum
{   
    INPUT_PULLUP,
    INPUT_NO_IT,
    OUTPUT,
    OUTPUT_OPEN_DRAIN,
    PWM
} PinMode_TypeDef;


#define IS_PIN(Pin)     (Pin < PIN_MAX)
#define IS_ADC_PIN(Pin) (IS_PIN(Pin) && PIN_MAP[Pin].ADCx != NULL && PIN_MAP[Pin].ADC_Channel  != ADC_Channel_X)
#define IS_PWM_PIN(Pin) (IS_PIN(Pin) && PIN_MAP[Pin].TIM1x != NULL || PIN_MAP[Pin].TIM2x != NULL && PIN_MAP[Pin].TimerChannel != 0)

void GPIOx_Init(uint8_t pin, PinMode_TypeDef mode);
void digitalWrite(uint8_t pin,uint8_t value);
void digitalWrite_HIGH(uint8_t pin);
void digitalWrite_LOW(uint8_t pin);
void digitalWriteReverse(uint8_t pin);
BitStatus digitalRead(uint8_t pin);
#endif
#include "gpio.h"


const PinInfo_TypeDef PIN_MAP[PIN_MAX] =
{
   
    {GPIOA, NULL,NULL, NULL,  GPIO_PIN_1, 0, ADC1_CHANNEL_X,0}, /* PA1 */
    {GPIOA, NULL,NULL, NULL,  GPIO_PIN_2, 0, ADC1_CHANNEL_X,0}, /* PA2 */
    {GPIOA, NULL,TIM2, NULL,  GPIO_PIN_3, 3, ADC1_CHANNEL_X,0}, /* PA3 */
        
    {GPIOB, NULL,NULL, NULL,  GPIO_PIN_4, 0, ADC1_CHANNEL_X,1}, /* PB4 */
    {GPIOB, NULL,NULL, NULL,  GPIO_PIN_5, 0, ADC1_CHANNEL_X,1}, /* PB5 */
 
    {GPIOC, TIM1,NULL, NULL,  GPIO_PIN_3, 3, ADC1_CHANNEL_X,2},/* PC3 */
    {GPIOC, TIM1,NULL, ADC1,  GPIO_PIN_4, 4, ADC1_CHANNEL_2,2},/* PC4 */
    {GPIOC, NULL,NULL, NULL,  GPIO_PIN_5, 0, ADC1_CHANNEL_X,2},/* PC5 */
    {GPIOC, NULL,NULL, NULL,  GPIO_PIN_6, 0, ADC1_CHANNEL_X,2}, /* PC6 */
    {GPIOC, NULL,NULL, NULL,  GPIO_PIN_7, 0, ADC1_CHANNEL_X,2}, /* PC7 */
     
    {GPIOD, NULL, NULL,NULL,  GPIO_PIN_1, 0, ADC1_CHANNEL_X,3}, /* PD1 */
    {GPIOD, NULL,TIM2, ADC1,  GPIO_PIN_2, 3, ADC1_CHANNEL_3,3}, /* PD2 */
    {GPIOD, NULL,TIM2, ADC1,  GPIO_PIN_3, 2, ADC1_CHANNEL_4,3}, /* PD3 */
    {GPIOD, NULL,TIM2, NULL,  GPIO_PIN_4, 1, ADC1_CHANNEL_X,3}, /* PD4 */
    {GPIOD, NULL,NULL, ADC1,  GPIO_PIN_5, 0, ADC1_CHANNEL_5,3}, /* PD5 */
    {GPIOD, NULL,NULL, ADC1,  GPIO_PIN_6, 0, ADC1_CHANNEL_6,3}, /* PD6 */
    
};


void GPIOx_Init(uint8_t pin, PinMode_TypeDef mode)
{
  GPIO_Mode_TypeDef GPIO_Mode;
    
  if(mode == OUTPUT)
  {GPIO_Mode = GPIO_MODE_OUT_PP_HIGH_FAST;}
  
  else if(mode == INPUT_PULLUP)
  {GPIO_Mode = GPIO_MODE_IN_PU_IT;}
    
  else if (mode == OUTPUT_OPEN_DRAIN)
  {GPIO_Mode = GPIO_MODE_OUT_OD_HIZ_FAST;}
  
  else if (mode == INPUT_NO_IT)
  {GPIO_Mode =  GPIO_MODE_IN_PU_NO_IT;}
  
  GPIO_Init(PIN_MAP[pin].GPIOx,PIN_MAP[pin].GPIO_PIN_x,GPIO_Mode);
     
}


void digitalWrite(uint8_t pin,uint8_t value)
{
  
    if(!IS_PIN(pin))
    {
        return;
    }

    value ? digitalWrite_HIGH(pin) : digitalWrite_LOW(pin);

}


void digitalWrite_HIGH(uint8_t pin)
{


  PIN_MAP[pin].GPIOx->ODR |= (uint8_t)PIN_MAP[pin].GPIO_PIN_x;

}

void digitalWrite_LOW(uint8_t pin)
{

  PIN_MAP[pin].GPIOx->ODR &= (uint8_t)(~PIN_MAP[pin].GPIO_PIN_x);

}

void digitalWriteReverse(uint8_t pin)
{

  PIN_MAP[pin].GPIOx->ODR ^= (uint8_t)PIN_MAP[pin].GPIO_PIN_x;

}


BitStatus digitalRead(uint8_t pin)
{
  
    return (BitStatus)(PIN_MAP[pin].GPIOx->IDR & (uint8_t)PIN_MAP[pin].GPIO_PIN_x);
}



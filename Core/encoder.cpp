#include "Encoder.h"


void Encoder_Init()
{
    GPIO_Init(GPIOC,GPIO_PIN_6,GPIO_MODE_IN_PU_NO_IT);
    GPIO_Init(GPIOC,GPIO_PIN_7,GPIO_MODE_IN_PU_NO_IT);
 
    TIM1_TimeBaseInit(0x0000, TIM1_COUNTERMODE_UP, 100, 0x00);

    TIM1_EncoderInterfaceConfig(TIM1_ENCODERMODE_TI12, TIM1_ICPOLARITY_FALLING, TIM1_ICPOLARITY_FALLING);
    TIM1_ICInit(TIM1_CHANNEL_1, TIM1_ICPOLARITY_FALLING, TIM1_ICSELECTION_DIRECTTI, TIM1_ICPSC_DIV1, 0x00);
    TIM1_ICInit(TIM1_CHANNEL_2, TIM1_ICPOLARITY_FALLING, TIM1_ICSELECTION_DIRECTTI, TIM1_ICPSC_DIV1, 0x00);
    TIM1_ARRPreloadConfig(ENABLE);
    TIM1_Cmd(ENABLE);
 
    
}

uint16_t Encoder_GetCounter(void)
{
  uint16_t tmpcntr = 0;
  
  tmpcntr = ((uint16_t)TIM1->CNTRH << 8);
   
  /* Get the Counter Register value */
    return (uint16_t)(tmpcntr | (uint16_t)(TIM1->CNTRL));
}


void Encoder_SetCounter(uint16_t Counter)
{
    /* Set the Counter Register value */
    TIM1->CNTRH = (uint8_t)(Counter >> 8);
    TIM1->CNTRL = (uint8_t)(Counter);

}


uint8_t Encoder_Dir()
{

return (TIM1->CR1 & 0x10);

}





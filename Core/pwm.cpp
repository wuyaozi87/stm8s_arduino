#include "pwm.h"



void TIM2_SetPWM(uint8_t pin,uint16_t PWM_DutyCycle, uint32_t PWM_Frequency)
{     
    TIM2_Prescaler_TypeDef TIM2_Prescaler;   
    uint16_t clock_div = 16000000 / (PWM_DutyCycle * PWM_Frequency); 
    
    if(clock_div <= 1)TIM2_Prescaler = TIM2_PRESCALER_1;
    else if(clock_div <= 2)TIM2_Prescaler = TIM2_PRESCALER_2;
    else if(clock_div <= 4)TIM2_Prescaler = TIM2_PRESCALER_4;
    else if(clock_div <= 8)TIM2_Prescaler = TIM2_PRESCALER_8;
    else if(clock_div <= 16)TIM2_Prescaler = TIM2_PRESCALER_16;
    else if(clock_div <= 32)TIM2_Prescaler = TIM2_PRESCALER_32;
    else if(clock_div <= 64)TIM2_Prescaler = TIM2_PRESCALER_64;
    else if(clock_div <= 128)TIM2_Prescaler = TIM2_PRESCALER_128;
    else if(clock_div <= 256)TIM2_Prescaler = TIM2_PRESCALER_256;
    else if(clock_div <= 512)TIM2_Prescaler = TIM2_PRESCALER_512;
    else if(clock_div <= 1024)TIM2_Prescaler = TIM2_PRESCALER_1024;
    else if(clock_div <= 2048)TIM2_Prescaler = TIM2_PRESCALER_2048;
    else if(clock_div <= 4096)TIM2_Prescaler = TIM2_PRESCALER_4096;
    else if(clock_div <= 8192)TIM2_Prescaler = TIM2_PRESCALER_8192;
    else if(clock_div <= 16384)TIM2_Prescaler = TIM2_PRESCALER_16384;       
    else TIM2_Prescaler = TIM2_PRESCALER_32768;
      
    TIM2_TimeBaseInit(TIM2_Prescaler, PWM_DutyCycle);
        
      switch(PIN_MAP[pin].TimerChannel)
    {
    case 1:
            TIM2_OC1Init(TIM2_OCMODE_PWM1, TIM2_OUTPUTSTATE_ENABLE, 0, TIM2_OCPOLARITY_HIGH);
            TIM2_OC1PreloadConfig(ENABLE);
        break;
    case 2:
            TIM2_OC2Init(TIM2_OCMODE_PWM1, TIM2_OUTPUTSTATE_ENABLE, 0, TIM2_OCPOLARITY_HIGH);
            TIM2_OC2PreloadConfig(ENABLE);
        break;
    case 3:
           TIM2_OC3Init(TIM2_OCMODE_PWM1, TIM2_OUTPUTSTATE_ENABLE, 0, TIM2_OCPOLARITY_HIGH);
           TIM2_OC3PreloadConfig(ENABLE);
        break;

    }
    
    TIM2_Cmd(ENABLE);//使能定时器
}






void TIM1_SetPWM(uint8_t pin,uint16_t PWM_DutyCycle, uint32_t PWM_Frequency)
{
     
     uint16_t TIM1_Prescaler;
     
     TIM1_Prescaler =  16000000 / (PWM_DutyCycle * PWM_Frequency); 
  
     TIM1_TimeBaseInit(TIM1_Prescaler,TIM1_COUNTERMODE_UP,PWM_DutyCycle,0x00);   
       
      switch(PIN_MAP[pin].TimerChannel)
    {
    case 1:
          TIM1_OC1Init(TIM1_OCMODE_PWM1, 
                       TIM1_OUTPUTSTATE_ENABLE, 
                       TIM1_OUTPUTNSTATE_DISABLE, 
                       0, 
                       TIM1_OCPOLARITY_HIGH, 
                       TIM1_OCNPOLARITY_HIGH,
                       TIM1_OCIDLESTATE_SET, 
                       TIM1_OCNIDLESTATE_SET);   
        break;
    case 2:
          TIM1_OC2Init(TIM1_OCMODE_PWM1, 
                       TIM1_OUTPUTSTATE_ENABLE, 
                       TIM1_OUTPUTNSTATE_DISABLE, 
                       0, 
                       TIM1_OCPOLARITY_HIGH, 
                       TIM1_OCNPOLARITY_HIGH,
                       TIM1_OCIDLESTATE_SET, 
                       TIM1_OCNIDLESTATE_SET);   
        break;
    case 3:
          TIM1_OC3Init(TIM1_OCMODE_PWM1, 
                       TIM1_OUTPUTSTATE_ENABLE, 
                       TIM1_OUTPUTNSTATE_DISABLE, 
                       0, 
                       TIM1_OCPOLARITY_HIGH, 
                       TIM1_OCNPOLARITY_HIGH,
                       TIM1_OCIDLESTATE_SET, 
                       TIM1_OCNIDLESTATE_SET);   
        break;
    case 4:
          TIM1_OC4Init(TIM1_OCMODE_PWM1, TIM1_OUTPUTSTATE_ENABLE, 0x0000, TIM1_OCPOLARITY_HIGH, TIM1_OCIDLESTATE_SET);
  
        break;
    }

      TIM1_Cmd(ENABLE);
      TIM1_CtrlPWMOutputs(ENABLE);
}




int PWM_Init(uint8_t pin,uint16_t PWM_DutyCycle, uint32_t PWM_Frequency)
{
   
  if(!IS_PWM_PIN(pin))
        return 0;
  
 
  if(PIN_MAP[pin].GPIOGroupNum == 2)
  {
      //TIM1
      TIM1_SetPWM(pin, PWM_DutyCycle, PWM_Frequency);
  }
  else
  {
     //TIM2
    
      TIM2_SetPWM(pin, PWM_DutyCycle, PWM_Frequency);
  
  }
  
  return 1;

}






void TIM1_Write(uint8_t pin, uint16_t val)
{
  
          switch(PIN_MAP[pin].TimerChannel)
    {
    case 1:
            TIM1->CCR1H = (uint8_t)(val >> 8);
            TIM1->CCR1L = (uint8_t)(val);
        break;
    case 2:
            TIM1->CCR2H = (uint8_t)(val >> 8);
            TIM1->CCR2L = (uint8_t)(val);
        break;
    case 3:
            TIM1->CCR3H = (uint8_t)(val >> 8);
            TIM1->CCR3L = (uint8_t)(val);
        break;
    
    case 4:
        TIM1->CCR4H = (uint8_t)(val >> 8);
        TIM1->CCR4L = (uint8_t)(val);
    break;    

    }
  
  
  


}

void TIM2_Write(uint8_t pin, uint16_t val)
{

        switch(PIN_MAP[pin].TimerChannel)
    {
    case 1:
            TIM2->CCR1H = (uint8_t)(val >> 8);
            TIM2->CCR1L = (uint8_t)(val);
        break;
    case 2:
            TIM2->CCR2H = (uint8_t)(val >> 8);
            TIM2->CCR2L = (uint8_t)(val);
        break;
    case 3:
            TIM2->CCR3H = (uint8_t)(val >> 8);
            TIM2->CCR3L = (uint8_t)(val);
        break;

    }
  
  

}


/**
  * @brief  输出PWM信号
  * @param  Pin: 引脚编号
  * @param  val:PWM占空比值
  * @retval PWM占空比值
  */
void pwmWrite(uint8_t pin, uint16_t val)
{
    
   
  if(PIN_MAP[pin].GPIOGroupNum == 2)
  {
      //TIM1
      TIM1_Write(pin, val);
  }
  else
  {
     //TIM2
    
      TIM2_Write(pin, val);
  
  }
    
  
}




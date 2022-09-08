#include "timer.h"


static Timer_CallbackFunction_t Timer_CallbackFunction;


static void Timer_TimeFactorization(
    uint32_t time,
    uint32_t clock,
    uint16_t* factor1,
    uint16_t* factor2
)
{
    const uint32_t cyclesPerMicros = clock / 1000000U;
    const uint32_t prodect = time * cyclesPerMicros;
    uint16_t fct1, fct2;

    if(prodect < cyclesPerMicros * 30)
    {
        fct1 = 10;
        fct2 = prodect / 10;
    }
    else if(prodect < 65535 * 1000)
    {
        fct1 = prodect / 1000;
        fct2 = prodect / fct1;
    }
    else
    {
        fct1 = prodect / 20000;
        fct2 = prodect / fct1;
    }
    *factor1 = fct1;
    *factor2 = fct2;
}

  uint16_t period = 0;
  uint16_t prescaler = 0;  

void Timer_SetInterrupt(uint32_t Time, Timer_CallbackFunction_t Function)
{
   
  Timer_TimeFactorization(Time * 1000, 16000000, &period, &prescaler);
    
  TIM1_TimeBaseInit(period,TIM1_COUNTERMODE_UP,prescaler,0);
  TIM1_ARRPreloadConfig(ENABLE);//使能自动重装
  TIM1_ITConfig(TIM1_IT_UPDATE , ENABLE);//数据更新中断
  TIM1_Cmd(ENABLE);//开定时器
  
  Timer_CallbackFunction = Function ;
    
}



__IO uint32_t current_millis = 0; 

void TIM4_Init(void)
{
       
	TIM4_TimeBaseInit(TIM4_PRESCALER_128, 124);
	/* Clear TIM4 update flag */
	TIM4_ClearFlag(TIM4_FLAG_UPDATE);
	/* Enable update interrupt */
	TIM4_ITConfig(TIM4_IT_UPDATE, ENABLE);

	/* enable interrupts */
	enableInterrupts();

	/* Enable TIM4 */
	TIM4_Cmd(ENABLE);  
}


uint32_t millis(void)
{
	return current_millis;
}




#pragma vector=0xD
__interrupt void TIM1_UPD_OVF_TRG_BRK_IRQHandler(void)
{
  
  Timer_CallbackFunction();
  TIM1_ClearITPendingBit(TIM1_IT_UPDATE);
  
  
  
}
#pragma vector=0xE
__interrupt void TIM1_CAP_COM_IRQHandler(void)
{
  

  
  
}

#pragma vector=0xF
__interrupt void TIM2_UPD_OVF_BRK_IRQHandler(void)
{
     
}
#pragma vector=0x10
__interrupt void TIM2_CAP_COM_IRQHandler(void)
{
  
}


#pragma vector=0x19
__interrupt void TIM4_UPD_OVF_IRQHandler(void)
{
  	
  
    tmt.tick();
    
    current_millis ++;
	
	TIM4_ClearITPendingBit(TIM4_IT_UPDATE);
  
}


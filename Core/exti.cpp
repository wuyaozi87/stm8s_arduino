#include "exti.h"


static EXTI_CallbackFunction_t EXTI_Function[4] = {0};

void attachInterrupt(uint8_t pin,EXTI_CallbackFunction_t Function, EXTI_Sensitivity_TypeDef SensitivityValue)
{
      

	EXTI_Function[PIN_MAP[pin].GPIOGroupNum] = Function;
	
    EXTI_SetExtIntSensitivity((EXTI_Port_TypeDef)PIN_MAP[pin].GPIOGroupNum, SensitivityValue); //设置中断管脚 下降沿触发
		
	__enable_interrupt(); 			
}


#define EXTIx_IRQHANDLER(n)  if(EXTI_Function[n]) EXTI_Function[n]();


#pragma vector=5
__interrupt void EXTI_PORTA_IRQHandler(void)
{
	
	EXTIx_IRQHANDLER(0);
  
}
#pragma vector=6
__interrupt void EXTI_PORTB_IRQHandler(void)
{
  
  EXTIx_IRQHANDLER(1);
}
#pragma vector=7
__interrupt void EXTI_PORTC_IRQHandler(void)
{
	
  EXTIx_IRQHANDLER(2);
}

#pragma vector=8
__interrupt void EXTI_PORTD_IRQHandler(void)
{

  EXTIx_IRQHANDLER(3);
  
}
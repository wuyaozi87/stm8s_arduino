#include "Arduino.h"





void setup()
{  
  

 

}



void loop()
{ 
  

}




int main(void)
{
  /* Infinite loop */
  CLK->CKDIVR&= (uint8_t)(~0x18);/*ʱ�Ӹ�λ*/
  /*�����ڲ�����ʱ��16MΪ��ʱ��*/ 
  CLK->CKDIVR|= (uint8_t)0x00;
  /* millis()����ʹ�õĶ�ʱ�� */ 
  TIM4_Init();
  
  setup();
  for(;;)loop();
}





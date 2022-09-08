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
  CLK->CKDIVR&= (uint8_t)(~0x18);/*时钟复位*/
  /*设置内部高速时钟16M为主时钟*/ 
  CLK->CKDIVR|= (uint8_t)0x00;
  /* millis()函数使用的定时器 */ 
  TIM4_Init();
  
  setup();
  for(;;)loop();
}





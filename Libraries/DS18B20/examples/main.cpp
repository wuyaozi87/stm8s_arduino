#include "Arduino.h"

//由于输出是浮点型 暂时没有写如何输出 可以把浮点型转成整形或者字符型，然后在串口或者屏幕输出 目前只能用调式器看
	
float temp = 0;	


void setup()
{  
 
}



void loop()
{ 
  
  temp = ds.get_temp();
  delay_ms(1000);
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





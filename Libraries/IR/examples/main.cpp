#include "Arduino.h"

uint8_t codedata;

void setup()
{  
  
  SCREEN.begin();
  SCREEN.fillScreen(SCREEN.BLACK);
  ir_begin(); 
}



void loop()
{ 

  char buf[5];
  codedata = ir_receive();
  mini_snprintf(buf,sizeof(buf),"0x%02X",codedata);
  SCREEN.ShowChar(4,45,(const uint8_t *)buf);
    
}




int main(void)
{
  /* Infinite loop */
  CLK->CKDIVR&= (uint8_t)(~0x18);/*时钟复位*/
  /*设置内部高速时钟16M为主时钟*/ 
  CLK->CKDIVR|= (uint8_t)0x00;
  /* millis()函数使用的定时器 */ 
//  TIM4_Init();
  
  setup();
  for(;;)loop();
}





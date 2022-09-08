#include "Arduino.h"



void setup()
{  
  
  SCREEN.begin();
  SCREEN.fillScreen(SCREEN.BLACK);

  Encoder_init();
 
  disp_menu();//菜单初始化
  
  tmt.create(select_scan,30); //创建菜单按键扫描任务
  
  Timer_SetInterrupt(10,Encoder_Update); //创建编码器中键按键更新任务 目的是在进入菜单任务后能响应“返回”“确认”

}



void loop()
{ 
  
  tmt.run();

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





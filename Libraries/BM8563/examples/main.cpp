#include "Arduino.h"

void refresh_time()
{
	char buf[9] = {0};
	BM8563_TimeTypeDef timeStruct;
	rtc.get_time(&timeStruct);
	mini_snprintf(buf,sizeof(buf),"%02d:%02d:%02d",timeStruct.hours,timeStruct.minutes,timeStruct.seconds);
	SCREEN.ShowChar(5,32,(const uint8_t*)buf);
}


void refresh_date()
{
	char buf[9] = {0};
	BM8563_DateTypeDef dateStruct;
	rtc.get_date(&dateStruct);
	mini_snprintf(buf,sizeof(buf),"%02d/%02d/%02d",dateStruct.year,dateStruct.month,dateStruct.date);
	SCREEN.ShowChar(3,32,(const uint8_t*)buf);
}
	
	
	


void setup()
{  
  
  SCREEN.begin();
  SCREEN.fillScreen(SCREEN.BLACK);
  
  rtc.begin();
	
  tmt.create(refresh_time,1000);
  tmt.create(refresh_date,10000);
  
  
 

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





#include "Arduino.h"


/**
  * @brief  配置引脚输入输出模式
  * @param  pin: 引脚编号
  * @param  PinMode_x: 模式
  * @retval 无
  */
void pinMode(uint8_t pin, PinMode_TypeDef mode)
{

   if(mode == PWM)
    {
        PWM_Init(pin, PWM_RESOLUTION_DEFAULT, PWM_FREQUENCY_DEFAULT);
    }
    else
    {
		GPIOx_Init(pin,mode);
    }
}



/**
  * @brief  将模拟值(PWM占空比)写入引脚
  * @param  Pin: 引脚编号
  * @param  val: PWM占空比
  * @retval PWM占空比
  */
uint8_t analogWrite(uint8_t pin, uint16_t val)
{
    if(!IS_PIN(pin))
        return 0;
    
    
    if(!IS_PWM_PIN(pin))
        return 0;
      
    pwmWrite(pin, val);return 1;
}





//---  微秒级延时--------------------------   
static void delayus(void)   
{    
    //一个asm("nop")函数经过示波器测试代表100ns 
    asm("nop");
    asm("nop");
    asm("nop");   
    asm("nop");
}   

//---  微秒级延时--------------------------   
void delay_us(unsigned int xus)   
{    
    unsigned int i;
	for(i=0;i<xus;i++)
	{
	asm("nop");   
    asm("nop");
    asm("nop");
	}
    
} 

//---- 毫秒级延时程序-----------------------   
void delay_ms(unsigned int time)   
{   
    unsigned int i;   
    while(time--)     
    for(i=900;i>0;i--)   
    delayus();    
}






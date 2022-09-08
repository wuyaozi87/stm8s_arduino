#include "Arduino.h"


/**
  * @brief  ���������������ģʽ
  * @param  pin: ���ű��
  * @param  PinMode_x: ģʽ
  * @retval ��
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
  * @brief  ��ģ��ֵ(PWMռ�ձ�)д������
  * @param  Pin: ���ű��
  * @param  val: PWMռ�ձ�
  * @retval PWMռ�ձ�
  */
uint8_t analogWrite(uint8_t pin, uint16_t val)
{
    if(!IS_PIN(pin))
        return 0;
    
    
    if(!IS_PWM_PIN(pin))
        return 0;
      
    pwmWrite(pin, val);return 1;
}





//---  ΢�뼶��ʱ--------------------------   
static void delayus(void)   
{    
    //һ��asm("nop")��������ʾ�������Դ���100ns 
    asm("nop");
    asm("nop");
    asm("nop");   
    asm("nop");
}   

//---  ΢�뼶��ʱ--------------------------   
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

//---- ���뼶��ʱ����-----------------------   
void delay_ms(unsigned int time)   
{   
    unsigned int i;   
    while(time--)     
    for(i=900;i>0;i--)   
    delayus();    
}






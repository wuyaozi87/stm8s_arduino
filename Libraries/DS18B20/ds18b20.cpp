#include "ds18b20.h"


static uint8_t read_byte()
{
  uint8_t i=0,TempData=0;
	for(i=0;i<8;i++)
	{
	 TempData>>=1;//从低位开始读
	 dq_out;
	 set_dq_low;
	 delay_us(4);
	 set_dq_high;
	 delay_us(10);
	 dq_in;
		
	 if(dq_read)
	  {
		TempData|=0x80;
	  }
	 delay_us(45); 
	}
 return TempData;
}


static void write_byte(uint8_t data)
{
	uint8_t i=0;
	dq_out;//输出

	for(i=0;i<8;i++)
	{
		set_dq_low;	 //拉低
		delay_us(15);//延时15微妙
		
        (data & 0x01) ? set_dq_high : set_dq_low;
        
		delay_us(60);//延时60微妙
		set_dq_high;
		
		data>>=1;//准备下一位数据的发送	
	}
}

static void reset()
{
	dq_out;//输出
	set_dq_low;
	delay_us(480);//延时480微妙	
	set_dq_high;
	delay_us(480);//延时480微妙	
}


uint16_t get_temp()
{

	reset();//复位
	write_byte(0xCC); //跳过ROM命令
	write_byte(0x44); //温度转换命令

	delay_ms(800);//延时800毫秒
	reset();//复位
	write_byte(0xCC); //跳过ROM命令
	write_byte(0xBE); //读温度命令

	uint8_t  TL=read_byte();//LSB
	uint16_t TH=read_byte()<<8;//MSB
			
		
    return (TH|TL)*10>>4;

}


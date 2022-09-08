#include "ds18b20.h"


DS18B20::DS18B20(uint8_t pin):_dq_pin(pin)
{	
}


uint8_t DS18B20::read_byte()
{
  uint8_t i=0,TempData=0;
	for(i=0;i<8;i++)
	{
	 TempData>>=1;//从低位开始读
	 dq_out();
	 set_dq(LOW);
	 delay_us(4);
	 set_dq(HIGH);
	 delay_us(10);
	 dq_in();
		
	 if(digitalRead(_dq_pin))
	  {
		TempData|=0x80;
	  }
	 delay_us(45); 
	}
 return TempData;
}


void DS18B20::write_byte(uint8_t data)
{
	uint8_t i=0;
	dq_out();//输出

	for(i=0;i<8;i++)
	{
		set_dq(LOW);	 //拉低
		delay_us(15);//延时15微妙
		
        (data & 0x01) ? set_dq(HIGH) : set_dq(LOW);
        
		delay_us(60);//延时60微妙
		set_dq(HIGH);
		
		data>>=1;//准备下一位数据的发送	
	}
}

void DS18B20::reset()
{
	dq_out();//输出
	set_dq(LOW);
	delay_us(480);//延时480微妙	
	set_dq(HIGH);
	delay_us(480);//延时480微妙	
}

float DS18B20::get_temp()
{

	this->reset();//复位
	this->write_byte(0xCC); //跳过ROM命令
	this->write_byte(0x44); //温度转换命令

	delay_ms(800);//延时800毫秒
	this->reset();//复位
	this->write_byte(0xCC); //跳过ROM命令
	this->write_byte(0xBE); //读温度命令

	uint8_t TL=this->read_byte();//LSB
	uint8_t TH=this->read_byte();//MSB
			
	uint8_t sign = TH & 0x80;
	int16_t temp = (TH << 8) + TL;
	
	
	if (sign) {
        temp = ((temp ^ 0xffff) + 1) * -1;
    }

    return temp / 16.0;

}


DS18B20 ds(PA3);


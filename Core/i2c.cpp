#include "i2c.h"
#include "Arduino.h"

TwoWire::TwoWire(uint8_t scl, uint8_t sda)
{
    this->_scl_pin = scl;
    this->_sda_pin = sda;
}


TwoWire::~TwoWire()
{
    this->_scl_pin = 0;
    this->_sda_pin = 0;
}


void TwoWire::begin()
{

pinMode(_scl_pin,OUTPUT);
pinMode(_sda_pin,OUTPUT);
	
set_scl(HIGH);
set_sda(HIGH);
}




//产生起始信号
void TwoWire::i2c_start()
{
 sda_out();
 set_scl(HIGH);
 set_sda(HIGH);
 delay_us(5);
 set_sda(LOW);
 delay_us(6);	
 set_scl(LOW);
}

//产生终止信号
void TwoWire::i2c_stop()
{	
 sda_out();
 set_scl(LOW);
 set_sda(LOW);
 set_scl(HIGH);
 delay_us(6);	
 set_sda(HIGH);
 delay_us(6);		
}

//主机产生应答信号
void TwoWire::i2c_send_ack()
{
 sda_out();
 set_scl(LOW);
 set_sda(LOW);
 delay_us(2);	
 set_scl(HIGH);
 delay_us(5);	
 set_scl(LOW);	
}

//主机产生非应答信号
void TwoWire::i2c_send_nack()
{
 sda_out();
 set_scl(LOW);
 set_sda(HIGH);
 delay_us(2);	
 set_scl(HIGH);
 delay_us(5);	
 set_scl(LOW);	 
}

//等待从机应答信号
//返回值：1 接收应答失败
//	 	  0 接收应答成功
bool TwoWire::i2c_get_ack()
{
	
 uint8_t TempTime = 0;
 sda_in();
 set_sda(HIGH);
 delay_us(1);	
 set_scl(HIGH);
 delay_us(1);	
 while(digitalRead(_sda_pin))
 {
		TempTime++;
		if(TempTime>250)
		{
		 this->i2c_stop();
		 return 1;
		}	
 }
set_scl(LOW);
return 0;  
}

//发送一个字节数据
void TwoWire::i2c_send_byte(uint8_t data)
{	
 sda_out(); 
 set_scl(LOW);
 for(uint8_t i=0;i<8;i++)
 {       
      (data & 0x80) ? set_sda(HIGH) : set_sda(LOW);
      data <<= 1;	
      set_scl(HIGH);
      delay_us(2);
      set_scl(LOW);
      delay_us(2);
 }
}


//读取一个字节数据
uint8_t TwoWire::i2c_read_byte(ACK_Status ack)
{
 uint8_t receive=0;
 sda_in();
 for(uint8_t i=0;i<8;i++)
  {
    set_scl(LOW);
    delay_us(2);
    set_scl(HIGH);
    receive<<=1;
    if(digitalRead(_sda_pin))
      receive++;
    delay_us(1);	
      
  }
  if(ack)
    i2c_send_ack();    
  else
     i2c_send_nack();

  return receive;
}

/*stm8s i2c引脚为PB4 PB5由于输出是开漏输出 不能输出高，需外接上拉电阻 模块没有上来电阻 所以暂时用别的引脚代替*/
TwoWire wire(PD6,PD5);

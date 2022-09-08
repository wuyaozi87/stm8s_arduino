#include "BM8563.h"

BM8563::BM8563(uint8_t deviceAddress, TwoWire &i2cPort)
{
  _deviceAddress = deviceAddress;
  _i2cPort = &i2cPort;
}


void BM8563::begin()
{
  _i2cPort->begin();

}


/**
  * @brief  读寄存器地址的值（可连续读多个地址，地址自动累加）
  * @param  RegAddress	:寄存器地址
			DataBuff	：读取的值存放地址指针
			Datalen 	：要读取的数据长度
  * @retval 成功：1 失败：0
  */
bool BM8563::get_reg(uint8_t RegAddress,uint8_t* DataBuff,u16 Datalen)
{

		
	 _i2cPort->i2c_start();
	 _i2cPort->i2c_send_byte(CHIP_WRITE_ADD);
	 if(_i2cPort->i2c_get_ack()) return 0;
	  _i2cPort->i2c_send_byte(RegAddress);
	 if(_i2cPort->i2c_get_ack()) return 0;
	 _i2cPort->i2c_start();
	 _i2cPort->i2c_send_byte(CHIP_READ_ADD);
	 if(_i2cPort->i2c_get_ack()) return 0;
		
	 for(uint8_t i=0;i<Datalen-1;i++)
      {
		*DataBuff = _i2cPort->i2c_read_byte(ACK);
		DataBuff++;
      }
		
	  *DataBuff = _i2cPort->i2c_read_byte(NACK);
	  _i2cPort->i2c_stop();
	  return 1; 
}

/**
  * @brief  设置寄存器地址的值（可连续写多个地址，地址自动累加）
  * @param  RegAddress	: 寄存器地址
			DataBuff	：要写入值存放地址指针
			Datalen 	：要写入的数据长度
  * @retval 成功：1 失败：0
  */
bool BM8563::set_reg(uint8_t RegAddress,uint8_t* DataBuff,u16 Datalen)
{
	
	_i2cPort->i2c_start();
	_i2cPort->i2c_send_byte(CHIP_WRITE_ADD);
	if(_i2cPort->i2c_get_ack()) return 0;
	_i2cPort->i2c_send_byte(RegAddress);
	if(_i2cPort->i2c_get_ack()) return 0;
	 
	for(uint8_t i=0;i<Datalen;i++)
	{
	  _i2cPort->i2c_send_byte(*DataBuff);
      if(_i2cPort->i2c_get_ack()) return 0;
      DataBuff++;
	}
	
	 _i2cPort->i2c_stop();
	return 1; 
	
}

/**
  * @brief  设置时间
  * @param  hour	: 时
			min		：分
			sec 	：秒
  * @retval 成功：1 失败：0
  */
bool BM8563::set_time(BM8563_TimeTypeDef* BM8563_TimeStruct)
{
  uint8_t buf[3] = {0};
  if (BM8563_TimeStruct == 0) {
    return 0;
  }
  
  buf[0] = byteToBcd2(BM8563_TimeStruct->seconds);
  buf[1] = byteToBcd2(BM8563_TimeStruct->minutes);
  buf[2] = byteToBcd2(BM8563_TimeStruct->hours);
  return set_reg(SEC_ADD,buf,3);

	
}

/**
  * @brief  设置日期
  * @param  year	: 年
			month	：月
			day 	：日
			week	：星期
  * @retval 成功：1 失败：0
  */
bool BM8563::set_date(BM8563_DateTypeDef* BM8563_DateStruct)
{
  uint8_t buf[4] = {0};  
  if (BM8563_DateStruct == 0) {
    return 0 ;
  }
    
	buf[0]=byteToBcd2(BM8563_DateStruct->date);
	buf[1]=byteToBcd2(BM8563_DateStruct->weekDay);
	buf[2]=byteToBcd2(BM8563_DateStruct->month);
	buf[3]=byteToBcd2(BM8563_DateStruct->year);
	return set_reg(DATE_ADD,buf,4);	
}

/**
  * @brief  获取日期
  * @param  DataBuff :获取到日期存放的地址
				DataBuff[0]=day;
				DataBuff[1]=week;
				DataBuff[2]=month;
				DataBuff[3]=year;
  * @retval 成功：1 失败：0
  */
bool BM8563::get_date(BM8563_DateTypeDef* BM8563_DateStruct)
{
    uint8_t buf[4] = {0};
    
    get_reg(DATE_ADD,buf,4);
    
    BM8563_DateStruct->date = bcd2ToByte(buf[0] & 0x3f);
    BM8563_DateStruct->weekDay = bcd2ToByte(buf[1] & 0x07);
    BM8563_DateStruct->month = bcd2ToByte(buf[2] & 0x1f);
    BM8563_DateStruct->year = bcd2ToByte(buf[3] & 0xff);
	return 1;
}

/**
  * @brief  获取时间
  * @param  DataBuff :获取到时间存放的地址
			DataBuff[0]=sec;
			DataBuff[1]=min;
			DataBuff[2]=hour;
  * @retval 成功：1 失败：0
  */
bool BM8563::get_time(BM8563_TimeTypeDef* BM8563_TimeStruct)
{
    uint8_t buf[3] = {0};
    
    get_reg(SEC_ADD,buf,3);
    
    BM8563_TimeStruct->seconds = bcd2ToByte(buf[0] & 0x7f);
    BM8563_TimeStruct->minutes = bcd2ToByte(buf[1] & 0x7f);
    BM8563_TimeStruct->hours = bcd2ToByte(buf[2] & 0x3f);
	return 1;	
}

/**
  * @brief  设置闹钟
  * @param  hour ：时
			min	 ：分
  * @retval 成功：1 失败：0
  */
bool BM8563::set_alarm(uint8_t hour, uint8_t min)
{	
	uint8_t Time_Data[4];
	Time_Data[0]=min&0x7f;
	Time_Data[1]=hour&0x7f;
	Time_Data[2]=0|0x80;  	//日期如不设置需要AE=1 AE=0，星期报警有效；AE=1，星期报警无效
	Time_Data[3]=0|0x80;	//星期如不设置需要AE=1 AE=0，星期报警有效；AE=1，星期报警无效	
	return set_reg(MIN_ALM_ADD,Time_Data,4);	
}

/**
  * @brief  获取闹钟
  * @param 	DataBuff闹钟数据存放的地址指针
			DataBuff[0]=min
			DataBuff[1]=hour
  * @retval 成功：1 失败：0
  */
bool BM8563::get_alarm(uint8_t *DataBuff)
{		
	return get_reg(MIN_ALM_ADD,DataBuff,2);		
}


/**
  * @brief  获取闹钟使能状态
  * @param 	
  * @retval 使能：1 失能：0
  */
bool BM8563::get_alarm_enable(void)
{
	uint8_t DataBuff[1];
	get_reg(REG_CTL2_ADD,DataBuff,1);		
	return DataBuff[0]&0x02;	
}


/**
  * @brief  使能闹钟 设置AIE=1
  * @param 	Stat：ENABLE	使能
				：DISABLE	失能
  * @retval 无
  */
void BM8563::set_alarm_enable(FunctionalState State)
{
	uint8_t AIE_ENABLE[1] = {0x02};
	uint8_t AIE_DISABLE[1] ={0x00};	
 	if(State == ENABLE){
	set_reg(REG_CTL2_ADD,AIE_ENABLE,1);
	}
	else
	set_reg(REG_CTL2_ADD,AIE_DISABLE,1);		
}

/**
  * @brief  取消本次闹钟 设置AF=0
  * @param 	无
  * @retval 无
  */
void BM8563::bm8563_AF_clean()
{
	uint8_t REG_BUFF[1]={0};
	get_reg(REG_CTL2_ADD,REG_BUFF,1);
	REG_BUFF[0]=REG_BUFF[0]&0xf7;	
	set_reg(REG_CTL2_ADD,REG_BUFF,1);
		
}

uint8_t BM8563::bcd2ToByte(uint8_t value) {
  uint8_t tmp = 0;
  tmp = ((uint8_t)(value & (uint8_t)0xF0) >> (uint8_t)0x4) * 10;
  return (tmp + (value & (uint8_t)0x0F));
}


uint8_t BM8563::byteToBcd2(uint8_t value) {
  uint8_t bcdhigh = 0;

  while (value >= 10) {
    bcdhigh++;
    value -= 10;
  }

  return ((uint8_t)(bcdhigh << 4) | value);
}


void BM8563::stop()
{
  uint8_t temp[1] = {0x10};
  this->set_reg(0x00,temp,0x01);

}


void BM8563::start()
{
  uint8_t temp[1] = {0x00};
  this->set_reg(0x00,temp,0x01);
}



BM8563 rtc;

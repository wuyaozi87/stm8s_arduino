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
  * @brief  ���Ĵ�����ַ��ֵ���������������ַ����ַ�Զ��ۼӣ�
  * @param  RegAddress	:�Ĵ�����ַ
			DataBuff	����ȡ��ֵ��ŵ�ַָ��
			Datalen 	��Ҫ��ȡ�����ݳ���
  * @retval �ɹ���1 ʧ�ܣ�0
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
  * @brief  ���üĴ�����ַ��ֵ��������д�����ַ����ַ�Զ��ۼӣ�
  * @param  RegAddress	: �Ĵ�����ַ
			DataBuff	��Ҫд��ֵ��ŵ�ַָ��
			Datalen 	��Ҫд������ݳ���
  * @retval �ɹ���1 ʧ�ܣ�0
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
  * @brief  ����ʱ��
  * @param  hour	: ʱ
			min		����
			sec 	����
  * @retval �ɹ���1 ʧ�ܣ�0
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
  * @brief  ��������
  * @param  year	: ��
			month	����
			day 	����
			week	������
  * @retval �ɹ���1 ʧ�ܣ�0
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
  * @brief  ��ȡ����
  * @param  DataBuff :��ȡ�����ڴ�ŵĵ�ַ
				DataBuff[0]=day;
				DataBuff[1]=week;
				DataBuff[2]=month;
				DataBuff[3]=year;
  * @retval �ɹ���1 ʧ�ܣ�0
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
  * @brief  ��ȡʱ��
  * @param  DataBuff :��ȡ��ʱ���ŵĵ�ַ
			DataBuff[0]=sec;
			DataBuff[1]=min;
			DataBuff[2]=hour;
  * @retval �ɹ���1 ʧ�ܣ�0
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
  * @brief  ��������
  * @param  hour ��ʱ
			min	 ����
  * @retval �ɹ���1 ʧ�ܣ�0
  */
bool BM8563::set_alarm(uint8_t hour, uint8_t min)
{	
	uint8_t Time_Data[4];
	Time_Data[0]=min&0x7f;
	Time_Data[1]=hour&0x7f;
	Time_Data[2]=0|0x80;  	//�����粻������ҪAE=1 AE=0�����ڱ�����Ч��AE=1�����ڱ�����Ч
	Time_Data[3]=0|0x80;	//�����粻������ҪAE=1 AE=0�����ڱ�����Ч��AE=1�����ڱ�����Ч	
	return set_reg(MIN_ALM_ADD,Time_Data,4);	
}

/**
  * @brief  ��ȡ����
  * @param 	DataBuff�������ݴ�ŵĵ�ַָ��
			DataBuff[0]=min
			DataBuff[1]=hour
  * @retval �ɹ���1 ʧ�ܣ�0
  */
bool BM8563::get_alarm(uint8_t *DataBuff)
{		
	return get_reg(MIN_ALM_ADD,DataBuff,2);		
}


/**
  * @brief  ��ȡ����ʹ��״̬
  * @param 	
  * @retval ʹ�ܣ�1 ʧ�ܣ�0
  */
bool BM8563::get_alarm_enable(void)
{
	uint8_t DataBuff[1];
	get_reg(REG_CTL2_ADD,DataBuff,1);		
	return DataBuff[0]&0x02;	
}


/**
  * @brief  ʹ������ ����AIE=1
  * @param 	Stat��ENABLE	ʹ��
				��DISABLE	ʧ��
  * @retval ��
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
  * @brief  ȡ���������� ����AF=0
  * @param 	��
  * @retval ��
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

#ifndef _BM8563_H
#define _BM8563_H
 
#include "i2c.h"

/*bm8563开关*/
#define CHIP_STOP 		0x20
#define CHIP_START 		0x00

/*bm8563器件读写地址*/
#define CHIP_READ_ADD 	0xA3
#define CHIP_WRITE_ADD 	0xA2

/*bm8563各个寄存器的地址*/
#define REG_CTL1_ADD 	0x00
#define REG_CTL2_ADD 	0x01
#define SEC_ADD 		0x02
#define MIN_ADD 		0x03
#define HOUR_ADD 		0x04
#define DATE_ADD 		0x05
#define WEEK_ADD 		0x06
#define MONTH_ADD 		0x07
#define YEAR_ADD 		0x08
#define MIN_ALM_ADD 	0x09
#define HOUR_ALM_ADD 	0x0A
#define DATE_ALM_ADD 	0x0B
#define WEEK_ALM_ADD 	0x0C

#define I2C_BM8563_DEFAULT_ADDRESS 0x51




typedef struct
{
  uint8_t hours;
  uint8_t minutes;
  uint8_t seconds;
} BM8563_TimeTypeDef;

typedef struct
{
  uint8_t weekDay;
  uint8_t month;
  uint8_t date;
  uint8_t year;
} BM8563_DateTypeDef;


class BM8563
{
public:
  BM8563(uint8_t deviceAddress = I2C_BM8563_DEFAULT_ADDRESS, TwoWire &i2cPort = wire);
  
  void begin();

  bool set_time(BM8563_TimeTypeDef* BM8563_TimeStruct);
  bool set_date(BM8563_DateTypeDef* BM8563_DateStruct);
  bool get_date(BM8563_DateTypeDef* BM8563_DateStruct);
  bool get_time(BM8563_TimeTypeDef* BM8563_TimeStruct);
  bool set_alarm(uint8_t hour, uint8_t min);
  bool get_alarm(uint8_t *DataBuff);
  bool get_alarm_enable(void);
  void set_alarm_enable(FunctionalState State);
  void bm8563_AF_clean();
  uint8_t bcd2ToByte(uint8_t value);
  uint8_t byteToBcd2(uint8_t value);
  void stop();
  void start();
  
private:
    TwoWire *_i2cPort;
    int _deviceAddress;

    bool get_reg(uint8_t RegAddress,uint8_t* DataBuff,u16 Datalen);
    bool set_reg(uint8_t RegAddress,uint8_t* DataBuff,u16 Datalen);
    
    
};

extern BM8563 rtc;

#endif

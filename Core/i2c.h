#ifndef __I2C_H
#define __I2C_H

#include "stm8s_i2c.h"


#define set_scl(x) digitalWrite(_scl_pin,x)
#define set_sda(x) digitalWrite(_sda_pin,x)

#define sda_out()    pinMode(_sda_pin,OUTPUT)
#define sda_in()     pinMode(_sda_pin,INPUT_NO_IT)

typedef enum{ NACK = 0,ACK = !NACK } ACK_Status;

class TwoWire
{

public:
  TwoWire(uint8_t scl, uint8_t sda);
  ~TwoWire();
  
  void begin();
  void i2c_start();
  void i2c_stop();
  void i2c_send_ack();
  void i2c_send_nack();
  bool i2c_get_ack();
  void i2c_send_byte(uint8_t data);
  uint8_t i2c_read_byte(ACK_Status ack);
  
private:
  uint8_t _scl_pin,_sda_pin;
  

};



extern TwoWire wire;



#endif
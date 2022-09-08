#ifndef __DS18B20_H
#define __DS18B20_H


#include "Arduino.h"

#define set_dq(x) 	digitalWrite(_dq_pin,x)

#define dq_out()    pinMode(_dq_pin,OUTPUT)
#define dq_in()     pinMode(_dq_pin,INPUT_NO_IT)


class DS18B20
{

public:

	DS18B20(uint8_t pin);
	float get_temp();
	void reset();

private:
	uint8_t _dq_pin;
	uint8_t read_byte();
	void write_byte(uint8_t data);
		
};



extern DS18B20 ds;


#endif
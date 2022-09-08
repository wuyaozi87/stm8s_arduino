#ifndef __UART_H
#define	__UART_H

#include "Arduino.h"


class HardwareSerial
{
public:
	void begin(unsigned int baudrate = 9600);
	void SendString(unsigned char* s);
    void printf( char * Data, ... );
		
private:	
	void SendChar(unsigned char dat);
	char *int2char( int value, char *str, unsigned int radix );
    void flaot2char( double value, char *str, unsigned int eps );
    
	
};




extern HardwareSerial Serial1;

#endif /* __UART_H */

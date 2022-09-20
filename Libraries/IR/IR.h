#ifndef __IR_H
#define __IR_H

#include "Arduino.h"

#define _out_pin PA2


uint8_t ir_receive();//红外接收数据处理函
void ir_begin();
void ir_receives(uint8_t* datacode);
#endif
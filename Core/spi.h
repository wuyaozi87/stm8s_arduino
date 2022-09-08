#ifndef __SPI_H
#define __SPI_H

#include "stm8s_spi.h"

class SPI1
{
  public:
      void begin();
      void SendData(uint8_t Data);
      uint8_t ReceiveData();
      
  private:

	
};



extern SPI1 spi;


#endif

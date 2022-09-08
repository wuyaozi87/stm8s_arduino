#include "spi.h"


void SPI1::begin()
{
	
   SPI_Init(SPI_FIRSTBIT_MSB, SPI_BAUDRATEPRESCALER_2, SPI_MODE_MASTER,\
            SPI_CLOCKPOLARITY_HIGH, SPI_CLOCKPHASE_2EDGE, \
            SPI_DATADIRECTION_2LINES_FULLDUPLEX, SPI_NSS_SOFT, 0x07);
   SPI_Cmd(ENABLE);	
		
}

void SPI1::SendData(uint8_t Data)
{	
	SPI->DR = Data;
}



uint8_t SPI1::ReceiveData()
{	
	return ((uint8_t)SPI->DR);
}



SPI1 spi;


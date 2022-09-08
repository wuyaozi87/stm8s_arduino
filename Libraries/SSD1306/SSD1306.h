#ifndef __SSD1306_H
#define __SSD1306_H

#include "Arduino.h"
#include "codetab.h"

typedef enum {SOFTSPI = 0, HDSPI = !SOFTSPI} SPI_Status;
typedef enum {Reverse = 0 ,DisReverse = !Reverse} Show_Mode;

class SSD1306
{   
  
public:
    
    typedef enum
     {
        BLACK = 0x00,
        WHITE = 0xff  
     }color_t;
    
     
  
    SSD1306(uint8_t cs, uint8_t dc, uint8_t rst);
    SSD1306(uint8_t cs, uint8_t dc, uint8_t rst, uint8_t sck, uint8_t mosi); 
  
    void begin();
    void spiWrite(uint8_t data);
    void writeCommand(uint8_t cmd);
    void writeData(uint8_t data);
    void setAddrWindow(unsigned char page,unsigned char column);
    void fillScreen(uint8_t color);
    void ShowBMP(uint8_t page,uint8_t column,const uint8_t *data);
    void ShowChar(uint8_t page,uint8_t column,const uint8_t *data,Show_Mode show_mode = DisReverse);
  
private:
    uint8_t _cs, _dc, _rst, _sck, _mosi;
    SPI_Status _SPI_STATUS;

};

extern SSD1306 SCREEN;

#endif
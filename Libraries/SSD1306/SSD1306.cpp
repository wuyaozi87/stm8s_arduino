#include "SSD1306.h"

#define SCREEN_CS_SET      digitalWrite(_cs,HIGH)
#define SCREEN_DC_SET      digitalWrite(_dc,HIGH)
#define SCREEN_SCK_SET     digitalWrite(_sck,HIGH)
#define SCREEN_MOSI_SET    digitalWrite(_mosi,HIGH)

#define SCREEN_CS_CLR      digitalWrite(_cs,LOW)
#define SCREEN_DC_CLR      digitalWrite(_dc,LOW)
#define SCREEN_SCK_CLR     digitalWrite(_sck,LOW)
#define SCREEN_MOSI_CLR    digitalWrite(_mosi,LOW)

SSD1306::SSD1306(uint8_t cs, uint8_t dc, uint8_t rst):_cs(cs),_dc(dc),_rst(rst),_sck(NOT_A_PIN),_mosi(NOT_A_PIN)
{ 
  _SPI_STATUS = HDSPI;
}

SSD1306::SSD1306(uint8_t cs, uint8_t dc, uint8_t rst, uint8_t sck, uint8_t mosi):_cs(cs),_dc(dc),_rst(rst),_sck(sck),_mosi(mosi)
{ 
  _SPI_STATUS = SOFTSPI;
}

void SSD1306::begin()
{
  
   if(_SPI_STATUS)
    {
      spi.begin();       
    }
    else
    {
      pinMode(_sck, OUTPUT);
      pinMode(_mosi, OUTPUT);
    }

    pinMode(_cs, OUTPUT);
    pinMode(_dc, OUTPUT);
    pinMode(_rst,OUTPUT);

    digitalWrite(_cs, HIGH);

    digitalWrite(_rst, LOW);
    delay_ms(20);
    digitalWrite(_rst, HIGH);
    delay_ms(20);
    
    writeCommand(0xAE);   //display off
    writeCommand(0x20);	//Set Memory Addressing Mode	
    writeCommand(0x10);	//00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
    writeCommand(0xb0);	//Set Page Start Address for Page Addressing Mode,0-7
    writeCommand(0xc8);	//Set COM Output Scan Direction
    writeCommand(0x00);//---set low column address
    writeCommand(0x10);//---set high column address
    writeCommand(0x40);//--set start line address
    writeCommand(0x81);//--set contrast control register
    writeCommand(0x7f);
    writeCommand(0xa1);//--set segment re-map 0 to 127
    writeCommand(0xa6);//--set normal display
    writeCommand(0xa8);//--set multiplex ratio(1 to 64)
    writeCommand(0x3F);//
    writeCommand(0xa4);//0xa4,Output follows RAM content;0xa5,Output ignores RAM content
    writeCommand(0xd3);//-set display offset
    writeCommand(0x00);//-not offset
    writeCommand(0xd5);//--set display clock divide ratio/oscillator frequency
    writeCommand(0xf0);//--set divide ratio
    writeCommand(0xd9);//--set pre-charge period
    writeCommand(0x22); //
    writeCommand(0xda);//--set com pins hardware configuration
    writeCommand(0x12);
    writeCommand(0xdb);//--set vcomh
    writeCommand(0x20);//0x20,0.77xVcc
    writeCommand(0x8d);//--set DC-DC enable
    writeCommand(0x14);//
    writeCommand(0xaf);//--turn on oled panel   
}


void SSD1306::spiWrite(uint8_t data)
{
    for(uint8_t i = 0; i < 8; i++)
    {
        SCREEN_SCK_CLR;
        (data & 0x80) ? SCREEN_MOSI_SET : SCREEN_MOSI_CLR;
        SCREEN_SCK_SET;
        data <<= 1;
    }
}



void SSD1306::writeCommand(uint8_t cmd)
{
    SCREEN_CS_CLR;
    SCREEN_DC_CLR;
    if(_SPI_STATUS)
        spi.SendData(cmd);
    else
        spiWrite(cmd);
    SCREEN_CS_SET;
}


void SSD1306::writeData(uint8_t data)
{
    SCREEN_CS_CLR;
    SCREEN_DC_SET;
    if(_SPI_STATUS)
    {
        spi.SendData(data);
    }
    else
    {
        spiWrite(data);
    }
    SCREEN_CS_SET;
}


/*page:1-8   column:1-128*/
void SSD1306::setAddrWindow(unsigned char page,unsigned char column) 
 {
	 column=column-1;
	 page=page-1;
	 writeCommand(0xb0+page);
	 writeCommand(((column>>4)&0x0f)+0x10); 
	 writeCommand(column&0x0f);   
}


void SSD1306::fillScreen(uint8_t color)	
{
	 unsigned char i,j;
	 for(i=0;i<8;i++)
	 {
	   setAddrWindow(1+i,1);
	   for(j=0;j<128;j++)
	   {
        writeData(color); 
	   } 
	 }
}


void SSD1306::ShowChar(uint8_t page,uint8_t column,const uint8_t *data,Show_Mode show_mode)
{
  uint8_t i=0,j,k,n;
  while(data[i]>0x00)
  {
     if((data[i]>=0x20)&&(data[i]<=0x7e))
     {
        j=data[i]-0x20;
        for(n=0;n<2;n++)
        {
           setAddrWindow(page+n,column);
           for(k=0;k<8;k++)
           {
              if(show_mode)
              {
                  writeData(Ascii[j][k+8*n]);
              }	
              else		
                  writeData(~Ascii[j][k+8*n]);	
            }	 
         }
         i++;
         column+=8; 	 
     }	
     else
         i++;
  }
}

/*ÖÐÎÄÊä³ö*/
//void SSD1306::ShowString(u8 x,u8 y,const u8 *p,u8 size)
//{
//}


void SSD1306::ShowBMP(uint8_t page,uint8_t column,const uint8_t *data)	
{
	 uint8_t i,j;
	 for(i=0;i<8;i++)
	  {
	    setAddrWindow(page+i,column);
		for(j=0;j<128;j++)
		  {
		   writeData(*data++);
		  } 
	  }
}



/*HDSPI*/
SSD1306 SCREEN(PC3,PC7,PC4);
/*SOFTSPI*/
//SSD1306 SCREEN(PC3,PC7,PC4,PC5,PC6);

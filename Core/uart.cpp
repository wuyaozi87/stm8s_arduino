#include "uart.h"
#include "stdarg.h" //printf可变参数头文件
//#include "stdio.h"

//波特率最大可以设置为38400
void HardwareSerial::begin(unsigned int baudrate)
{
   
    unsigned int baud_div=0;
    
    UART1->CR1 = (0<<4)|(0<<3)|(0<<2)|(0<<1)|(0<<0); 
    //1位起始位 8位数据位 被空闲总线唤醒 不使用奇偶校验 不使能奇偶校验中断
    UART1->CR3 = (0<<6)|(0<<4)|(0<<3); //设置1位停止位 不使能SCLK 
    
    UART1->CR2 = (0<<7)|(0<<6)|(1<<5)|(0<<4)|(1<<3)|(1<<2); 
    //使能发送和接收 接收中断发送中断禁止,如果需要使用中断可以开，本例没有使用中断
           
    UART1->CR5 = (0<<2)|(0<<1);     
    //使用智能卡模式需要设置的，可以不修改
    
    //设置波特率
    baud_div =16000000/baudrate;  //分频因子
    UART1->BRR2 = baud_div & 0x0f;
    UART1->BRR2 |= ((baud_div & 0xf000) >> 8);
    UART1->BRR1 = ((baud_div & 0x0ff0) >> 4);    //先给BRR2赋值 最后再设置BRR1
    
    UART1->CR1 |= (0<<5);         /*使能UART*/
}

//阻塞式发送函数
void HardwareSerial::SendChar( unsigned char dat )
{
    while( ( UART1->SR & 0x80 ) == 0x00 );       //发送数据寄存器空
    UART1->DR = dat;
}

//发送字符串
void HardwareSerial::SendString( unsigned char* s )
{
    while( 0 != *s )
    {
        SendChar( *s );
        s++;
    }
}


/*
  功能：将int型数据转为2，8，10，16进制字符串
  参数：value --- 输入的int整型数
        str --- 存储转换的字符串
        radix --- 进制类型选择
  注意：8位单片机int字节只占2个字节
*/
char*  HardwareSerial:: int2char( int value, char *str, unsigned int radix )
{
    char list[] = "0123456789ABCDEF";
    unsigned int tmp_value;
    int i = 0, j, k = 0;
    if ( NULL == str )
    {
        return NULL;
    }
    if ( 2 != radix && 8 != radix && 10 != radix && 16 != radix )
    {
        return NULL;
    }
    if ( radix == 10 && value < 0 )
    {
        //十进制且为负数
        tmp_value = ( unsigned int )( 0 - value );
        str[i++] = '-';
        k = 1;
    }
    else
    {
        tmp_value = ( unsigned int )value;
    }
    //数据转换为字符串，逆序存储
    do
    {
        str[i ++] = list[tmp_value % radix];
        tmp_value /= radix;
    }
    while( tmp_value );
    str[i] = '\0';
    //将逆序字符串转换为正序
    char tmp;
    for ( j = k; j < ( i + k ) / 2; j++ )
    {
        tmp = str[j];
        str[j] = str[i - j - 1 + k];
        str[i - j - 1 + k] = tmp;
    }
    return str;
}

/*
  功能：将double型数据转为字符串
  参数：value --- 输入的double浮点数
        str --- 存储转换的字符串
        eps --- 保留小数位选择，至少保留一个小数位,至多保留4个小数位
  注意：8位单片机int字节只占2个字节
*/
void  HardwareSerial::flaot2char( double value, char *str, unsigned int eps )
{
    unsigned int integer;
    double decimal;
    char list[] = "0123456789";
    int i = 0, j, k = 0;
    //将整数及小数部分提取出来
    if ( value < 0 )
    {
        decimal = ( double )( ( ( int )value ) - value );
        integer = ( unsigned int )( 0 - value );
        str[i ++] = '-';
        k = 1;
    }
    else
    {
        integer = ( unsigned int )( value );
        decimal = ( double )( value - integer );
    }
    //整数部分数据转换为字符串，逆序存储
    do
    {
        str[i ++] = list[integer % 10];
        integer /= 10;
    }
    while( integer );
    str[i] = '\0';
    //将逆序字符串转换为正序
    char tmp;
    for ( j = k; j < ( i + k ) / 2; j++ )
    {
        tmp = str[j];
        str[j] = str[i - j - 1 + k];
        str[i - j - 1 + k] = tmp;
    }
    //处理小数部分
    if ( eps < 1 || eps > 4 )
    {
        eps = 4;
    }

    //精度问题，防止输入1.2输出1.19等情况
    double pp = 0.1;
    for ( j = 0; j <= eps; j++ )
    {
        pp *= 0.1;
    }
    decimal += pp;
    while ( eps )
    {
        decimal *= 10;
        eps --;
    }
    int tmp_decimal = ( int )decimal;
    str[i ++] = '.';
    k = i;
    //整数部分数据转换为字符串，逆序存储
    do
    {
        str[i ++] = list[tmp_decimal % 10];
        tmp_decimal /= 10;
    }
    while( tmp_decimal );
    str[i] = '\0';
    //将逆序字符串转换为正序
    for ( j = k; j < ( i + k ) / 2; j++ )
    {
        tmp = str[j];
        str[j] = str[i - j - 1 + k];
        str[i - j - 1 + k] = tmp;
    }
    str[i] = '\0';
}

void  HardwareSerial::printf( char * Data, ... )
{
    const char *s;
    int d;
    char buf[16];
    unsigned char txdata;
    va_list ap;
    va_start( ap, Data );
    while ( * Data != 0 )
    {
        if ( * Data == 0x5c )
        {
            switch ( *++Data )
            {
            case 'r':
                txdata = 0x0d;
                SendChar( txdata );
                Data ++;
                break;
            case 'n':
                txdata = 0x0a;
                SendChar( txdata );
                Data ++;
                break;
            default:
                Data ++;
                break;
            }
        }
        else if ( * Data == '%' )
        {
            switch ( *++Data )
            {
/*              
            case 's':
                s = va_arg( ap, const char * );
                for ( ; *s; s++ )
                {
                    SendChar( *( ( unsigned char * )s ) );
                }
                Data++;
                break;
*/
            case 'd':
                d = va_arg( ap, int );
                int2char( d, buf, 10 );
                for ( s = buf; *s; s++ )
                {
                    SendChar( *( ( unsigned char * )s ) );
                }
                Data++;
                break;
/*                
            case 'x':
            {
                d = va_arg( ap, int );
                int2char( d, buf, 16 );
                for ( s = buf; *s; s++ )
                {
                    SendChar( *( ( unsigned char * )s ) );
                }
                Data++;
                break;
            }
            
            case 'f':
            {
				double num = va_arg(ap, double);
				flaot2char(num, buf, 4);
				for (s = buf; *s; s++)
				{
					SendChar(*((unsigned char *)s));
				}
				Data++;
                break;
            }
*/
            default:
                Data++;
                break;
            }
        }
        else
        {
            SendChar( *( ( unsigned char * )Data ) );
            Data++;
        }
    }
}



////接收中断函数 中断号18
//#pragma vector = 20                             // IAR中的中断号，要在STVD中的中断号上加2
//__interrupt void UART1_Handle( void )
//{
//    unsigned char res = 0;
//  
//    UART1->SR &= ~( 1 << 5 );                    //RXNE 清零
//    res = UART1->DR;
//}

	
HardwareSerial Serial1;

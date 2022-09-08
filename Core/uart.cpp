#include "uart.h"
#include "stdarg.h" //printf�ɱ����ͷ�ļ�
//#include "stdio.h"

//����������������Ϊ38400
void HardwareSerial::begin(unsigned int baudrate)
{
   
    unsigned int baud_div=0;
    
    UART1->CR1 = (0<<4)|(0<<3)|(0<<2)|(0<<1)|(0<<0); 
    //1λ��ʼλ 8λ����λ ���������߻��� ��ʹ����żУ�� ��ʹ����żУ���ж�
    UART1->CR3 = (0<<6)|(0<<4)|(0<<3); //����1λֹͣλ ��ʹ��SCLK 
    
    UART1->CR2 = (0<<7)|(0<<6)|(1<<5)|(0<<4)|(1<<3)|(1<<2); 
    //ʹ�ܷ��ͺͽ��� �����жϷ����жϽ�ֹ,�����Ҫʹ���жϿ��Կ�������û��ʹ���ж�
           
    UART1->CR5 = (0<<2)|(0<<1);     
    //ʹ�����ܿ�ģʽ��Ҫ���õģ����Բ��޸�
    
    //���ò�����
    baud_div =16000000/baudrate;  //��Ƶ����
    UART1->BRR2 = baud_div & 0x0f;
    UART1->BRR2 |= ((baud_div & 0xf000) >> 8);
    UART1->BRR1 = ((baud_div & 0x0ff0) >> 4);    //�ȸ�BRR2��ֵ ���������BRR1
    
    UART1->CR1 |= (0<<5);         /*ʹ��UART*/
}

//����ʽ���ͺ���
void HardwareSerial::SendChar( unsigned char dat )
{
    while( ( UART1->SR & 0x80 ) == 0x00 );       //�������ݼĴ�����
    UART1->DR = dat;
}

//�����ַ���
void HardwareSerial::SendString( unsigned char* s )
{
    while( 0 != *s )
    {
        SendChar( *s );
        s++;
    }
}


/*
  ���ܣ���int������תΪ2��8��10��16�����ַ���
  ������value --- �����int������
        str --- �洢ת�����ַ���
        radix --- ��������ѡ��
  ע�⣺8λ��Ƭ��int�ֽ�ֻռ2���ֽ�
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
        //ʮ������Ϊ����
        tmp_value = ( unsigned int )( 0 - value );
        str[i++] = '-';
        k = 1;
    }
    else
    {
        tmp_value = ( unsigned int )value;
    }
    //����ת��Ϊ�ַ���������洢
    do
    {
        str[i ++] = list[tmp_value % radix];
        tmp_value /= radix;
    }
    while( tmp_value );
    str[i] = '\0';
    //�������ַ���ת��Ϊ����
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
  ���ܣ���double������תΪ�ַ���
  ������value --- �����double������
        str --- �洢ת�����ַ���
        eps --- ����С��λѡ�����ٱ���һ��С��λ,���ౣ��4��С��λ
  ע�⣺8λ��Ƭ��int�ֽ�ֻռ2���ֽ�
*/
void  HardwareSerial::flaot2char( double value, char *str, unsigned int eps )
{
    unsigned int integer;
    double decimal;
    char list[] = "0123456789";
    int i = 0, j, k = 0;
    //��������С��������ȡ����
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
    //������������ת��Ϊ�ַ���������洢
    do
    {
        str[i ++] = list[integer % 10];
        integer /= 10;
    }
    while( integer );
    str[i] = '\0';
    //�������ַ���ת��Ϊ����
    char tmp;
    for ( j = k; j < ( i + k ) / 2; j++ )
    {
        tmp = str[j];
        str[j] = str[i - j - 1 + k];
        str[i - j - 1 + k] = tmp;
    }
    //����С������
    if ( eps < 1 || eps > 4 )
    {
        eps = 4;
    }

    //�������⣬��ֹ����1.2���1.19�����
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
    //������������ת��Ϊ�ַ���������洢
    do
    {
        str[i ++] = list[tmp_decimal % 10];
        tmp_decimal /= 10;
    }
    while( tmp_decimal );
    str[i] = '\0';
    //�������ַ���ת��Ϊ����
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



////�����жϺ��� �жϺ�18
//#pragma vector = 20                             // IAR�е��жϺţ�Ҫ��STVD�е��жϺ��ϼ�2
//__interrupt void UART1_Handle( void )
//{
//    unsigned char res = 0;
//  
//    UART1->SR &= ~( 1 << 5 );                    //RXNE ����
//    res = UART1->DR;
//}

	
HardwareSerial Serial1;

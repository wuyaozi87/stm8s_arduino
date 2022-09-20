#include "IR.h"

static uint32_t VS838_Receive_Data=0;        //32位的红外接收数据
static uint8_t  VS838_receive_ok=0;          //红外接收完成标志

void VS838_Receive_Handle()//红外接收中断处理函数
{ 
  
  static uint8_t  VS838_Receive_Count=0;  //红外接收数据位计数
  static uint8_t  VS838_Status=0; //红外接收处理状态
  uint16_t Interval_tim=0;//两个下降沿间隔时间 
  switch(VS838_Status)
  {
    case 0://第一个下降沿，定时器开始计数                    
            VS838_Status=1;
            TIM1_Cmd(ENABLE);                   //Enable TIM1 
            TIM1_SetCounter(0);                 //定时器计数值清零
            break;
                        
    case 1://第二个下降沿，定时器关闭，读取定时器计数值                                              
            TIM1_Cmd(DISABLE);
            Interval_tim=0;
            Interval_tim=TIM1_GetCounter();     //读取定时器计数值
            TIM1_SetCounter(0);                 //定时器计数值清零
            TIM1_Cmd(ENABLE);                   //Enable TIM1 
            
            if( (Interval_tim>=12500)&&(Interval_tim<=14500) )//判断引导码是否正确9+4.5ms                        
            {
                VS838_Status=2;                    //进入下一状态  
            }
            else                                //引导码错误，从新接收
            {
                VS838_Status=0;
                VS838_Receive_Count=0;
            }                        
            break;
                        
    case 2://开始32位数据的接收
            TIM1_Cmd(DISABLE);
            Interval_tim=0;
            Interval_tim=TIM1_GetCounter();
            TIM1_SetCounter(0);
            TIM1_Cmd(ENABLE); //Enable TIM1 
        
            if( (Interval_tim>=1000)&&(Interval_tim<=1300) )        //间隔1.12ms ->0
            {
                  VS838_Receive_Data=VS838_Receive_Data<<1;
                  VS838_Receive_Count++;                                
            }
            else if( (Interval_tim>=2000)&&(Interval_tim<=2600) )   //间隔2.25ms ->1
            {
                  VS838_Receive_Data=VS838_Receive_Data<<1;
                  VS838_Receive_Data=VS838_Receive_Data|0x0001;
                  VS838_Receive_Count++;
                                  
            }
            else//不是0,1 接收错误，从新接收
            {
                  VS838_Status=0;
                  VS838_Receive_Data=0;
                  VS838_Receive_Count=0;
            }
           
            //超出接收数据位数，接收下一个
          while(VS838_Receive_Count==32)
            {         
                VS838_receive_ok=1;//红外接收完成
                VS838_Status=0;
                VS838_Receive_Count=0;
                break;
            }                       
            break;
                        
    default :
            {
                VS838_Status=0;
            }
            break;
    }
}

uint8_t ir_receive()//红外接收数据处理函
{
  uint32_t cp_VS838_Receive_Data = 0; 
  uint8_t VS838_num = 0;              //最终处理后的键值返回值
  uint8_t Address_H,Address_L;       //地址码,地址反码
  uint8_t Data_H,Data_L;             //数据码,数据反码
  
  if(VS838_receive_ok==1)          //接收完成
  {
       cp_VS838_Receive_Data = VS838_Receive_Data;
       Address_H=cp_VS838_Receive_Data>>24;                //得到地址码
       Address_L=(cp_VS838_Receive_Data>>16)&0xff;         //得到地址反码 
       if((Address_H==(u8)~Address_L))//检验遥控识别码(ID)及地址 
       { 
            Data_H=cp_VS838_Receive_Data>>8;              //得到数据码
            Data_L=cp_VS838_Receive_Data;                 //得到数据反码
            if(Data_H==(u8)~Data_L)                 //接收数据码正确
            {
                  VS838_num=Data_H;    //正确键值                                  
            }
        }    
  }
   return  VS838_num;      //返回键值
}



void ir_begin()
{
  pinMode(_out_pin,INPUT_PULLUP);
  attachInterrupt(_out_pin,VS838_Receive_Handle ,EXTI_SENSITIVITY_FALL_ONLY); 
   
  TIM1_TimeBaseInit(16,TIM1_COUNTERMODE_UP,60000,0); //1us
  TIM1_ARRPreloadConfig(ENABLE);//使能自动重装
  TIM1_Cmd(ENABLE);//开定时器
      
}
  



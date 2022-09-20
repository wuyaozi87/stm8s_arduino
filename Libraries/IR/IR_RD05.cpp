#include "IR.h"

static uint8_t  VS838_Receive_Data[6];        //32位的红外接收数据
static uint8_t  VS838_receive_ok=0;          //红外接收完成标志

static uint8_t  VS838_Receive_Count=0;  //红外接收数据位计数
static uint8_t  VS838_Status=0; //红外接收处理状态


void VS838_Receive_Handle()//红外接收中断处理函数
{ 
  
  static uint8_t data = 0;
  static uint8_t i = 0;
  
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
            
            if( (Interval_tim>=8000)&&(Interval_tim<=9500) )//判断引导码是否正确4.4+4.4ms                        
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
        
            if( (Interval_tim>=900)&&(Interval_tim<=1300) )        //间隔1.08ms ->0
            {
                  data=data<<1;
                  VS838_Receive_Count++;                                
            }
            else if( (Interval_tim>=2000)&&(Interval_tim<=2600) )   //间隔2.16ms ->1
            {
                  data=data<<1;
                  data=data|0x0001;
                  VS838_Receive_Count++;
                                  
            }
            else//不是0,1 接收错误，从新接收
            {
                  VS838_Status=0;
                  data=0;
                  VS838_Receive_Count=0;
            }
            
            //超出接收数据位数，接收下一个
            while(VS838_Receive_Count == 8)
            {         
                VS838_Receive_Data[i] = data;//红外接收完成
                data = 0;
                VS838_Receive_Count=0;
                i++;
                break;
            }
           while(i >= 5) 
           {
              VS838_receive_ok=1;//红外接收完成
              VS838_Status=0;
              i = 0 ;
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




void ir_receives(uint8_t* datacode)
{
  
  if(VS838_receive_ok==1)
  {
  
    datacode = VS838_Receive_Data;
  
  }
  
  
}






void ir_begin()
{
  pinMode(_out_pin,INPUT_PULLUP);
  attachInterrupt(_out_pin,VS838_Receive_Handle ,EXTI_SENSITIVITY_FALL_ONLY); 
   
  TIM1_TimeBaseInit(16,TIM1_COUNTERMODE_UP,60000,0); //1us
  TIM1_ARRPreloadConfig(ENABLE);//使能自动重装
  TIM1_Cmd(ENABLE);//开定时器
      
}
  



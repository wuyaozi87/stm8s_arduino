#include "IR.h"

static uint8_t  VS838_Receive_Data[6];        //32λ�ĺ����������
static uint8_t  VS838_receive_ok=0;          //���������ɱ�־

static uint8_t  VS838_Receive_Count=0;  //�����������λ����
static uint8_t  VS838_Status=0; //������մ���״̬


void VS838_Receive_Handle()//��������жϴ�����
{ 
  
  static uint8_t data = 0;
  static uint8_t i = 0;
  
  uint16_t Interval_tim=0;//�����½��ؼ��ʱ��
  
  switch(VS838_Status)
  {
    case 0://��һ���½��أ���ʱ����ʼ����                    
            VS838_Status=1;
            TIM1_Cmd(ENABLE);                   //Enable TIM1 
            TIM1_SetCounter(0);                 //��ʱ������ֵ����
            break;
                        
    case 1://�ڶ����½��أ���ʱ���رգ���ȡ��ʱ������ֵ                                              
            TIM1_Cmd(DISABLE);
            Interval_tim=0;
            Interval_tim=TIM1_GetCounter();     //��ȡ��ʱ������ֵ
            TIM1_SetCounter(0);                 //��ʱ������ֵ����
            TIM1_Cmd(ENABLE);                   //Enable TIM1 
            
            if( (Interval_tim>=8000)&&(Interval_tim<=9500) )//�ж��������Ƿ���ȷ4.4+4.4ms                        
            {
                VS838_Status=2;                    //������һ״̬  
            }
            else                                //��������󣬴��½���
            {
                VS838_Status=0;
                VS838_Receive_Count=0;
            }                        
            break;
                        
    case 2://��ʼ32λ���ݵĽ���
            TIM1_Cmd(DISABLE);
            Interval_tim=0;
            Interval_tim=TIM1_GetCounter();
            TIM1_SetCounter(0);
            TIM1_Cmd(ENABLE); //Enable TIM1 
        
            if( (Interval_tim>=900)&&(Interval_tim<=1300) )        //���1.08ms ->0
            {
                  data=data<<1;
                  VS838_Receive_Count++;                                
            }
            else if( (Interval_tim>=2000)&&(Interval_tim<=2600) )   //���2.16ms ->1
            {
                  data=data<<1;
                  data=data|0x0001;
                  VS838_Receive_Count++;
                                  
            }
            else//����0,1 ���մ��󣬴��½���
            {
                  VS838_Status=0;
                  data=0;
                  VS838_Receive_Count=0;
            }
            
            //������������λ����������һ��
            while(VS838_Receive_Count == 8)
            {         
                VS838_Receive_Data[i] = data;//����������
                data = 0;
                VS838_Receive_Count=0;
                i++;
                break;
            }
           while(i >= 5) 
           {
              VS838_receive_ok=1;//����������
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
  TIM1_ARRPreloadConfig(ENABLE);//ʹ���Զ���װ
  TIM1_Cmd(ENABLE);//����ʱ��
      
}
  



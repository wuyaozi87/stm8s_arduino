#include "menu.h"



/* �˵����涨�� */
static menu MainMenu = { //�������˵�
 0,3,5,1,//Ĭ����ʾ0-3��ܹ�4���ǰѡ���0��
  {
  "AAAAAAAA",
  "BBBBBBBB",
  "CCCCCCCC",
  "DDDDDDDD",
  "PPPPPPPP"
  }
};

static menu searchMenu = {//�����˵�
 0,3,5,1,
 {
  "EEEEEEEE",
  "FFFFFFFF",
  "GGGGGGGG",
  "HHHHHHHH",
  "IIIIIIII"
 }
};






/* ����˵�ģ��1 */
void func1()
{
	tmt.run_ctrl(select_scan,task_stop);
    SCREEN.fillScreen(SCREEN.BLACK);
 
	while(key_status != KEY_CANCEL)
    {
        
      SCREEN.ShowChar(1,20,"HELLO");
       /**
            YOU CODE ....
    
        **/
      
        /* ������Ӧ */
        switch(key_status)
        {     
          case KEY_UP:
            break;
          case KEY_DOWN:
            break;
          case KEY_ENTER:
            break;
                    
          default:
            break;
        }

    }    
	
    SCREEN.fillScreen(SCREEN.BLACK);
    tmt.run_ctrl(select_scan,task_continue);
           
    display(0);
  
  
    
}


/* ����˵�ģ��2 */
void func2()
{
	tmt.run_ctrl(select_scan,task_stop);
    SCREEN.fillScreen(SCREEN.BLACK);
 
	while(key_status != KEY_CANCEL)
    {       
        SCREEN.ShowChar(1,20,"world");
         /**
              
              YOU CODE ....
      
         **/
        
        /* ������Ӧ */
        switch(key_status)
        {     
          case KEY_UP:
            break;
          case KEY_DOWN:
            break;
          case KEY_ENTER:
            break;
                    
          default:
            break;
        } 
    }    
	
   SCREEN.fillScreen(SCREEN.BLACK);
   tmt.run_ctrl(select_scan,task_continue);	
   

    
    display(0);
  
   
}






/**
*��    �ƣ�initMenu(void)
*��    �ܣ���ʼ���˵�
*��ڲ�������                      
**/
void initMenu()
{

 MainMenu.subMenus[0] = 0;//��1��3��û���Ӳ˵���null,ѡ����������func����Ӧ���еĺ���
 MainMenu.subMenus[1] = &searchMenu;//�������ѯ���Ӳ˵�
 MainMenu.subMenus[2] = 0;
 MainMenu.subMenus[3] = 0;
 MainMenu.subMenus[4] = 0;

 MainMenu.func[0] = &func1;//��ѡ���˲�����ȷ������ִ��func����;
 MainMenu.func[1] = 0;
 MainMenu.func[2] = 0;
 MainMenu.func[3] = 0;
 MainMenu.func[4] = 0;
 MainMenu.parent = 0;//��ʾ�Ƕ����˵�
 

 searchMenu.subMenus[0] = 0;
 searchMenu.subMenus[1] = 0;
 searchMenu.subMenus[2] = 0;
 searchMenu.subMenus[3] = 0;
 searchMenu.subMenus[4] = 0;

 searchMenu.func[0] = &func2;
 searchMenu.func[1] = 0;
 searchMenu.func[2] = 0;
 searchMenu.func[3] = 0;
 searchMenu.func[4] = 0;
           
 searchMenu.parent = &MainMenu;//��һ���˵���MainMenu.�����ѯ�Ӳ˵��󰴷��ؼ���������ʾ����˵� ��
 
 currentMenu = &MainMenu; 
}
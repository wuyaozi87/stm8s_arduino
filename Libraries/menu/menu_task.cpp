#include "menu.h"



/* 菜单界面定义 */
static menu MainMenu = { //定义主菜单
 0,3,5,1,//默认显示0-3项，总共4项，当前选择第0项
  {
  "AAAAAAAA",
  "BBBBBBBB",
  "CCCCCCCC",
  "DDDDDDDD",
  "PPPPPPPP"
  }
};

static menu searchMenu = {//二级菜单
 0,3,5,1,
 {
  "EEEEEEEE",
  "FFFFFFFF",
  "GGGGGGGG",
  "HHHHHHHH",
  "IIIIIIII"
 }
};






/* 任务菜单模版1 */
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
      
        /* 按键响应 */
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


/* 任务菜单模版2 */
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
        
        /* 按键响应 */
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
*名    称：initMenu(void)
*功    能：初始化菜单
*入口参数：无                      
**/
void initMenu()
{

 MainMenu.subMenus[0] = 0;//第1到3项没有子菜单置null,选择后程序会调用func中相应项中的函数
 MainMenu.subMenus[1] = &searchMenu;//第四项查询有子菜单
 MainMenu.subMenus[2] = 0;
 MainMenu.subMenus[3] = 0;
 MainMenu.subMenus[4] = 0;

 MainMenu.func[0] = &func1;//当选择了并按了确定，会执行func函数;
 MainMenu.func[1] = 0;
 MainMenu.func[2] = 0;
 MainMenu.func[3] = 0;
 MainMenu.func[4] = 0;
 MainMenu.parent = 0;//表示是顶级菜单
 

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
           
 searchMenu.parent = &MainMenu;//上一级菜单是MainMenu.进入查询子菜单后按返回键，将会显示这个菜单 项
 
 currentMenu = &MainMenu; 
}
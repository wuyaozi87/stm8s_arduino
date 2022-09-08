#include "menu.h"


/* 定义当前菜单指针 */
menu *currentMenu;//当前的菜单


/* 定义全局按键变量 */
KEY_Status key_status = KEY_IDEL;


/**
*名    称：display(u8 line)
*功    能：显示菜单项并设置选中的项反白
*入口参数：无                      
**/
void display(uint8_t line)
{  
   
   line = 3-(currentMenu->range_to - line);
   for(uint8_t i = 0;i<4;i++)
   {	 
    SCREEN.ShowChar(i*2+1,32,currentMenu->menuItems[i+currentMenu->range_from],i == line ? Reverse:DisReverse);
    SCREEN.ShowChar(i*2+1,20,"[");
    SCREEN.ShowChar(i*2+1,100,"]");
   }
    key_status = KEY_IDEL;
}

/**
*名    称：void select_scan(uchar sel)
*功    能：扫描按键显示相应菜单
*入口参数：无                      
**/
void select_scan()		 
{ 
  switch(key_status)
  {
   case KEY_UP://向上
      if(currentMenu->selected == 0)//到了第一项
          break;
      else
      {
         currentMenu->selected--;
         if(currentMenu->selected < currentMenu->range_from)//更新显示的区域
           {
              currentMenu->range_from = currentMenu->selected;
              currentMenu->range_to = currentMenu->range_from+3;
           }
         display(currentMenu->selected);
      }
      break;
   case KEY_DOWN://向下
      if(currentMenu->selected == currentMenu->itemCount-1)
          break;
      else
      {
       currentMenu->selected++;
       if(currentMenu->selected>currentMenu->range_to)
         {
            currentMenu->range_to = currentMenu->selected;
            currentMenu->range_from = currentMenu->range_to-3;
         }
       display(currentMenu->selected);      
      }
      break;
   case KEY_ENTER://Enter键
   {
      if(currentMenu->subMenus[currentMenu->selected] !=0)
      {
       currentMenu = currentMenu->subMenus[currentMenu->selected];
       display(0);
      }
      else
      {
       if(currentMenu->func[currentMenu->selected] != 0)
       {
          currentMenu->func[currentMenu->selected]();//执行相应的函数
          //display(currentMenu->selected);//返回后恢复原来的菜单状态
       }
      }
      break;
   }
   case KEY_CANCEL://返回键
   {
      if(currentMenu->parent!=0) //父菜单不为空，将显示父菜单
      {
         currentMenu = currentMenu->parent;
         display(currentMenu->selected);
      }
      
      break;
   }
   default:
       break;
  }
 
}		


/**
*名    称：disp_menu(void)
*功    能：初始化菜单，并显示选择主菜单第一项
*入口参数：无                      
**/
void disp_menu()
{
 initMenu();
 display(currentMenu->selected); 
}

#ifndef __MENU_H
#define __MENU_H

#include "Arduino.h"


typedef enum
{
 KEY_IDEL   =0X00,
 KEY_UP     =0x01,
 KEY_DOWN   =0x02,
 KEY_ENTER  =0x03,
 KEY_CANCEL =0x04
}KEY_Status;





typedef struct menu//定义一个菜单
{
 uint8_t range_from,range_to; //当前显示的项开始及结束序号
 uint8_t itemCount;//项目总数
 uint8_t selected;//当前选择项
 const uint8_t *menuItems[5];//菜单项目
 struct menu* subMenus[5];//子菜单
 struct menu* parent;//上级菜单 ,如果是顶级则为null
 void (*func[5])();//选择相应项按确定键后执行的函数
}Menu;


void initMenu();
void display(u8 line);
void select_scan();
void disp_menu(void);


/* 定义全局按键变量 */
extern KEY_Status key_status;
extern menu *currentMenu;//当前的菜单


#endif
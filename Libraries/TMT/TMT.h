#ifndef __TMT_H_
#define __TMT_H_

#include "arduino.h"



/**
 * @brief     任务数量控制宏，用来确定TMT需要调度的最大任务数量。
 * @details   The number of tasks control macro is used to 
 *            determine the maximum number of tasks that TMT
 *            needs to schedule.
**/
#define 	  TMT_TASK_NUM  	 (4)
#define       TASKS_MAX       TMT_TASK_NUM


#define       ENTER_TMT_CRI_AREA()    do{ TIM4_Cmd(DISABLE); }while(0) 
#define       EXTI_TMT_CRI_AREA()     do{ TIM4_Cmd(ENABLE); }while(0) 
   
typedef enum
{
    task_stop = 1,   /*!< 停止运行状态。*/
    task_continue = !task_stop /*!< 继续运行状态。*/
}task_type;

typedef enum
{
    tmt_nok= 1,     /* Function self checking failed */
    tmt_ok = !tmt_nok /* Function self checking successfed */ 
}tmt_fun_t;    
   
   
class TMT
{
public:
  

  TMT(){num = 0;}
  
  void tick();
  void run();
  tmt_fun_t create(void (*entry)(void),uint16_t set_time);
  tmt_fun_t deletel(void (*entry)(void));
  tmt_fun_t time_ctrl(void (*entry) (void), uint16_t set_time);
  tmt_fun_t run_ctrl(void (*entry) (void), task_type state);
  
 
private:
      
     struct
    {
        void (* entry) (void); /*!< 任务函数入口指针。*/
        uint16_t tim_cnt;     /*!< 任务调度时间计数器。*/
        uint16_t set_time;      /*!< 任务设置的调度时间。*/
        uint8_t state;         /*!< 任务运行状态。*/
    }comp[TASKS_MAX];

    uint8_t num;   /*!< 已经创建的任务数量。*/

};
    
extern TMT tmt;


#endif
/*-----------------------------------------------------------------------
|          END OF FLIE        (C) COPYRIGHT zeweni                      | 
-----------------------------------------------------------------------*/


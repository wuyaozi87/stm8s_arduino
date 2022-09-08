#include "tmt.h"
#include "stm8s_tim4.h" 


/**
 * @brief     TMT更新任务调度tick时间。
 * @details   TMT update task schedule tick time.
 * @param[in] None.
 * @return    None.
**/
void TMT::tick()
{
	uint8_t i;
	for(i = 0; i< num; i++)
    {
		 /* If time arrives */
        if(comp[i].tim_cnt > 0 )
        {
           comp[i].tim_cnt--;
        }
	}	
}

/**
 * @brief     TMT运行函数，是任务调度器。
 * @details   TMT runs the function, which is the task scheduler.
 * @param[in] None.
 * @return    None.
**/
void  TMT::run()
{
	
    uint8_t index;
	for(index = 0; index < num; index++)
	{
		 /* If time arrives */
		if(comp[index].tim_cnt == 0 && comp[index].state != task_stop)
		{
			comp[index].tim_cnt = comp[index].set_time;
			
			/* 
				To prevent process conflict, 
				only one process can be executed in the same time period.
			*/
			if(comp[index].entry != 0 )
			{
				comp[index].entry();  /* Run task */
			}
		}
	}
}


/**
 * @brief     TMT创建一个任务函数。
 * @details   TMT creates a task function.
 * @param[in] entry 任务函数入口指针.
 *            A pointer function without formal parameters.
 * @param[in] set_time 任务调度的时间 task run time (ticks)
 * @return    [tmt_ok]创建成功.Create successfully.
 * @return    [tmt_nok]创建失败.	Create failed.
**/	
tmt_fun_t TMT::create(void (*entry)(void),uint16_t set_time)
{	
	
   if(num < TASKS_MAX)
	{
		comp[num].entry = entry;
		comp[num].set_time = set_time;
		comp[num].tim_cnt = set_time;
		comp[num].state = task_continue;
		num++;
		return tmt_ok;
	}
	else
	{
		return tmt_nok;	
	}		
}


/**
 * @brief     TMT删除一个任务函数。
 * @details   TMT creates a task function.
 * @param[in] entry 任务函数入口指针.
 *            A pointer function without formal parameters.
 * @return    [tmt_ok]删除成功.Delete successfully.
 * @return    [tmt_nok]删除失败.	Delete failed.
**/	
tmt_fun_t  TMT::deletel(void (*entry) (void))
{	
    uint8_t index;
    if(num > 0)
    {
        ENTER_TMT_CRI_AREA();
		
        for(index = 0; index < num; index++)
        {
            if(comp[index].entry == entry)
            {
                    num--;
                    comp[index].entry = comp[num].entry;
                    comp[index].set_time = comp[num].set_time;
                    comp[index].tim_cnt = comp[num].tim_cnt;
                    comp[index].state = comp[num].state;
                    EXTI_TMT_CRI_AREA();
                    return tmt_ok;
            }
        }
    }
    EXTI_TMT_CRI_AREA();
    return tmt_nok;
}


/**
 * @brief     TMT控制一个任务运行状态函数。
 * @details   TMT controls a task running state function.
 * @param[in] entry 任务函数入口指针.
 *            A pointer function without formal parameters.
 * @param[in] state 任务运行状态.Task running status
 * @return    [tmt_ok]修改成功.The modification was successful.
 * @return    [tmt_nok]修改失败.The modification was failed.
**/	
tmt_fun_t  TMT::run_ctrl(void (*entry)(void),task_type state)
{
	uint8_t index;
	for(index = 0; index<num; index++)
	{
		if(comp[index].entry == entry)
		{
		    comp[index].state = state;
			return tmt_ok;
		}
	}
	return tmt_nok;
}


/**
 * @brief     TMT控制一个任务的调度时间函数。
 * @details   The TMT controls the scheduling time function of a task.
 * @param[in] *taskFunc (void) 任务函数入口指针.
 *            A pointer function without formal parameters.
 * @param[in] set_time 任务调度的时间 task run time (ticks)
 * @return    [tmt_ok]修改成功.The modification was successful.
 * @return    [tmt_nok]修改失败.The modification was failed.
**/	
tmt_fun_t TMT::time_ctrl(void (*entry) (void),uint16_t set_time)
{	
	uint8_t index;
	for(index = 0; index< num; index++)
	{
		if(comp[index].entry == entry)
		{
			comp[index].tim_cnt = set_time;
			comp[index].set_time = set_time;
			return tmt_ok;
		}
	}
	return tmt_nok;
}


/* 实例化对象 */
TMT tmt;

/*-----------------------------------------------------------------------
|                   END OF FLIE.  (C) COPYRIGHT zeweni                  |
-----------------------------------------------------------------------*/



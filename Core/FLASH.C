#include "FLASH.H"

void FLASH_Save(u8 ECdata)
{
     /* 定义 FLASH 操作时间*/
    FLASH_SetProgrammingTime(FLASH_PROGRAMTIME_STANDARD);
    /* 解锁数据存储器*/
    FLASH_Unlock(FLASH_MEMTYPE_DATA);
    
    FLASH_ProgramByte(0x4001,ECdata);    

}


u8 FLASH_Read(void)
{
  
     u8 temp;
     /* 定义 FLASH 操作时间*/
    FLASH_SetProgrammingTime(FLASH_PROGRAMTIME_STANDARD);
    /* 解锁数据存储器*/
    FLASH_Unlock(FLASH_MEMTYPE_DATA);
    
    temp = FLASH_ReadByte(0x4001);
    return temp;

}


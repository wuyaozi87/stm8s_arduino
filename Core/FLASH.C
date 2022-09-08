#include "FLASH.H"

void FLASH_Save(u8 ECdata)
{
     /* ���� FLASH ����ʱ��*/
    FLASH_SetProgrammingTime(FLASH_PROGRAMTIME_STANDARD);
    /* �������ݴ洢��*/
    FLASH_Unlock(FLASH_MEMTYPE_DATA);
    
    FLASH_ProgramByte(0x4001,ECdata);    

}


u8 FLASH_Read(void)
{
  
     u8 temp;
     /* ���� FLASH ����ʱ��*/
    FLASH_SetProgrammingTime(FLASH_PROGRAMTIME_STANDARD);
    /* �������ݴ洢��*/
    FLASH_Unlock(FLASH_MEMTYPE_DATA);
    
    temp = FLASH_ReadByte(0x4001);
    return temp;

}

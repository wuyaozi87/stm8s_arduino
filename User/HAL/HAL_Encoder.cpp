#include "HAL_Encoder.h"


static ButtonEvent EncoderPush(2000);


static bool EncoderEnable = true;
static bool EncoderDiffDisable = false;


static void Encoder_EventHandler()
{   
     if(!EncoderEnable || EncoderDiffDisable)
    {
        return;
    } 
    
    key_status = (digitalRead(CONFIG_ENCODER_B_PIN) == LOW ? KEY_DOWN : KEY_UP);  //更换引脚后注意此处要修改
}


static void Encoder_PushHandler(ButtonEvent* btn, int event)
{   
    if(event == ButtonEvent::EVENT_PRESSED)
    {
        EncoderDiffDisable = true;
    }
    else if(event == ButtonEvent::EVENT_RELEASED)
    {
        EncoderDiffDisable = false;
    }

    else if(event == ButtonEvent::EVENT_LONG_PRESSED)
    {
        key_status = KEY_CANCEL;
    }

    else if(event == ButtonEvent::EVENT_DOUBLE_CLICKED)
    {
       key_status = KEY_ENTER;
       
    }
}



void Encoder_init()
{
    pinMode(CONFIG_ENCODER_A_PIN, INPUT_PULLUP);
    pinMode(CONFIG_ENCODER_B_PIN, INPUT_NO_IT);
    pinMode(CONFIG_ENCODER_PUSH_PIN, INPUT_NO_IT);

    attachInterrupt(CONFIG_ENCODER_A_PIN, Encoder_EventHandler);

    EncoderPush.EventAttach(Encoder_PushHandler);
}




void Encoder_Update()
{       
    EncoderPush.EventMonitor(Encoder_GetIsPush());
}



bool Encoder_GetIsPush()
{   
    if(!EncoderEnable)
    {
        return false;
    }
    return (digitalRead(CONFIG_ENCODER_PUSH_PIN) == LOW);
}


void Encoder_SetEnable(bool en)
{
    EncoderEnable = en;
}



#ifndef __HAL_ENCODER_H
#define __HAL_ENCODER_H

#include "Arduino.h"
#include "ButtonEvent.h"

 
#define CONFIG_ENCODER_A_PIN    PA1
#define CONFIG_ENCODER_B_PIN    PD6
#define CONFIG_ENCODER_PUSH_PIN PD5




  
  void Encoder_init();
  void Encoder_Update();
  
  bool Encoder_GetIsPush();
  void Encoder_SetEnable(bool en);
  








#endif
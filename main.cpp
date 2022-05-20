#include "stm32f0xx.h"
#include <cstring>
#include <cstdlib>
#include <math.h>
#include "delay.h"

static   RCC_ClocksTypeDef RCC_Clocks; 

int main(void)
{
  SystemInit(); //инициализация системы(настройка кварца, кварцового генератора, тактирование ядра)
  
  RCC_GetClocksFreq(&RCC_Clocks); // затактировать системный таймер
  
  //тактирование порта PC
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
   
  //тактирование порта PA
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  
  // Инициализация порта 
  GPIO_InitTypeDef LIGHTPINS;
  LIGHTPINS.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9; //указание номера порта
  LIGHTPINS.GPIO_Mode = GPIO_Mode_OUT;
  LIGHTPINS.GPIO_Speed = GPIO_Speed_Level_1; // частота
  LIGHTPINS.GPIO_OType = GPIO_OType_PP; // состояние ножки процессора(PP,OD земля)
  LIGHTPINS.GPIO_PuPd = GPIO_PuPd_NOPULL; //нет подтяжки  
  GPIO_Init(GPIOC, &LIGHTPINS);
  
  
  GPIO_InitTypeDef TOCHPINS;
  TOCHPINS.GPIO_Pin = GPIO_Pin_0;
  TOCHPINS.GPIO_Mode = GPIO_Mode_IN;
  TOCHPINS.GPIO_Speed = GPIO_Speed_Level_1;
  TOCHPINS.GPIO_OType = GPIO_OType_OD;
  TOCHPINS.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &TOCHPINS);
  
  
  
  while(1)
   {
     
     if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 1)
     {
        GPIO_SetBits(GPIOC, GPIO_Pin_8);
        Delay(500); 
        GPIO_ResetBits(GPIOC, GPIO_Pin_8);
        Delay(300);
     }
     
     
     GPIO_SetBits(GPIOC, GPIO_Pin_9);
     Delay(300); 
     GPIO_ResetBits(GPIOC, GPIO_Pin_9);
     Delay(300);
  
  /*
     GPIO_SetBits(GPIOC, GPIO_Pin_9);
     Delay(300); 
     GPIO_ResetBits(GPIOC, GPIO_Pin_9);
     Delay(300);
  */
   }
}
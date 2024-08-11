/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : 主程序代码
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024- aeneas-杨金鹏
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE BEGIN Header */
#include "stm32f10x.h"
#include "sys.h"
#include "Delay.h"
#include "PCA9685.h"
#include "servo.h"
#include "Timer.h"
#include "Motor.h"
#include "Action.h"
#include "JDY31.h"
//right A1
//left A0
int main(void)
{
	PCA9685_Init(50,180);	
	
	Servo_Init();

//    printf("AT+NAME\r\n");      //查询蓝牙名字
//    Delay_ms(100);
	Timer_Init();
	while(1)
	{
		standnormal();
		if(TIM2_IQRHandler()==1)
			break;
	}
	Delay_s(5);
	while(1)
	{
		Roration_place(0);
		//_Meanwhile_Advance_Move();
	}
}



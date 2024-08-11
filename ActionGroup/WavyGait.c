/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : WavyGait.c
  * @brief          : 波浪步态运动函数文件
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
#include "Action.h"
#include "Timer.h"
extern uint8_t body[16];
extern uint8_t Alone_Servo[2];
extern uint8_t standAngle[16];
extern uint8_t stand_high[16];
//////////////////////////////////////////////
int8_t Wavy_Gait_advanceLeft_Uplift[6]=//波浪步态抬起角度枚举
{
	-20,-20,-20,-20,-20,-20
};
int8_t Wavy_Gait_advanceLeft_LayDown[6]=
{
	0,20,0,20,0,20
};
uint8_t Wavy_Gait_advanceALLLeft_MoveModule[6]=//左腿移动零部件枚举
{
	rearLeft_leg,rearLeft_joint,middleLeft_leg,middleLeft_joint,frontLeft_leg,frontLeft_joint
};

int8_t Wavy_Gait_advanceRight_Uplift[6]=
{
	20,20,20,20,20,20
};

int8_t Wavy_Gait_advanceRight_LayDown[6]=
{
	0,-20,0,-20,0,-20
};
uint8_t Wavy_Gait_advanceALLRightMoveModule[6]=
{
	rearRight_leg,rearRight_joint,middleRight_leg,middleRight_joint,frontRight_leg,frontRight_joint
};

void Wavy_Gait_Advance_Move()
{
	return;
}






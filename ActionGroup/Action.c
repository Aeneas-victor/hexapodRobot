/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : Action.c
  * @brief          : 运动的规则函数文件
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
//#include "Motor.h"
uint8_t body[16]={
				//后腿
				rearRight_foot,rearLeft_foot,
				rearRight_leg,rearLeft_leg,
				rearRight_joint,rearLeft_joint,
				//中腿
				middleRight_foot,middleLeft_foot,
				middleRight_leg,middleLeft_leg,
				middleRight_joint,middleLeft_joint,
				//前腿
				frontRight_joint,frontLeft_joint,
				frontRight_foot,frontLeft_foot
};
uint8_t Alone_Servo[2]={110,70};
uint8_t standAngle[16]={//站立姿态枚举
	180,0,150,30, //3
    60,60,175,0, //7
    130,40,70,110,//11
	60,40,175,0//15
};
uint8_t stand_high[16]=//left 110  //right  70
{
	130,45,70,80,
	60,60,140,30,
	60,95,70,50,//11
	70,55,130,35
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int8_t advanceLeftRightLeft_Uplift[6]=//左腿移动抬起角度枚举
{
/////10,100,100,60,30,
///源55,60, 70, 100,60,110
	 -40,50,30,-30,-20,-10
//编号13,8, 10,  3,5,left
};
int8_t advanceLeftRightLeft_LayDown[6]=//左腿移动放下角度枚举
{
	-30,-10, -20,0  ,20,0
////70,60,50,100,80
////
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


uint8_t advanceLeftMoveModule[5]=//左腿移动的零部件枚举
{
	frontLeft_joint,middleRight_leg,middleRight_joint,rearLeft_leg,rearLeft_joint
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int8_t advanceRightLeftRight_Uplift[6]=//右腿移动抬起角度枚举
{
//源60,90,90,70,60,70
	0,30,-40,20,20,20
////12   9  11 2 4,right
};
int8_t advanceRightLeftRight_LayDown[6]=//右腿移动放下角度枚举
{
	-50,20,10,0,-20,0
////40,110,85,70,40
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


uint8_t advanceRightMoveModule[5]=//右腿移动零部件枚举
{
	frontRight_joint,middleLeft_leg,middleLeft_joint,rearRight_leg,rearRight_joint
};

void Stand_High()
{
		ServoLegLeft_SetAngle(110);
		Delay_ms(180);
		ServoLegRight_SetAngle(80);
		Delay_ms(180);	
	
		setAngle(0,130);// 输入pwm通道号、舵机转动角度
		Delay_ms(180);
		setAngle(1,50);// 输入pwm通道号、舵机转动角度
		Delay_ms(180);
		setAngle(2,70);
		Delay_ms(180);		// 输入pwm通道号、舵机转动角度	
		setAngle(3,100);
		Delay_ms(180);
		setAngle(4,60);
		Delay_ms(180);
		setAngle(5,60);
		Delay_ms(180);
		setAngle(6,130);
		Delay_ms(180);
		setAngle(7,50);
		Delay_ms(180);
		setAngle(8,60);
		Delay_ms(180);
		setAngle(9,110);
		Delay_ms(180);
		setAngle(10,70);
		Delay_ms(180);
		setAngle(11,100);
		Delay_ms(180);
		
		setAngle(12,60);
		Delay_ms(180);
		setAngle(13,55);
		Delay_ms(180);
		setAngle(14,130);
		Delay_ms(180);
		setAngle(15,50);
		Delay_ms(180);
}
void trial_funtion(void)
{
		ServoLegLeft_SetAngle(110);
		//Delay_ms(180);
		ServoLegRight_SetAngle(80);
		//Delay_ms(180);	
	
		setAngle(0,130);// 输入pwm通道号、舵机转动角度
		//Delay_ms(180);
		setAngle(1,50);// 输入pwm通道号、舵机转动角度
		//Delay_ms(180);
		setAngle(2,70);
		//Delay_ms(180);		// 输入pwm通道号、舵机转动角度	
		setAngle(3,100);
		//Delay_ms(180);
		setAngle(4,60);
		//Delay_ms(180);
		setAngle(5,60);
		//Delay_ms(180);
		setAngle(6,130);
		//Delay_ms(180);
		setAngle(7,50);
		//Delay_ms(180);
		setAngle(8,60);
		//Delay_ms(180);
		setAngle(9,110);
		//Delay_ms(180);
		setAngle(10,70);
		//Delay_ms(180);
		setAngle(11,65);
		//Delay_ms(180);
		
		setAngle(12,60);
		//Delay_ms(180);
		setAngle(13,55);
		//Delay_ms(180);
		setAngle(14,130);
		//Delay_ms(180);
		setAngle(15,50);
		//Delay_ms(180);
}
void _move_Toleg(front_Leg _leg,float _leg_angle,uint8_t* bodyModule,int8_t* ModuleAngle)
{
	//_leg(_leg_angle);
	//Delay_ms(150);
	for(uint8_t i=0;i<5;i++)
	{
		setAngle(bodyModule[i],stand_high[i]+ModuleAngle[i]);
		//Delay_ms(150);
	}
}
void AdvanceMove(void)
{
	Timer_Init();
	while(1)
	{
		_move_Toleg(ServoLegLeft_SetAngle,70,advanceLeftMoveModule,advanceLeftRightLeft_Uplift);
		if(TIM2_IQRHandler()==1)
		{
			break;
		}
	}
	Timer_Init();
	while(1)
	{
		_move_Toleg(ServoLegLeft_SetAngle,110,advanceLeftMoveModule,advanceLeftRightLeft_LayDown);
		if(TIM2_IQRHandler()==1)
		{
		break;
		}
	}
	Timer_Init();
	while(1)
	{
		_move_Toleg(ServoLegRight_SetAngle,120,advanceRightMoveModule,advanceRightLeftRight_Uplift);
		if(TIM2_IQRHandler()==1)
		{
		break;
		}
	}
	Timer_Init();

	while(1)
	{
		_move_Toleg(ServoLegRight_SetAngle,80,advanceRightMoveModule,advanceRightLeftRight_LayDown);
		if(TIM2_IQRHandler()==1)
		{
			break;
		}
	}

}
void _Meanwhile_Advance_Move(uint8_t* a)
{
	Timer_Init();
	while(1)
	{
		if(*a==0){
			_move_Toleg(ServoLegRight_SetAngle,Alone_Servo[1]+advanceRightLeftRight_LayDown[5],advanceRightMoveModule,advanceRightLeftRight_LayDown);
		}//右腿放下代码
		_move_Toleg(ServoLegLeft_SetAngle,Alone_Servo[0]+advanceLeftRightLeft_Uplift[5],advanceLeftMoveModule,advanceLeftRightLeft_Uplift);//左腿抬起
		if(TIM2_IQRHandler()==1)
		{
			break;
			(*a)++;
		}
	}
	Timer_Init();
	while(1)
	{
		_move_Toleg(ServoLegLeft_SetAngle,advanceLeftRightLeft_LayDown[5]+Alone_Servo[0],advanceLeftMoveModule,advanceLeftRightLeft_LayDown);//左腿放下
		_move_Toleg(ServoLegRight_SetAngle,advanceRightLeftRight_Uplift[5]+Alone_Servo[1],advanceRightMoveModule,advanceRightLeftRight_Uplift);//右腿抬起
		if(TIM2_IQRHandler()==1)
		{
			break;
		}
	}
	
	
}
void _Move_()
{
	
}
void normal(uint8_t* action)
{
	ServoLegLeft_SetAngle(110);
	Delay_ms(180);
	ServoLegRight_SetAngle(70);
	Delay_ms(180);
	for(uint8_t i=0;i<16;i++)
	{
		setAngle(body[i],action[i]);
		Delay_ms(180);
	}
}
void standnormal(void)
{
	normal(stand_high);
}

void side_leg_lift(void)
{
	_move_Toleg(ServoLegLeft_SetAngle,70,advanceLeftMoveModule,advanceLeftRightLeft_Uplift);
}
//void side_leg_lift(void)
//{
//	normal(standAngle_high)
//	{
//		Delay_ms(standAngle);
//		
//	}
//	
//}



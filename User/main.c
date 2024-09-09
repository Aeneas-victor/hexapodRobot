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
#include <string.h>
#include "sys.h"
#include "Delay.h"
#include "PCA9685.h"
#include "servo.h"
#include "Timer.h"
#include "Motor.h"
#include "Action.h"
#include "JDY31.h"
uint8_t Angle_Start[16];


extern void Start_Init(void);
//right A1
//left A0
void test()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOC, GPIO_Pin_13);
}
void LED1_OFF(void)
{
	GPIO_ResetBits(GPIOC,GPIO_Pin_13);
}

void LED1_ON(void)
{
	GPIO_SetBits(GPIOC,GPIO_Pin_13);
}
void test2()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_mytest;
	GPIO_mytest.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_mytest.GPIO_Pin=GPIO_Pin_3;
	GPIO_mytest.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_mytest);
	
}
uint8_t KeyNum = 0;

int main(void)
{
	test();
	test2();
	PCA9685_Init(50,180);
	Servo_Init();
	Serial_Init();
	Start_Init();
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
//		if(Serial_RxFlag==1)
//		{
//			if(strcmp(Serial_RxPacket,"left")==0)
//			{
//				Roration_place(0);
//				LED1_ON();
//				Serial_SendString("正在左转\r\n");
//			}
//			else if(strcmp(Serial_RxPacket,"right")==0)
//			{
//				Roration_place(1);
//				LED1_OFF();
//				Serial_SendString("正在右转\r\n");
//			}
//			else
//			{
//				Serial_SendString("去你妈的\r\n");
//			}
//			Serial_RxFlag = 0;
//		}

//		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3) == 0)
//		{
//			Delay_ms(10);
//			while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3) == 0);
//			Delay_ms(10);
//			KeyNum=KeyNum==0?1:0;
//			if(KeyNum==0)
//			{
//				Roration_place(0);
//				LED1_ON();
//			}
//			else
//			{
//				Roration_place(1);
//				LED1_OFF();
//			}
//		}
//		standnormal();
		AdvanceSingleWalk();
		//_Meanwhile_Advance_Move();
		
	}
}



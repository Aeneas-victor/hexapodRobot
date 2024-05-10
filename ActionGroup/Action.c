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
uint8_t standAngle[16]={//站立姿态枚举
	180,0,150,30, 
    60,60,175,0, 
    130,40,70,110,
	60,40,175,0
};
uint8_t stand_high[16]=//left 110  //right  80
{
	130,50,70,100,
	60,60,130,50,
	60,110,70,110,
	60,40,130,50
};
uint8_t advanceLeftRightLeft_Uplift[5]=//左腿移动抬起角度枚举
{
	10,100,100,60,30
////13,8,10,3,5
};
uint8_t advanceLeftRightLeft_LayDown[5]=//左腿移动放下角度枚举
{
	70,60,50,100,80
};
uint8_t advanceLeftMoveModule[5]=//左腿移动的零部件枚举
{
	frontLeft_joint,middleRight_leg,middleRight_joint,rearLeft_leg,rearLeft_joint
};
uint8_t advanceRightLeftRight_Uplift[5]=//右腿移动抬起角度枚举
{
	90,70,80,110,90
////12 9 11 2 4
};
uint8_t advanceRightLeftRight_LayDown[5]=//右腿移动放下角度枚举
{
	40,110,130,70,40
};
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
		setAngle(11,110);
		Delay_ms(180);
		
		setAngle(12,60);
		Delay_ms(180);
		setAngle(13,60);
		Delay_ms(180);
		setAngle(14,130);
		Delay_ms(180);
		setAngle(15,50);
		Delay_ms(180);
}
void test(void)
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
		setAngle(13,170);
		//Delay_ms(180);
		setAngle(14,130);
		//Delay_ms(180);
		setAngle(15,50);
		//Delay_ms(180);
}
void _move_Toleg(front_Leg _leg,float _leg_angle,uint8_t* bodyModule,uint8_t* ModuleAngle)
{
	_leg(_leg_angle);
	Delay_ms(150);
	for(uint8_t i=0;i<5;i++)
	{
		setAngle(bodyModule[i],ModuleAngle[i]);
		Delay_ms(150);
	}
}
void AdvanceMove(void)
{
	//Timer_Init();
	//while(1)
	{
		_move_Toleg(ServoLegLeft_SetAngle,70,advanceLeftMoveModule,advanceLeftRightLeft_Uplift);
//		if(TIM2_IQRHandler()==1)
//		{
//			break;
//		}
	}
	//Timer_Init();
	//while(1)
	{
		_move_Toleg(ServoLegLeft_SetAngle,110,advanceLeftMoveModule,advanceLeftRightLeft_LayDown);
//		if(TIM2_IQRHandler()==1)
//		{
//		break;
//		}
	}
	//Timer_Init();
	//while(1)
	{
		_move_Toleg(ServoLegRight_SetAngle,120,advanceRightMoveModule,advanceRightLeftRight_Uplift);
//		if(TIM2_IQRHandler()==1)
//		{
//		break;
//		}
	}
	//Timer_Init();

	//while(1)
	{
		_move_Toleg(ServoLegRight_SetAngle,80,advanceRightMoveModule,advanceRightLeftRight_LayDown);
//		if(TIM2_IQRHandler()==1)
//		{
//			break;
//		}
	}

}
void normal(uint8_t* action)
{
	ServoLegLeft_SetAngle(110);
	//Delay_ms(180);
	ServoLegRight_SetAngle(80);
	//Delay_ms(180);
	for(uint8_t i=0;i<16;i++)
	{
		setAngle(body[i],action[i]);
		//Delay_ms(180);
	}
}
void standnormal(void)
{
	normal(stand_high);
}



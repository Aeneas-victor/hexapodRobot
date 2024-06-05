#ifndef __ACTION_H__
#define __ACTION_H__
#include<stdint.h>
typedef void(*front_Leg)(float);
enum Body{
	rearRight_foot=0,rearLeft_foot,//1
	rearRight_leg,rearLeft_leg,//3
	rearRight_joint,rearLeft_joint,//5
	
	middleRight_foot,middleLeft_foot,//7
	middleRight_leg,middleLeft_leg,//9
	middleRight_joint,middleLeft_joint,//11
	
	frontRight_joint,frontLeft_joint,//13
	frontRight_foot,frontLeft_foot//15
	
};


void Stand_High(void);
void trial_funtion(void);
void standnormal(void);
void _move_Toleg(front_Leg _leg,float _leg_angle,uint8_t* bodyModule,int8_t* ModuleAngle);//移动函数
void AdvanceMove(void);
void _Meanwhile_Advance_Move(uint8_t* a);
void _Move_(void);
void normal(uint8_t* action);
void side_leg_lift(void);
#endif


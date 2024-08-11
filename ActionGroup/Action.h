#ifndef __ACTION_H__
#define __ACTION_H__
#include "common.h"

void standnormal(void);
void _move_Toleg(uint8_t* bodyModule,int8_t* ModuleAngle);//移动函数
void AdvanceMove(void);
void _Meanwhile_Advance_Move(void);

void Wavy_Gait_Advance_Move(void);
void normal(uint8_t* action);
void side_leg_lift(void);
void Roration_place(uint8_t direction);
#endif


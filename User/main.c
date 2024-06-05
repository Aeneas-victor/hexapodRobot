#include "stm32f10x.h"
#include "sys.h"
#include "Delay.h"
#include "PCA9685.h"
#include "servo.h"
#include "Timer.h"
#include "Motor.h"
#include "Action.h"
//right A1
//left A0
int main(void)
{
	uint8_t a=0;
	PCA9685_Init(50,180);	
	Servo_Init();
	standnormal();
	while(1)
	{
		//side_leg_lift();
		//test();
		//AdvanceMove();
		_Meanwhile_Advance_Move(&a);
	}
}


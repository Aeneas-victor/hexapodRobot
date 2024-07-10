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
	
	while(1)
	{
		
		_Meanwhile_Advance_Move();
	}
}



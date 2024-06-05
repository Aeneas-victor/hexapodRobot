#include "stdint.h"
#include "bodymove.h"
#include "PCA9685.h"
#include "servo.h"

void front_left_foot(uint8_t angle)
{
	setAngle(15,angle);
}

void front_right_foot(uint8_t angle)
{
	setAngle(14,angle);
}

void midlle_left_foot(uint8_t angle)
{
	setAngle(7,angle);
}

void middle_right_foot(uint8_t angle)
{
	setAngle(8,angle);
}

void rear_left_root(uint8_t angle)
{
	setAngle(5,angle);
}

void rear_right_root(uint8_t angle)
{
	setAngle(0,angle);
}

void front_left_leg(uint8_t angle)
{
	ServoLegLeft_SetAngle(angle);
}

void front_right_leg(uint8_t angle)
{
	ServoLegRight_SetAngle(angle);
}

void middle_left_leg(uint8_t angle)
{
	setAngle(9,angle);
}

void middle_right_leg(uint8_t angle)
{
	setAngle(8,angle);
}

void rear_left_leg(uint8_t angle)
{
	setAngle(3,angle);
}

void rear_right_leg(uint8_t angle)
{
	setAngle(2,angle);
}

void front_left_joint(uint8_t angle)
{
	setAngle(15,angle);
}

void front_right_joint(uint8_t angle)
{
	setAngle(14,angle);
}

void middle_left_joint(uint8_t angle)
{
	setAngle(11,angle);
}

void middle_right_joint(uint8_t angle)
{
	setAngle(10,angle);
}

void rear_left_joint(uint8_t angle)
{
	setAngle(5,angle);
}

void rear_right_joint(uint8_t angle)
{
	setAngle(4,angle);
}









/*
 * servo1.c
 *
 *  Created on: Mar 24, 2023
 *      Author: Yüksel
 */
/*
 * servo.c
 *
 *  Created on: Mar 23, 2023
 *      Author: Yüksel
 */


#include "servo.h"


typedef struct
{
	uint16_t  period_Min;
	uint16_t  period_Max;


}SERVO_info;

static SERVO_info SERVO_Info[SERVO_NUM] = {0};


void SERVO_Init(uint16_t SERVO_Number, uint32_t TIM,uint32_t CHANNEL)
{
	HAL_TIM_PWM_Start(TIM,CHANNEL);


	//	Calculate & Save The Servo Pulse Information

	SERVO_Info[SERVO_Number].period_Min = (uint16_t) (47999 * (0.5/20.0));
	SERVO_Info[SERVO_Number].period_Max = (uint16_t) (47999 * (2.4/20.0));


}

void SERVO_MoveTo(uint16_t SERVO_Number, float Angle)
{
	uint16_t Pulse = 0;

	Pulse = ((Angle*(SERVO_Info[SERVO_Number].period_Max - SERVO_Info[SERVO_Number].period_Min))/180.0)
			+ SERVO_Info[SERVO_Number].period_Min;

	TIM2->CCR1 = Pulse;
}

void SERVO_RawMove(uint16_t SERVO_Number, uint16_t Pulse)
{
	if(Pulse <= SERVO_Info[SERVO_Number].period_Max && Pulse >= SERVO_Info[SERVO_Number].period_Min)
	{
		TIM2->CCR1 = Pulse;
	}
}

uint16_t SERVO_Get_MaxPulse(uint16_t SERVO_Number)
{
	return (SERVO_Info[SERVO_Number].period_Max);
}


/* Gets The Minimum Pulse Width Value For A Specific Motor */
uint16_t SERVO_Get_MinPulse(uint16_t SERVO_Number)
{
	return (SERVO_Info[SERVO_Number].period_Min);
}




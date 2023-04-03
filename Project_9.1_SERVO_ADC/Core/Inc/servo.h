/*
 * servo.h
 *
 *  Created on: Mar 23, 2023
 *      Author: Yüksel
 */

#ifndef INC_SERVO_H_
#define INC_SERVO_H_



#include "stm32f0xx_hal.h"


// The Number OF Servo Motors To Be Used In The Project

#define SERVO_NUM  1


/*-----[ Prototypes For All Functions ]-----*/

void SERVO_Init(uint16_t SERVO_Number, uint32_t TIM,uint32_t CHANNEL);
void SERVO_MoveTo(uint16_t SERVO_Number, float Angle);
void SERVO_RawMove(uint16_t SERVO_Number, uint16_t Pulse);
uint16_t SERVO_Get_MaxPulse(uint16_t SERVO_Number);
uint16_t SERVO_Get_MinPulse(uint16_t SERVO_Number);


#endif /* INC_SERVO_H_ */

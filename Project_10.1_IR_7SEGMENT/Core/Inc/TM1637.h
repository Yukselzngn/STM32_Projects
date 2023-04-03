/*
 * TM1637.h
 *
 *  Created on: Mar 27, 2023
 *      Author: Yüksel
 */

#ifndef INC_TM1637_H_
#define INC_TM1637_H_


void Display_Init(uint8_t brightness);//
void TM1637_Start();//
void TM1637_Stop();//
void TM1637_WriteData(uint8_t data);//
void sendTo_Display(uint8_t grid0,uint8_t grid1,uint8_t grid2,uint8_t grid3);//

void TM1637_CLK_SetHigh();
void TM1637_CLK_SetLow();
void TM1637_DIO_SetHigh();
void TM1637_DIO_SetLow();
void SomeDelay(uint32_t i);
uint8_t tm1637_NumberToSegments(uint8_t n);
#endif /* INC_TM1637_H_ */

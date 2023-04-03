/*
 * TM1637.c
 *
 *  Created on: Mar 27, 2023
 *      Author: Yüksel
 */

#ifndef SRC_TM1637_C_
#define SRC_TM1637_C_


#include "stm32f0xx_hal.h"
#include "TM1637.h"


#define TM1637_CLK_PORT GPIOB
#define TM1637_CLK_PIN GPIO_PIN_9

#define TM1637_DIO_PORT GPIOB
#define TM1637_DIO_PIN GPIO_PIN_8


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



void TM1637_Start(){
	TM1637_CLK_SetHigh();
	TM1637_DIO_SetHigh();

	SomeDelay(5);

	TM1637_DIO_SetLow();
}

void TM1637_Stop(){
	TM1637_CLK_SetHigh();
	TM1637_DIO_SetLow();

	SomeDelay(5);

	TM1637_DIO_SetHigh();

}




void TM1637_WriteData(uint8_t data){

	for (uint8_t i = 0; i < 8; i++) {

		TM1637_CLK_SetLow();

		(data & 0x01) ? TM1637_DIO_SetHigh():TM1637_DIO_SetLow();
		SomeDelay(7);
		data >>= 1;

		TM1637_CLK_SetHigh();

		SomeDelay(7);

	}

	//read ACK

	TM1637_CLK_SetLow();
	SomeDelay(5);
	TM1637_CLK_SetHigh();
	SomeDelay(5);
    TM1637_CLK_SetLow();

}





void sendTo_Display(uint8_t grid0,uint8_t grid1,uint8_t grid2,uint8_t grid3){


	TM1637_Start();
	TM1637_WriteData(0x40);
	TM1637_Stop();

	TM1637_Start();
	TM1637_WriteData(0xc0);

	TM1637_WriteData(grid0);

	TM1637_WriteData(grid1);

	TM1637_WriteData(grid2);

	TM1637_WriteData(grid3);

	TM1637_Stop();


}

void Display_Init(uint8_t brightness){
	TM1637_Start();
	TM1637_WriteData(0x84+brightness);
	TM1637_Stop();

	sendTo_Display(0,0,0,0);

}




void TM1637_CLK_SetHigh(){
	HAL_GPIO_WritePin(TM1637_CLK_PORT, TM1637_CLK_PIN, GPIO_PIN_SET);
}


void TM1637_CLK_SetLow(){
	HAL_GPIO_WritePin(TM1637_CLK_PORT, TM1637_CLK_PIN, GPIO_PIN_RESET);
}

void TM1637_DIO_SetHigh(){
	HAL_GPIO_WritePin(TM1637_DIO_PORT, TM1637_DIO_PIN, GPIO_PIN_SET);
}
void TM1637_DIO_SetLow(){
	HAL_GPIO_WritePin(TM1637_DIO_PORT, TM1637_DIO_PIN, GPIO_PIN_RESET);
}


void SomeDelay(uint32_t i){
    while (i > 0) {
    	for (uint32_t j = 0; j < 10; j++) {
    		__NOP();
    	};
    	i--;
    };
}





//Convert number to 7-segment code
uint8_t tm1637_NumberToSegments(uint8_t n){
	if (n == 0) return 0x3F;//0
	if (n == 1) return 0x06;//1
	if (n == 2) return 0x5B;//2
	if (n == 3) return 0x4F;//3
	if (n == 4) return 0x66;//4
	if (n == 5) return 0x6D;//5
	if (n == 6) return 0x7D;//6
	if (n == 7) return 0x07;//7
	if (n == 8) return 0x7F;//8
	if (n == 9) return 0x6F;//9

	return 0x00;
}





















#endif /* SRC_TM1637_C_ */

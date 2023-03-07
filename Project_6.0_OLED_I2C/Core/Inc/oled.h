/*
 * oled.h
 *
 *  Created on: 7 Mar 2023
 *      Author: Yüksel
 */

#ifndef INC_OLED_H_
#define INC_OLED_H_

#include "stm32f0xx_hal.h"
#include "fonts.h"
#include "stdlib.h"
#include "string.h"

#define OLED_I2C_ADDR         0x78

#define SSD1306_WIDTH            128

#define SSD1306_HEIGHT           64

#endif /* INC_OLED_H_ */

typedef enum {
	SSD1306_COLOR_BLACK = 0x00, /*!< Black color, no pixel */
	SSD1306_COLOR_WHITE = 0x01  /*!< Pixel is set. Color depends on LCD */
} SSD1306_COLOR_t;


uint8_t SSD1306_Init(void);
void SSD1306_UpdateScreen(void);
void SSD1306_Fill(SSD1306_COLOR_t Color);
void SSD1306_DrawPixel(uint16_t x, uint16_t y, SSD1306_COLOR_t color);
void SSD1306_GotoXY(uint16_t x, uint16_t y);
char SSD1306_Putc(char ch, FontDef_t* Font, SSD1306_COLOR_t color);
char SSD1306_Puts(char* str, FontDef_t* Font, SSD1306_COLOR_t color);

void ssd1306_I2C_Init();
void ssd1306_I2C_Write(uint8_t command);
void ssd1306_I2C_WriteMulti(uint8_t reg, uint8_t *data, uint16_t count);
void SSD1306_Clear (void);
















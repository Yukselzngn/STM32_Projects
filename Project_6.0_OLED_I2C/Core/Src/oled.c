/*
 * oled.c
 *
 *  Created on: 7 Mar 2023
 *      Author: Yüksel
 */


#include "oled.h"

extern I2C_HandleTypeDef hi2c1;

static uint8_t SSD1306_Buffer[SSD1306_WIDTH * SSD1306_HEIGHT / 8];


typedef struct {
	uint16_t CurrentX;
	uint16_t CurrentY;
} SSD1306_t;

static SSD1306_t SSD1306;


uint8_t SSD1306_Init(void) {
	HAL_I2C_IsDeviceReady(&hi2c1, OLED_I2C_ADDR, 1,200);

	SSD1306_WRITECOMMAND(0x20);
	SSD1306_WRITECOMMAND(0x10);
	SSD1306_WRITECOMMAND(0xB0);
	SSD1306_WRITECOMMAND(0xC8);
	SSD1306_WRITECOMMAND(0x00);
	SSD1306_WRITECOMMAND(0x10);
	SSD1306_WRITECOMMAND(0x40);
	SSD1306_WRITECOMMAND(0x81);
	SSD1306_WRITECOMMAND(0xFF);
	SSD1306_WRITECOMMAND(0xA1);
	SSD1306_WRITECOMMAND(0xA6);
	SSD1306_WRITECOMMAND(0xA8);
	SSD1306_WRITECOMMAND(0x3F); //
	SSD1306_WRITECOMMAND(0xA4);
	SSD1306_WRITECOMMAND(0xD3);
	SSD1306_WRITECOMMAND(0x00);
	SSD1306_WRITECOMMAND(0xD5);
	SSD1306_WRITECOMMAND(0xD9);
	SSD1306_WRITECOMMAND(0x22);
	SSD1306_WRITECOMMAND(0xDA);
	SSD1306_WRITECOMMAND(0xDB);
	SSD1306_WRITECOMMAND(0x8D); //--set DC-DC enable
	SSD1306_WRITECOMMAND(0xAF);

	SSD1306_WRITECOMMAND(0x21);


	 //Clear screen
	SSD1306_Fill(SSD1306_COLOR_BLACK);

	// Update screen
	SSD1306_UpdateScreen();

	// Set default values
	SSD1306.CurrentX = 0;
	SSD1306.CurrentY = 0;

}


void SSD1306_UpdateScreen(void) {
	uint8_t m;

	for (m = 0; m < 8; m++) {
		SSD1306_WRITECOMMAND(0xB0 + m);
		SSD1306_WRITECOMMAND(0x00);
		SSD1306_WRITECOMMAND(0x10);

		/* Write multi data */
		ssd1306_I2C_WriteMulti(0x40, &SSD1306_Buffer[SSD1306_WIDTH * m], SSD1306_WIDTH);
	}
}


void SSD1306_Fill(SSD1306_COLOR_t color) {
	/* Set memory */
	memset(SSD1306_Buffer, (color == SSD1306_COLOR_BLACK) ? 0x00 : 0xFF, sizeof(SSD1306_Buffer));
}

void SSD1306_GotoXY(uint16_t x, uint16_t y) {
	/* Set write pointers */
	SSD1306.CurrentX = x;
	SSD1306.CurrentY = y;
}



void SSD1306_DrawPixel(uint16_t x, uint16_t y, SSD1306_COLOR_t color) {



	/* Set color */
	if (color == SSD1306_COLOR_WHITE) {
		SSD1306_Buffer[x + (y / 8) * SSD1306_WIDTH] |= 1 << (y % 8);      // pixel on
	} else {
		SSD1306_Buffer[x + (y / 8) * SSD1306_WIDTH] &= ~(1 << (y % 8));	  // pixel off
	}
}

char SSD1306_Putc(char ch, FontDef_t* Font, SSD1306_COLOR_t color) {
	uint32_t i, b, j;


	/* Go through font */
	for (i = 0; i < Font->FontHeight; i++) {
		b = Font->data[(ch - 32) * Font->FontHeight + i];
		for (j = 0; j < Font->FontWidth; j++) {
			if ((b << j) & 0x8000) {
				SSD1306_DrawPixel(SSD1306.CurrentX + j, (SSD1306.CurrentY + i), (SSD1306_COLOR_t) color);
			} else {
				SSD1306_DrawPixel(SSD1306.CurrentX + j, (SSD1306.CurrentY + i), (SSD1306_COLOR_t)!color);
			}
		}
	}

	/* Increase pointer */
	SSD1306.CurrentX += Font->FontWidth;

	/* Return character written */
	return ch;
}

char SSD1306_Puts(char* str, FontDef_t* Font, SSD1306_COLOR_t color) {
	/* Write characters */
	while (*str) {
		/* Write character by character */
		if (SSD1306_Putc(*str, Font, color) != *str) {
			/* Return error */
			return *str;
		}

		/* Increase string pointer */
		str++;
	}

	/* Everything OK, zero should be returned */
	return *str;
}



void SSD1306_Clear (void)
{
	SSD1306_Fill (0);
    SSD1306_UpdateScreen();
}




void SSD1306_WRITECOMMAND(uint8_t command) {
	uint8_t dt[2];
	dt[0] = 0x00;
	dt[1] = command;
	HAL_I2C_Master_Transmit(&hi2c1, OLED_I2C_ADDR, dt, 2, 10);
}




void ssd1306_I2C_WriteMulti(uint8_t reg, uint8_t* data, uint16_t count) {
uint8_t dt[256];
dt[0] = reg;
uint8_t i;
for(i = 0; i < count; i++)
dt[i+1] = data[i];
HAL_I2C_Master_Transmit(&hi2c1, OLED_I2C_ADDR, dt, count+1, 10);
}











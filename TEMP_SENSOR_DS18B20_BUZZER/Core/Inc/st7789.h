/*
 * st7789.h
 *
 *  Created on: Aug 27, 2024
 *      Author: Aleh
 */

#ifndef INC_ST7789_H_
#define INC_ST7789_H_

#define ST7789_COLMOD 			  0x3A
#define ST7789_COLMOD_PARAM_16BIT 0x55

#define ST7789_RAMWR			  0x2C
#define ST7789_DISPON			  0x29
#define ST7789_DC_DATA		      1
#define ST7789_DC_CMD			  0
#define ST7789_SWRESET			  0x01

#define ST7789_SLPOUT			  0x11

void ST7789_Init();
void ST7789_WriteFrame();

#define USING_240X240
#define ST7789_ROTATION 2

#ifdef USING_240X240

    #define ST7789_WIDTH 240
    #define ST7789_HEIGHT 240

		#if ST7789_ROTATION == 0
			#define X_SHIFT 0
			#define Y_SHIFT 80
		#elif ST7789_ROTATION == 1
			#define X_SHIFT 80
			#define Y_SHIFT 0
		#elif ST7789_ROTATION == 2
			#define X_SHIFT 0
			#define Y_SHIFT 0
		#elif ST7789_ROTATION == 3
			#define X_SHIFT 0
			#define Y_SHIFT 0
		#endif

#endif


#define WHITE       0xFFFF
#define BLACK       0x0000
#define BLUE        0x001F
#define RED         0xF800
#define MAGENTA     0xF81F
#define GREEN       0x07E0
#define CYAN        0x7FFF
#define YELLOW      0xFFE0
#define GRAY        0X8430
#define BRED        0XF81F
#define GRED        0XFFE0
#define GBLUE       0X07FF
#define BROWN       0XBC40
#define BRRED       0XFC07
#define DARKBLUE    0X01CF
#define LIGHTBLUE   0X7D7C
#define GRAYBLUE    0X5458

#define LIGHTGREEN  0X841F
#define LGRAY       0XC618
#define LGRAYBLUE   0XA651
#define LBBLUE      0X2B12

#define ST7789_CASET   0x2A
#define ST7789_RASET   0x2B
#define ST7789_INVON   0x21
#define ST7789_NORON   0x13
#define ST7789_MADCTL  0x36

void ST7789_SendCmd(uint8_t cmd);
void ST7789_SendDataPortion(uint8_t data);
void ST7789_SetAddressWindow(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye);
void ST7789_DrawString(char* str, uint16_t strSize, uint16_t xs, uint16_t ys, uint16_t xe, uint16_t rgb, uint16_t backgroundColor);

/* Page Address Order ('0': Top to Bottom, '1': the opposite) */
#define ST7789_MADCTL_MY  0x80
/* Column Address Order ('0': Left to Right, '1': the opposite) */
#define ST7789_MADCTL_MX  0x40
/* Page/Column Order ('0' = Normal Mode, '1' = Reverse Mode) */
#define ST7789_MADCTL_MV  0x20
/* Line Address Order ('0' = LCD Refresh Top to Bottom, '1' = the opposite) */
#define ST7789_MADCTL_ML  0x10
/* RGB/BGR Order ('0' = RGB, '1' = BGR) */
#define ST7789_MADCTL_RGB 0x00

#endif /* INC_ST7789_H_ */

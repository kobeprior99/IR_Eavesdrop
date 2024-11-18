/* 
 * File:   oled.h
 * Author: http://pic18fxx.blogspot.com 
 *
 * Graphical display OLED.
 * Driver:
 * Version 4.0.
 * Interface: SPI, I2C.
 */
#ifndef OLED_H
#define	OLED_H
//==============================================================================
// Includes.
//==============================================================================
#include "ide.h"
#include "datatypes.h"
#include "time_delay.h"

//==============================================================================
// Configuration of the library.(1). Select your display.
//==============================================================================
//#define DRIVER_SSD1306_96x16
//#define DRIVER_SSD1306_128x32
#define DRIVER_SSD1306_128x64
//#define DRIVER_SSD1309_128x64
//#define DRIVER_SH1106_132x64
//#define DRIVER_SH1107_64x128
//#define DRIVER_UC1609C_192x64
//#define DRIVER_ST7565R_128x64
//#define DRIVER_NOKIA5110_84x48

//==============================================================================
// Configuration of the library.(2). Select your interface.
//==============================================================================
#define DISPLAY_SPI_INTERFACE
//#define DISPLAY_I2C_INTERFACE

//==============================================================================
// Configuration of the library.(3). Define the maximum number of characters for scroll.
//==============================================================================
#define TEXT_SCROLL				50

//==============================================================================
// Configuration of the library.(4). Enable Frames per second.
//==============================================================================
//#define DISPLAY_INTERRUPT

//==============================================================================
// Configuration of the library.(5). Bitmap coding.
//==============================================================================
//#define BITMAP_CODING1
#define BITMAP_CODING2

//==============================================================================
// Configuration of the library.(6). Includes, SPI1, SPI2, I2C1, I2C2.
//==============================================================================
#ifdef DISPLAY_SPI_INTERFACE
#ifdef STM32CUBE_IDE
#include "main.h"
#include "spi.h"
#include "gpio.h"
#define OLED_WRITE_CMD(a)       HAL_SPI_Transmit(&hspi1, a, 1, 10)
#define OLED_WRITE_RAM(a, b)    HAL_SPI_Transmit(&hspi1, a, b, 10)
#define OLED_CS1()              HAL_GPIO_WritePin(OLED_CS_GPIO_Port, OLED_CS_Pin, GPIO_PIN_SET)
#define OLED_CS0()              HAL_GPIO_WritePin(OLED_CS_GPIO_Port, OLED_CS_Pin, GPIO_PIN_RESET)
#define OLED_DC1()              HAL_GPIO_WritePin(OLED_DC_GPIO_Port, OLED_DC_Pin, GPIO_PIN_SET)
#define OLED_DC0()              HAL_GPIO_WritePin(OLED_DC_GPIO_Port, OLED_DC_Pin, GPIO_PIN_RESET)
#define OLED_RST1()             HAL_GPIO_WritePin(OLED_RST_GPIO_Port, OLED_RST_Pin, GPIO_PIN_SET)
#define OLED_RST0()             HAL_GPIO_WritePin(OLED_RST_GPIO_Port, OLED_RST_Pin, GPIO_PIN_RESET)
#endif
#ifdef MPLABX_IDE
#include "mcc_generated_files/mcc.h"
#define OLED_WRITE_CMD(a)       SPI1_ExchangeByte(a)
#define OLED_WRITE_RAM(a, b)    SPI1_WriteBlock(a, b)
#define OLED_CS1()              OLED_CS_SetHigh()
#define OLED_CS0()              OLED_CS_SetLow()
#define OLED_DC1()              OLED_DC_SetHigh()
#define OLED_DC0()              OLED_DC_SetLow()
#define OLED_RST1()             OLED_RST_SetHigh()
#define OLED_RST0()             OLED_RST_SetLow()
#endif
#ifdef RASPBERRY_IDE
#endif
#endif

#ifdef DISPLAY_I2C_INTERFACE
#ifdef STM32CUBE_IDE
#include "main.h"
#include "i2c.h"
#include "gpio.h"
#define OLED_12C_ADDRES         0x78    // If SA0 = 0.
#define OLED_WRITE_CMD(a)       HAL_I2C_Mem_Write(&hi2c1, OLED_12C_ADDRES, 0x00, 1, a, 1, 100)
#define OLED_WRITE_RAM(a, b)    HAL_I2C_Mem_Write(&hi2c1, OLED_12C_ADDRES, 0x40, 1, a, b, 100)
#define OLED_RST1()             HAL_GPIO_WritePin(OLED_RST_GPIO_Port, OLED_RST_Pin, GPIO_PIN_SET)
#define OLED_RST0()             HAL_GPIO_WritePin(OLED_RST_GPIO_Port, OLED_RST_Pin, GPIO_PIN_RESET)
#endif
#ifdef MPLABX_IDE
#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/examples/i2c2_master_example.h"
#define OLED_12C_ADDRES         0x3C    // If SA0 = 0.
#define OLED_WRITE_CMD(a)       I2C2_Write1ByteRegister(OLED_12C_ADDRES, 0x00, a)
#define OLED_WRITE_RAM(a, b)    I2C2_WriteNBytes(OLED_12C_ADDRES, a, b)
#define OLED_RST1()             OLED_RST_SetHigh()
#define OLED_RST0()             OLED_RST_SetLow()
#endif
#ifdef RASPBERRY_IDE
#endif
#endif

//==============================================================================
// Defines, structs and functions.
// This section of code must not be changed.
//==============================================================================
#define DISPLAY_0				0x00
#define DISPLAY_90				0x01
#define DISPLAY_180				0x02
#define DISPLAY_270				0x03
#define PIXEL_0                 0x00
#define PIXEL_1                 0x01
#define PIXEL_INVERSE           0x02
#define PIXEL_RETURN			0x03
#define PIXEL_ERROR				0x04
#define DEC_CONTRAST			0x00
#define INC_CONTRAST			0x01
#define DISPLAY_DELAY1			0x04		// (1000 ms / 4) / 8 pages = 31.25 Frames per second.

#ifdef DRIVER_SSD1306_96x16
#define DISPLAY_W				96
#define DISPLAY_H				16
#define DISPLAY_MAX_CONTRAST	255
#define DISPLAY_MIN_CONTRAST	1
#define DISPLAY_INIT_DEFAULT
#define DISPLAY_FUNC_DEFAULT
#endif

#ifdef DRIVER_SSD1306_128x32
#define DISPLAY_W				128
#define DISPLAY_H				32
#define DISPLAY_MAX_CONTRAST	255
#define DISPLAY_MIN_CONTRAST	1
#define DISPLAY_INIT_DEFAULT
#define DISPLAY_FUNC_DEFAULT
#endif

#ifdef DRIVER_SSD1306_128x64
#define DISPLAY_W				128
#define DISPLAY_H				64
#define DISPLAY_MAX_CONTRAST	255
#define DISPLAY_MIN_CONTRAST	1
#define DISPLAY_INIT_DEFAULT
#define DISPLAY_FUNC_DEFAULT
#endif

#ifdef DRIVER_SSD1309_128x64
#define DISPLAY_W				128
#define DISPLAY_H				64
#define DISPLAY_MAX_CONTRAST	255
#define DISPLAY_MIN_CONTRAST	1
#define DISPLAY_INIT_DEFAULT
#define DISPLAY_FUNC_DEFAULT
#endif

#ifdef DRIVER_SH1106_132x64
#define DISPLAY_W				130
#define DISPLAY_H				64
#define DISPLAY_MAX_CONTRAST	255
#define DISPLAY_MIN_CONTRAST	1
#define DISPLAY_INIT_DEFAULT
#define DISPLAY_FUNC_DEFAULT
#endif

#ifdef DRIVER_SH1107_64x128
#define DISPLAY_W				64
#define DISPLAY_H				128
#define DISPLAY_MAX_CONTRAST	255
#define DISPLAY_MIN_CONTRAST	1
#define DISPLAY_FUNC_DEFAULT
#endif

#ifdef DRIVER_UC1609C_192x64
#define DISPLAY_W				192
#define DISPLAY_H				64
#define DISPLAY_MAX_CONTRAST	180
#define DISPLAY_MIN_CONTRAST	134
#define DISPLAY_FUNC_DEFAULT
#endif

#ifdef DRIVER_ST7565R_128x64
#define DISPLAY_W				128
#define DISPLAY_H				64
#define DISPLAY_MAX_CONTRAST	100
#define DISPLAY_MIN_CONTRAST	90
#define DISPLAY_FUNC_DEFAULT
#endif

#ifdef DRIVER_NOKIA5110_84x48
#define DISPLAY_W				84
#define DISPLAY_H				48
#define DISPLAY_MAX_CONTRAST	191
#define DISPLAY_MIN_CONTRAST	183
#endif

#define DISPLAY_RAM				DISPLAY_W * (DISPLAY_H / 8)

typedef struct{
	U8 Contrast;
	//U8 Sleep;
	U8 FrameMemory;
	U8 WrRam;
	U8 Ram[DISPLAY_RAM];
	U16 X, Y;
	U16 Cnt1, Cnt2;
}STRUCT_DISPLAY;
extern STRUCT_DISPLAY Display;

typedef struct{
	U8 FirstCharacter;
	U8 LastCharacter;
	U8 Height;
	U8 Width;
	U8 LetterSpacing;
	CU8 *Ptr1, *Ptr2;
}STRUCT_FONT;
extern STRUCT_FONT Font;

typedef struct{
	U16 Height;
	U16 Width;
}STRUCT_IMAGE;
extern STRUCT_IMAGE Image;

typedef struct{
	S8 Text[TEXT_SCROLL];
	U8 Width;
	U16 SizeText;
	U16 X1, Y1, X2, Y2;
	U16 CntCh;
	U16 Cnt1, Cnt2;
}STRUCT_SCROLL;

void Oled_Init(U8 frame_memory_);
void Oled_Driver(void);
void Oled_Reset(void);
void Oled_Command(U8 cmd);
void Oled_WritePage(U8 *p, U16 seg1, U16 seg2, U16 pag);
void Oled_SetPointer(U16 seg, U16 pag);
void Oled_OFF(void);
void Oled_ON(void);
void Oled_Contrast(U8 cmd);
void Oled_SetContrast(void);
void Oled_MemoryAccessControl(U8 frame_memory);
void Oled_SetFont(CU8 *p, U8 letterspacing);
void Oled_WriteChar(U8 c, U16 x, U16 y);
U16 Oled_TextWidth(S8 *p);
void Oled_ConstText(CS8 *p, U16 x, U16 y);
void Oled_Text(S8 *p, U16 x, U16 y);
void Oled_TextCenter(S8 *p, U16 x1, U16 y1, U16 x2, U8 pixel_);
void Oled_TextLeft(S8 *p, U16 x1, U16 y1, U16 x2, U8 pixel_);
void Oled_TextRight(S8 *p, U16 x1, U16 y1, U16 x2, U8 pixel_);
void Oled_InitScroll(STRUCT_SCROLL *p1, S8 *p2, U16 x1, U16 y1, U16 x2);
void Oled_TextScroll(STRUCT_SCROLL *p, U16 delay_scroll);
void Oled_DelayScroll(STRUCT_SCROLL *p);
void Oled_ScrollArea(U16 x1, U16 y1, U16 x2, U16 y2);
void Oled_Image(CU8 *p, U16 x, U16 y, U8 pixel_);
void Oled_FillScreen(U8 pattern);
void Oled_FillArea(U16 x1, U16 y1, U16 x2, U16 y2, U8 pixel_);
void Oled_Line(U16 x1, U16 y1, U16 x2, U16 y2, U8 pixel_);
void Oled_Rectangle(U16 x1, U16 y1, U16 x2, U16 y2, U8 pixel_);
void Oled_Circle(U16 x1, U16 y1, U16 radius, U8 pixel_);
U8 Oled_Pixel(U16 x, U16 y, U8 pixel_);
void Oled_WriteArea(U16 x1, U16 y1, U16 x2, U16 y2);
void Oled_INT(void);
void Oled_SetInterruptHandler(void (*p)(void));
extern void (*Oled_InterruptHandler)(void);
#endif	/* OLED_H */

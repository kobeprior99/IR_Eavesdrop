/*
 * File:   oled.c
 * Author: http://pic18fxx.blogspot.com
 *
 * Graphical display OLED.
 * Driver:
 * Version 4.0
 * Interface: SPI, I2C.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "oled.h"

//==============================================================================
// Structs.
//==============================================================================
STRUCT_DISPLAY Display;
STRUCT_FONT Font;
STRUCT_IMAGE Image;
void (*Oled_InterruptHandler)(void);

//==============================================================================
// This function initializes the display.
// The rotation can be DISPLAY_0, DISPLAY_90, DISPLAY_180 and DISPLAY_270.
// Example:
// Oled_Init(DISPLAY_0);
//==============================================================================
void Oled_Init(U8 frame_memory_) {
    Oled_Reset();
    Oled_MemoryAccessControl(frame_memory_);
    Oled_Driver();
    Oled_FillScreen(0x00);
    Display.Cnt1 = 0;
    Display.Cnt2 = 0;
    Display.WrRam = 1;
    Display.Contrast = DISPLAY_MAX_CONTRAST;
}

//==============================================================================
// This function sets the contrast.
// Examples:
// Oled_Contrast(DEC_CONTRAST);
// Oled_Contrast(INC_CONTRAST);
//==============================================================================
void Oled_Contrast(U8 cmd) {
	if(cmd == INC_CONTRAST && Display.Contrast < DISPLAY_MAX_CONTRAST)
	{
		Display.Contrast++;
	}
	if(cmd == DEC_CONTRAST && Display.Contrast > DISPLAY_MIN_CONTRAST)
	{
		Display.Contrast--;
	}
	Oled_SetContrast();
}

//==============================================================================
// This function sets the rotation of display.
// The rotation can be DISPLAY_0, DISPLAY_90, DISPLAY_180 and DISPLAY_270.
// Example:
// Oled_MemoryAccessControl(DISPLAY_90);
//==============================================================================
void Oled_MemoryAccessControl(U8 frame_memory) {
    switch(frame_memory)
    {
    case DISPLAY_0:
    case DISPLAY_180:
        Display.X = DISPLAY_W - 1;
        Display.Y = DISPLAY_H - 1;
        break;
    case DISPLAY_90:
    case DISPLAY_270:
        Display.X = DISPLAY_H - 1;
        Display.Y = DISPLAY_W - 1;
        break;
    }
    Display.FrameMemory = frame_memory;
}

//==============================================================================
// This function sets the font.
// I would like to use the font "Terminal6x8" with a letter space of 4 pixels.
// Example:
// Oled_SetFont(Terminal6x8, 4);
// Oled_ConstText("Hello", 0, 0);
//==============================================================================
void Oled_SetFont(CU8 *p, U8 letterspacing) {
    Font.Ptr2 = p;
    p += 2;
    Font.FirstCharacter = *p;
    p += 2;
    Font.LastCharacter = *p;
    p += 2;
    Font.Height = *p;
    Font.LetterSpacing = letterspacing;
}

//==============================================================================
// This function writes a character.
// I need to write just the character 'A' at x = 0, y = 3.
// Example:
// Oled_WriteChar('A', 0, 3);
//==============================================================================
void Oled_WriteChar(U8 c, U16 x, U16 y) {
    U16 i, j, k;
    if(Display.WrRam == 1)
    {
        Display.WrRam = 2;
    }
    k = c - Font.FirstCharacter;
    k *= 4;
    k += 8;
    Font.Ptr1 = Font.Ptr2;
    Font.Ptr1 += k;
    Font.Width = *Font.Ptr1;
    Font.Ptr1 += 2;
    k = *Font.Ptr1;
    Font.Ptr1 -= 1;
    k = (k << 8) | *Font.Ptr1;
    Font.Ptr1 = Font.Ptr2;
    Font.Ptr1 += k;
    for(j = 0; j < Font.Height; j++)
    {
        for(i = 0; i < Font.Width + Font.LetterSpacing; i++)
        {
            if(i < Font.Width)
            {
                if(*Font.Ptr1 & (0x01 << (i % 8)))
                {
                    Oled_Pixel(x + i, y + j, PIXEL_1);
                } else
                {
                    Oled_Pixel(x + i, y + j, PIXEL_0);
                }
                if((i % 8) == 7 && i < Font.Width - 1)
                {
                    Font.Ptr1++;
                }
            } else
            {
                Oled_Pixel(x + i, y + j, PIXEL_0);
            }
        }
        Font.Ptr1++;
    }
    if(Display.WrRam == 2)
    {
#ifndef DISPLAY_INTERRUPT
        Oled_WriteArea(x, y, x + Font.Width + Font.LetterSpacing, y + Font.Height);
#endif
        Display.WrRam = 1;
    }
}

//==============================================================================
// This function returns the width of a text at pixels.
// May I get the width of a text?
// Example:
// unsigned short i;
// i = Oled_TextWidth((char *)"Hello!");
//==============================================================================
U16 Oled_TextWidth(S8 *p) {
    U16 i, text_width = 0;
    while(*p)
    {
        i = *p - Font.FirstCharacter;
        i *= 4;
        i += 8;
        Font.Ptr1 = Font.Ptr2;
        Font.Ptr1 += i;
        text_width += *Font.Ptr1;
        text_width += Font.LetterSpacing;
        p++;
    }
    text_width -= Font.LetterSpacing;
    return text_width;
}

//==============================================================================
// This function writes constant text.
// How can I write text? I want to try "Hi" at x = 14, y = 20.
// Example:
// Oled_ConstText("Hi", 14, 20);
//==============================================================================
void Oled_ConstText(CS8 *p, U16 x, U16 y) {
#ifndef DISPLAY_INTERRUPT
    U16 i = x;
    U16 j = y + Font.Height;
#endif
    Display.WrRam = 0;
    while(*p)
    {
        Oled_WriteChar(*p, x, y);
        x += Font.Width + Font.LetterSpacing;
        p++;
    }
    Display.WrRam = 1;
#ifndef DISPLAY_INTERRUPT
    Oled_WriteArea(i, y, x, j);
#endif
}

//==============================================================================
// This function writes variable text.
// Now, I have a variable. How should I write my variable at x = 3, y = 6?.
// Example:
// char b[20];
// int i;
// i = 36;
// sprintf(b, "%02d", i);
// Oled_Text(b, 3, 6);
//==============================================================================
void Oled_Text(S8 *p, U16 x, U16 y) {
#ifndef DISPLAY_INTERRUPT
    U16 i = x;
    U16 j = y + Font.Height;
#endif
    Display.WrRam = 0;
    while(*p)
    {
        Oled_WriteChar(*p, x, y);
        x += Font.Width + Font.LetterSpacing;
        p++;
    }
    Display.WrRam = 1;
#ifndef DISPLAY_INTERRUPT
    Oled_WriteArea(i, y, x, j);
#endif
}

//==============================================================================
// Functions with alignment text.
// I have understood  the previous functions. How can I write text with alignment?
// Examples:
//
// Oled_MemoryAccessControl(DISPLAY_0);
// Oled_FillScreen(0x00);
// Oled_SetFont(Terminal11x16, 1);
//
// Write "Settings" at x1 = 0, y1 = 0, x2 = 127 and pixel inverse.
// Oled_TextCenter((char *)"Settings", 0, 0, Display.X, PIXEL_INVERSE);
//
// Write "36" at x1 = 0, y1 = 20, x2 = 40 and pixel inverse.
// Oled_TextLeft((char *)"36", 0, 20, 40, PIXEL_INVERSE);
//
// Write "36" at x1 = 0, y1 = 40, x2 = 40 and pixel inverse.
// Oled_TextRight((char *)"36", 0, 40, 40, PIXEL_INVERSE);
//
// Have sense?
//==============================================================================
void Oled_TextCenter(S8 *p, U16 x1, U16 y1, U16 x2, U8 pixel_) {
    U16 i, j;
    Display.WrRam = 0;
    i = x2 - x1;
    i -= Oled_TextWidth(p);
    i /= 2;
    i += x1;
    i++;
    j = y1 + Font.Height;
    j--;
    Oled_FillArea(x1, y1, x2, j, PIXEL_0);
    while(*p)
    {
        Oled_WriteChar(*p, i, y1);
        i += Font.Width + Font.LetterSpacing;
        p++;
    }
    if(pixel_ == PIXEL_INVERSE)
    {
        Oled_FillArea(x1, y1, x2, j, PIXEL_INVERSE);
    }
    Display.WrRam = 1;
#ifndef DISPLAY_INTERRUPT
    Oled_WriteArea(x1, y1, x2, j);
#endif
}

void Oled_TextLeft(S8 *p, U16 x1, U16 y1, U16 x2, U8 pixel_) {
    U16 i, j;
    Display.WrRam = 0;
    i = x1;
    j = y1 + Font.Height;
    j--;
    while(*p)
    {
        Oled_WriteChar(*p, i, y1);
        i += Font.Width + Font.LetterSpacing;
        p++;
    }
    Oled_FillArea(i, y1, x2, j, PIXEL_0);
    if(pixel_ == PIXEL_INVERSE)
    {
        Oled_FillArea(x1, y1, x2, j, PIXEL_INVERSE);
    }
    Display.WrRam = 1;
#ifndef DISPLAY_INTERRUPT
    Oled_WriteArea(x1, y1, x2, j);
#endif
}

void Oled_TextRight(S8 *p, U16 x1, U16 y1, U16 x2, U8 pixel_) {
    U16 i, j;
    Display.WrRam = 0;
    i = x2 - Oled_TextWidth(p);
    j = y1 + Font.Height;
    j--;
    Oled_FillArea(x1, y1, i, j, PIXEL_0);
    while(*p)
    {
        Oled_WriteChar(*p, i, y1);
        i += Font.Width + Font.LetterSpacing;
        p++;
    }
    if(pixel_ == PIXEL_INVERSE)
    {
        Oled_FillArea(x1, y1, x2, j, PIXEL_INVERSE);
    }
    Display.WrRam = 1;
#ifndef DISPLAY_INTERRUPT
    Oled_WriteArea(x1, y1, x2, j);
#endif
}

//==============================================================================
// Functions for scrolling text.
// Is easy to use these functions, but an internal timer must be used.
// Please consult demo!.
//==============================================================================
void Oled_InitScroll(STRUCT_SCROLL *p1, S8 *p2, U16 x1, U16 y1, U16 x2) {
    strcpy(p1->Text, p2);
    p1->SizeText = strlen(p1->Text);
    p1->CntCh = 0;
    p1->Cnt1 = 0;
    p1->Cnt2 = 0;
    p1->X1 = x1;
    p1->Y1 = y1;
    p1->X2 = x2;
    p1->Y2 = y1 + Font.Height;
    Oled_WriteChar(p1->Text[p1->CntCh], p1->X2, p1->Y1);
    p1->Width = Font.Width + Font.LetterSpacing;
}

void Oled_TextScroll(STRUCT_SCROLL *p, U16 delay_scroll) {
    if(p->Cnt1 > delay_scroll)
    {
        if(p->Cnt2 == p->Width)
        {
            p->Cnt2 = 0;
            p->CntCh++;
            if(p->CntCh == p->SizeText)
            {
                p->CntCh = 0;
            }
            Oled_WriteChar(p->Text[p->CntCh], p->X2, p->Y1);
            p->Width = Font.Width + Font.LetterSpacing;
        }
        Oled_ScrollArea(p->X1, p->Y1, p->X2 + p->Width, p->Y2);
        p->Cnt1 = 0;
        p->Cnt2++;
    }
}

void Oled_DelayScroll(STRUCT_SCROLL *p) {
    p->Cnt1++;
}

void Oled_ScrollArea(U16 x1, U16 y1, U16 x2, U16 y2) {
    U8 pixel_;
    U16 i, j;
    Display.WrRam = 0;
    for(i = x1; i < x2; i++)
    {
        for(j = y1; j <= y2; j++)
        {
            pixel_ = Oled_Pixel(i + 1, j, PIXEL_RETURN);
            Oled_Pixel(i, j, pixel_);
        }
    }
    Display.WrRam = 1;
#ifndef DISPLAY_INTERRUPT
    Oled_WriteArea(x1, y1, x2, y2);
#endif
}

//==============================================================================
// This function draws an image.
// I am looking for drawing an image or icons. How should I try truck_bmp at x = 0, y = 0 with pixel inverted?.
// Example:
// Oled_Image(truck_bmp, 0, 0, PIXEL_1);
//==============================================================================
void Oled_Image(CU8 *p, U16 x, U16 y, U8 pixel_) {
    U8 pixel_0, pixel_1;
    U16 i, j;
    Display.WrRam = 0;
    if(pixel_ == PIXEL_INVERSE)
    {
        pixel_0 = PIXEL_1;
        pixel_1 = PIXEL_0;
    } else
    {
        pixel_0 = PIXEL_0;
        pixel_1 = PIXEL_1;
    }
    p += 3;
    Image.Width = *p;
    p--;
    Image.Width <<= 8;
    Image.Width |= *p;
    p += 3;
    Image.Height = *p;
    p--;
    Image.Height <<= 8;
    Image.Height |= *p;
    p += 2;
    for(j = 0; j < Image.Height; j++)
    {
        for(i = 0; i < Image.Width; i++)
        {
#ifdef BITMAP_CODING1
            if(*p & (0x01 << (i % 8)))
#endif
#ifdef BITMAP_CODING2
           if(*p & (0x80 >> (i % 8)))
#endif
            {
                Oled_Pixel(x + i, y + j, pixel_1);
            } else
            {
                Oled_Pixel(x + i, y + j, pixel_0);
            }
            if((i % 8) == 7 && i < Image.Width - 1)
            {
                p++;
            }
        }
        p++;
    }
    Display.WrRam = 1;
#ifndef DISPLAY_INTERRUPT
    Oled_WriteArea(x, y, x + Image.Width, y + Image.Height);
#endif
}

//==============================================================================
// This function fills the screen.
// How can I clear the screen?
// Example:
// Oled_FillScreen(0x00);
//==============================================================================
void Oled_FillScreen(U8 pattern) {
    U16 k;
    Display.WrRam = 0;
    for(k = 0; k < DISPLAY_RAM; k++)
    {
        Display.Ram[k] = pattern;
    }
    Display.WrRam = 1;
#ifndef DISPLAY_INTERRUPT
    Oled_WriteArea(0, 0, Display.X + 1, Display.Y + 1);
#endif
}

//==============================================================================
// This function can be used for drawing a dot, pixel or a box.
// I need to graph an equation. How can I write a single pixel at x = 10, y = 30?.
// Example:
// Oled_FillArea(10, 30, 10, 30, PIXEL_1);
//==============================================================================
void Oled_FillArea(U16 x1, U16 y1, U16 x2, U16 y2, U8 pixel_) {
    U16 i, j;
    if(Display.WrRam == 1)
    {
        Display.WrRam = 2;
    }
    for(i = x1; i <= x2; i++)
    {
        for (j = y1; j <= y2; j++)
        {
            Oled_Pixel(i, j, pixel_);
        }
    }
    if(Display.WrRam == 2)
    {
#ifndef DISPLAY_INTERRUPT
        Oled_WriteArea(x1, y1, x2, y2);
#endif
        Display.WrRam = 1;
    }
}

//==============================================================================
// Line, rectangle and circle functions.
// What about of line, rectangle and circle?.
// Examples:
//
// Draws a line from x1  = 5, y1 = 8 to x2 = 60, y2 = 22.
// Oled_Line(5, 81, 60, 22, PIXEL_1);
//
// Draws a rectangle from x1 = 12, y1 = 2 to x1 = 80, y2 = 14.
// Oled_Rectangle(12, 2, 80, 14, PIXEL_1);
//
// Draw a circle at x = 30, y = 30 with a of radius = 10.
// Oled_Circle(30, 30, 10, PIXEL_1);
//==============================================================================
void Oled_Line(U16 x1, U16 y1, U16 x2, U16 y2, U8 pixel_) {
    S16 dx = abs(x2 - x1), sx = x1 < x2 ? 1 : -1;
    S16 dy = abs(y2 - y1), sy = y1 < y2 ? 1 : -1;
    S16 err = (dx > dy ? dx : -dy) / 2, e2;
    for(;;) {
        Oled_FillArea(x1, y1, x1, y1, pixel_);
        if (x1 == x2 && y1 == y2) break;
        e2 = err;
        if(e2 >-dx)
        {
            err -= dy;
            x1 += sx;
        }
        if(e2 < dy)
        {
            err += dx;
            y1 += sy;
        }
    }
}

void Oled_Rectangle(U16 x1, U16 y1, U16 x2, U16 y2, U8 pixel_) {
    Oled_Line(x1, y1, x2, y1, pixel_);
    Oled_Line(x1, y2, x2, y2, pixel_);
    Oled_Line(x1, y1, x1, y2, pixel_);
    Oled_Line(x2, y1, x2, y2, pixel_);
}

void Oled_Circle(U16 x1, U16 y1, U16 radius, U8 pixel_) {
    S16 x = radius, y = 0;
    S16 radiusError = 1 - x;
    while(x >= y)
    {
        Oled_FillArea(x + x1, y + y1, x + x1, y + y1, pixel_);
        Oled_FillArea(y + x1, x + y1, y + x1, x + y1, pixel_);
        Oled_FillArea(-x + x1, y + y1, -x + x1, y + y1, pixel_);
        Oled_FillArea(-y + x1, x + y1, -y + x1, x + y1, pixel_);
        Oled_FillArea(-x + x1, -y + y1, -x + x1, -y + y1, pixel_);
        Oled_FillArea(-y + x1, -x + y1, -y + x1, -x + y1, pixel_);
        Oled_FillArea(x + x1, -y + y1, x + x1, -y + y1, pixel_);
        Oled_FillArea(y + x1, -x + y1, y + x1, -x + y1, pixel_);
        y++;
        if(radiusError<0)
        {
            radiusError += 2 * y + 1;
        } else
        {
            x--;
            radiusError += 2 * (y - x + 1);
        }
    }
}

//==============================================================================
// This function draws a pixel in the ram memory.
//==============================================================================
U8 Oled_Pixel(U16 x, U16 y, U8 pixel_) {
    U16 i;
    if(x > Display.X || y > Display.Y)
    {
        return PIXEL_ERROR;
    }
    switch(Display.FrameMemory)
    {
    case DISPLAY_0:
        break;
    case DISPLAY_90:
        i = x;
        x = Display.Y - y;
        y = i;
        break;
    case DISPLAY_180:
        x = Display.X  - x;
        y = Display.Y - y;
        break;
    case DISPLAY_270:
        i = x;
        x = y;
        y = Display.X  - i;
        break;
    }
    switch(pixel_)
    {
    case PIXEL_0:
        Display.Ram[x + ((y / 8) * DISPLAY_W)] &= ~(1 << (y % 8));
        break;
    case PIXEL_1:
        Display.Ram[x + ((y / 8) * DISPLAY_W)] |=  (1 << (y % 8));
        break;
    case PIXEL_INVERSE:
        Display.Ram[x + ((y / 8) * DISPLAY_W)] ^=  (1 << (y % 8));
        break;
    case PIXEL_RETURN:
        i = Display.Ram[x + ((y / 8) * DISPLAY_W)];
        i >>= y % 8;
        i &= 0x01;
        break;
    }
    return (U8)i;
}

//==============================================================================
// This function writes an area of the ram memory.
//==============================================================================
void Oled_WriteArea(U16 x1, U16 y1, U16 x2, U16 y2) {
    U16 i, j;
    U16 pag1, pag2;
    switch(Display.FrameMemory)
    {
    case DISPLAY_0:
    case DISPLAY_180:
        if(x1 < 0) {
            x1 = 0;
        }
        if(x2 < 0) {
            x2 = 0;
        }
        if(x1 > DISPLAY_W) {
            x1 = DISPLAY_W;
        }
        if(x2 > DISPLAY_W) {
            x2 = DISPLAY_W;
        }
        if(y1 < 0) {
            y1 = 0;
        }
        if(y2 < 0) {
            y2 = 0;
        }
        if(y1 > DISPLAY_H) {
            y1 = DISPLAY_H;
        }
        if(y2 > DISPLAY_H) {
            y2 = DISPLAY_H;
        }
        break;
    case DISPLAY_90:
    case DISPLAY_270:
        if(x1 < 0) {
            x1 = 0;
        }
        if(x2 < 0) {
            x2 = 0;
        }
        if(x1 > DISPLAY_H) {
            x1 = DISPLAY_H;
        }
        if(x2 > DISPLAY_H) {
            x2 = DISPLAY_H;
        }
        if(y1 < 0) {
            y1 = 0;
        }
        if(y2 < 0) {
            y2 = 0;
        }
        if(y1 > DISPLAY_W) {
            y1 = DISPLAY_W;
        }
        if(y2 > DISPLAY_W) {
            y2 = DISPLAY_W;
        }
        break;
    }
    switch(Display.FrameMemory)
    {
    case DISPLAY_0:
        break;
    case DISPLAY_90:
        i = x1;
        j = x2;
        x1 = DISPLAY_W - y2;
        x2 = DISPLAY_W - y1;
        y1 = i;
        y2 = j;
        break;
    case DISPLAY_180:
        i = x1;
        j = y1;
        x1 = DISPLAY_W - x2;
        x2 = DISPLAY_W - i;
        y1 = DISPLAY_H - y2;
        y2 = Display.Y - j;
        break;
    case DISPLAY_270:
        i = x1,
        j = x2;
        x1 = y1;
        x2 = y2;
        y1 = DISPLAY_H - j;
        y2 = DISPLAY_H - i;
        break;
    }
    if(x1 > 0)
    {
        x1--;
    }
    if(x2 < DISPLAY_W)
    {
        x2++;
    } else if(x2 > DISPLAY_W)
    {
        x2 = DISPLAY_W;
    }
    if(y1 >= DISPLAY_H)
    {
        y1 = DISPLAY_H - 1;
    }
    if(y2 >= DISPLAY_H)
    {
        y2 = DISPLAY_H - 1;
    }
    pag1 = y1 / 8;
    pag2 = y2 / 8;
    j = (pag1 * DISPLAY_W) + x1;
    for(i = pag1; i <= pag2; i++)
    {
        Oled_WritePage(&Display.Ram[j], x1, x2, i);
        j += DISPLAY_W;
    }
}

//==============================================================================
// This is an interrupt function.
// This function is called from a timer to do the frames per second.

// The timer must be configured to 1ms.
//==============================================================================
void Oled_INT(void) {
#ifdef DISPLAY_INTERRUPT
    if(Display.WrRam == 1 && Display.Cnt2 >= DISPLAY_DELAY1)
    {
        Oled_WritePage(&Display.Ram[Display.Cnt1], 0, DISPLAY_W, Display.Cnt1 / DISPLAY_W);
        Display.Cnt1 += DISPLAY_W;
        if(Display.Cnt1 == DISPLAY_RAM)
        {
            Display.Cnt1 = 0;
        }
        Display.Cnt2 = 0;
    }
    Display.Cnt2++;
#endif
    if(Oled_InterruptHandler)
    {
        Oled_InterruptHandler();
    }
}

//==============================================================================
// This function set the handler interrupt for the scrolling.
// Consult demo!
//==============================================================================
void Oled_SetInterruptHandler(void (*p)(void)) {
    Oled_InterruptHandler = p;
}

//==============================================================================
// This function resets the display.
// This function can be fixed if the IDE used has a new format.
//==============================================================================
void Oled_Reset(void) {
    OLED_RST0();
    Delay_ms(300);
    OLED_RST1();
    Delay_ms(300);
}

//==============================================================================
// This function writes a command.
// This function can be fixed if you have used a different SPI/I2C bus.
//==============================================================================
void Oled_Command(U8 cmd) {
#ifdef DISPLAY_SPI_INTERFACE
#ifdef STM32CUBE_IDE
    OLED_CS0();
    OLED_DC0();    
    OLED_WRITE_CMD(&cmd);
    OLED_CS1();
#endif
#ifdef MPLABX_IDE
    OLED_CS0();
    OLED_DC0();
    OLED_WRITE_CMD(cmd);
    OLED_CS1();
#endif
#ifdef RASPBERRY_IDE
    
#endif
#endif
#ifdef DISPLAY_I2C_INTERFACE
#ifdef STM32CUBE_IDE
    OLED_WRITE_CMD(&cmd);    
#endif
#ifdef MPLABX_IDE
    OLED_WRITE_CMD(cmd);
#endif
#ifdef RASPBERRY_IDE

#endif
#endif
}

//==============================================================================
// This function writes a page.
// This function can be fixed if you have used a different SPI/I2C bus.
//==============================================================================
void Oled_WritePage(U8 *p, U16 seg1, U16 seg2, U16 pag) {
#ifdef DISPLAY_SPI_INTERFACE
#ifdef STM32CUBE_IDE
    Oled_SetPointer(seg1, pag);
    OLED_CS0();
    OLED_DC1();    
    OLED_WRITE_RAM(p, seg2 - seg1);
    OLED_CS1();
#endif
#ifdef MPLABX_IDE
    U16 i = seg2 - seg1;
    Oled_SetPointer(seg1, pag);
    OLED_CS0();
    OLED_DC1();
    OLED_WRITE_RAM(p, i);
    OLED_CS1();
#endif
#ifdef RASPBERRY_IDE

#endif
#endif
#ifdef DISPLAY_I2C_INTERFACE
#ifdef STM32CUBE_IDE
    Oled_SetPointer(seg1, pag);
    OLED_WRITE_RAM(p, seg2 - seg1);
#endif
#ifdef MPLABX_IDE
    U8 b[DISPLAY_W + 3];
    U16 i;
    Oled_SetPointer(seg1, pag);
    b[0] = 0x40;
    for(i = 1; i <= seg2 - seg1; i++)
    {
        b[i] = *p;
        p++;
    }
    i = (seg2 - seg1) + 1;
    OLED_WRITE_RAM(b, i);
#endif
#ifdef RASPBERRY_IDE

#endif
#endif
}

//==============================================================================
// These functions are default for some drivers like ssd1306.
//==============================================================================
#ifdef DISPLAY_FUNC_DEFAULT
void Oled_SetPointer(U16 seg, U16 pag) {
    Oled_Command(seg & 0x0F);
    Oled_Command((seg >> 4) | 0x10);
    Oled_Command(pag | 0xB0);
}

void Oled_OFF(void) {
    Oled_Command(0xAE);
}

void Oled_ON(void) {
    Oled_Command(0xAF);
}

void Oled_SetContrast(void) {
	Oled_Command(0x81);
	Oled_Command(Display.Contrast);
}
#endif

//==============================================================================
// Drivers: SSD1306, SSD1309 and SH1106.
//==============================================================================
#ifdef DISPLAY_INIT_DEFAULT
void Oled_Driver(void)
{
#ifdef DRIVER_SSD1309_128x64
	Oled_Command(0xFD);		// Command. Set Command Lock.
	Oled_Command(0x12);
#endif
	Oled_Command(0xAE);		// Command. Set Display ON/OFF. Display OFF.
	Oled_Command(0x81);		// Command. Set Contrast Control.
	Oled_Command(0x7F);
	Oled_Command(0xA4);		// Command. Entire Display ON.
	Oled_Command(0xA6);		// Command. Set Normal/Inverse Display.

	Oled_Command(0x20);		// Command. Set Memory Addressing Mode.
	Oled_Command(0x02);
    Oled_Command(0x00);		// Command. Set Lower Column Start Address for Page Addressing Mode.
    Oled_Command(0x10);		// Command. Set Higher Column Start Address for Page Addressing Mode.
    Oled_Command(0xB0);		// Command. Set Page Start Address for Page Addressing Mode.

    Oled_Command(0x40);		// Command. Set Display Start Line.
    Oled_Command(0xA1);		// Command. Set Segment Re-map.
	Oled_Command(0xA8);		// Command. Set Multiplex Ratio.
	Oled_Command(DISPLAY_H - 1);
	Oled_Command(0xC8);		// Command. Set COM Output Scan Direction.
	Oled_Command(0xD3);		// Command. Set Display Offset.
	Oled_Command(0x00);
	Oled_Command(0xDA);		// Command. Set COM Pins Hardware Configuration.
	Oled_Command(0x12);
#ifdef DRIVER_SSD1306_96x16
	Oled_Command(0xDA);		// Command. Set COM Pins Hardware Configuration.
	Oled_Command(0x02);
#endif
#ifdef DRIVER_SSD1306_128x32
	Oled_Command(0xDA);		// Command. Set COM Pins Hardware Configuration.
	Oled_Command(0x02);
#endif

	Oled_Command(0xD5);		// Command. Set Display Clock Divide
	Oled_Command(0xA0);
	Oled_Command(0xD9);		// Command. Set Pre-charge Period
	Oled_Command(0x25);
	Oled_Command(0xDB);		// Command. Set VCOMH Deselect Level.
	Oled_Command(0x34);
#ifndef DRIVER_SSD1309_128x64
    Oled_Command(0x8D);		// Charge Pump Setting
    Oled_Command(0x14);
#endif

    Oled_Command(0xAF);		// Command. Set Display ON/OFF. Display ON.
}
#endif

//==============================================================================
// Driver: SH1107.
//==============================================================================
#ifdef DRIVER_SH1107_64x128
void Oled_Driver(void) {
	Oled_Command(0xAE);		// Command. Display OFF/ON. OFF.
	Oled_Command(0x00);		// Command. Set Column Address 4 lower bits.
	Oled_Command(0x10);		// Command. Set Column Address 4 higher bits.
	Oled_Command(0xB0);		// Command. Set Page Address.
	Oled_Command(0xD5);		// Command. Set Display Divide Ratio/Oscillator Frequency Mode.
	Oled_Command(0x51);
	Oled_Command(0x20);		// Command. Set Memory Addressing Mode.
	Oled_Command(0x81);		// Command. Set Contrast Control.
	Oled_Command(0x7F);
	Oled_Command(0xA0);		// Command. Set Segment Re-map (ADC).
	Oled_Command(0xA4);		// Command. Entire Display ON.
	Oled_Command(0xA6);		// Command. Set Normal/Reverse Display.
	Oled_Command(0xA8);		// Command. Set Multiplex Ratio.
	Oled_Command(0x3F);
	Oled_Command(0xDC);		// Command. Set Display Start Line.
	Oled_Command(0x00);
	Oled_Command(0xD3);		// Command. Set display offset.
	Oled_Command(0x60);
	Oled_Command(0xAD);		// Command. DC-DC Control Mode Set.
	Oled_Command(0x80);
	Oled_Command(0xC0);		// Command. Set Common Output Scan Direction.
	Oled_Command(0xD9);		// Command. Dis-charge / Pre-charge Period Mode.
	Oled_Command(0x22);
	Oled_Command(0xDB);		// Command. Set Vcomh voltage
	Oled_Command(0x35);
	Oled_Command(0xAD);		// Command. DC-DC Control Mode Set.
	Oled_Command(0x8A);
	Oled_Command(0xAF);		// Command. Display OFF/ON. ON.
}
#endif

//==============================================================================
// Driver: UC1609C.
//==============================================================================
#ifdef DRIVER_UC1609C_192x64
void Oled_Driver(void) {
	Oled_Command(0xA0);		// Command. Set Frame Rate.
	Oled_Command(0xEB);		// Command. Set LCD Bias Ratio.
	Oled_Command(0x2F);		// Command. Set Power Control.
	Oled_Command(0xC4);		// Command. Set LCD Mapping Control.
	Oled_Command(0x81);		// Command. Set VBIAS Potentiometer.
	Oled_Command(0xB4);		// Contrast.
	Oled_Command(0xAF);		// Command. Set Display Enable.
}
#endif

//==============================================================================
// Driver: ST7565R.
//==============================================================================
#ifdef DRIVER_ST7565R_128x64
void Oled_Driver(void) {
	Oled_Command(0xA2);		// Command. LCD Bias Set.
	Oled_Command(0xA0);		// Command. ADC Select.
	Oled_Command(0xC8);		// Command. Common Output Mode Select.
	Oled_Command(0x25);		// Command. Vo. Voltage regulator internal resistor ratio set.
	Oled_Command(0x81);		// Command. electronic volume mode set.
	Oled_Command(0x64);		// Contrast.
	Oled_Command(0x2F);		// Command. Power Control Set.
	Oled_Command(0x40);		// Command. Display Start Line Set.
	Oled_Command(0xA6);		// Command. Display Normal/Reverse.
	Oled_Command(0xA4);		// Command. Display All Points ON/OFF.
	Oled_Command(0xAF);		// Command. Display ON/OFF. Display ON.
}
#endif

//==============================================================================
// Driver: NOKIA5110.
//==============================================================================
#ifdef DRIVER_NOKIA5110_84x48
void Oled_Driver(void) {
	Oled_Command(0x21);		// Select extended instruction set (H = 1 mode)
	Oled_Command(0xBF);     // Set LCD Vop (Contrast)
	Oled_Command(0x04);		// Set Temperature Coefficient
	Oled_Command(0x14);		// Set Bias System (BSx)
	Oled_Command(0x20);		// Select normal instruction set (H = 0 mode)
	Oled_Command(0x0C);		// Display control set normal mode (D = 1 and E = 0)
}

void Oled_SetPointer(U16 seg, U16 pag) {
	Oled_Command(seg | 0x80);
	Oled_Command(pag | 0x40);
}

void Oled_OFF(void) {
	Oled_Command(0x25);
}

void Oled_ON(void) {
	Oled_Driver();
}
void Oled_SetContrast(void) {
	Oled_Command(0x21);
	Oled_Command(Display.Contrast);
	Oled_Command(0x04);
	Oled_Command(0x14);
	Oled_Command(0x20);
	Oled_Command(0x0C);
}
#endif

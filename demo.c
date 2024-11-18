/*
 * File:   demo.c
 * Author: http://pic18fxx.blogspot.com
 * Demos for Microchip XC8.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "demo.h"
#include "oled.h"
//#include "ds3231.h"
#include "font.h"
//#include "bitmap.h"
#include "time_delay.h"

//==============================================================================
// Basic demo!
//==============================================================================
void DispReceive(void) {
    char b[20];
    //int i, j;
    
    SPI1_Open(SPI1_DEFAULT);    // Comment this line if I2C is used.
    Oled_Init(DISPLAY_0);
    
// Do you need work on 90 degrees?
// No problem!
    Oled_SetFont(Terminal11x16, 0);
//    Oled_MemoryAccessControl(DISPLAY_0);
//    Oled_TextCenter("0 Degrees", 0, 0, Display.X, PIXEL_1);
//    Oled_MemoryAccessControl(DISPLAY_180);
//    Oled_TextCenter("180 Degrees", 0, 0, Display.X, PIXEL_1);
//    Oled_MemoryAccessControl(DISPLAY_90);
//    Oled_TextCenter("90 Degrees", 0, 0, Display.X, PIXEL_1);
//    Oled_MemoryAccessControl(DISPLAY_270);
//    Oled_TextCenter("270 Degrees", 0, 0, Display.X, PIXEL_1);
//    Delay_ms(3000);
    
    // Blane addition 
    Oled_MemoryAccessControl(DISPLAY_0);
    Oled_TextCenter("Receiving", 32, 32, Display.X, PIXEL_1);
// Would you like a full image?
// Sure! but with inverse pixel.
//    Oled_MemoryAccessControl(DISPLAY_0);
//    Oled_FillScreen(0x00);
//    Oled_Image(truck_bmp, 0, 0, PIXEL_INVERSE);
//    Delay_ms(3000);

// How can I print an small image like an icon at x = 10, y = 5?.
// I think.
//    Oled_MemoryAccessControl(DISPLAY_0);
//    Oled_FillScreen(0x00);
//    //Oled_Image(IconTools, 10, 5, PIXEL_1);
//    Delay_ms(3000);
    
// What about fonts?
// Done!
//    Oled_MemoryAccessControl(DISPLAY_0);
//    Oled_FillScreen(0x00);
//    Oled_SetFont(Terminal11x16, 1);
//    Oled_TextCenter("Fonts", 0, 0, Display.X, PIXEL_INVERSE);
//    for(i = 0; i < 5; i++)
//    {
//        for(j = 0; j <= 10; j++)
//        {
//            sprintf(b, "%02d:%02d", i, j);
//            Oled_SetFont(Arial_Rounded_MT_Bold27x36, 2);
//            Oled_Text(b, 0, 25);
//            Delay_ms(200);
//        }
//    }
//    Delay_ms(3000);
//
//    Oled_MemoryAccessControl(DISPLAY_90);
//    Oled_FillScreen(0x00);
//    Oled_SetFont(Terminal11x16, 1);
//    Oled_TextCenter("Fonts", 0, 0, Display.X, PIXEL_INVERSE);
//    for(i = 0; i < 5; i++)
//    {
//        for(j = 0; j <= 10; j++)
//        {
//            sprintf(b, "%02d", j);
//            Oled_SetFont(Arial_Rounded_MT_Bold27x36, 2);
//            Oled_TextCenter(b, 0, 25, Display.X, PIXEL_1);
//            Oled_SetFont(Terminal11x16, 2);
//            Oled_TextCenter(b, 0, 70, Display.X, PIXEL_1);
//            Oled_SetFont(Terminal6x9, 2);
//            Oled_TextCenter(b, 0, 100, Display.X, PIXEL_1);
//            Delay_ms(200);
//        }
//    }
    //while(1);
}

void DispNothing(void) {
    char b[20];
    //int i, j;
    
    SPI1_Open(SPI1_DEFAULT);    // Comment this line if I2C is used.
    Oled_Init(DISPLAY_0);
    
// Do you need work on 90 degrees?
// No problem!
    Oled_SetFont(Terminal11x16, 0);
//    Oled_MemoryAccessControl(DISPLAY_0);
//    Oled_TextCenter("0 Degrees", 0, 0, Display.X, PIXEL_1);
//    Oled_MemoryAccessControl(DISPLAY_180);
//    Oled_TextCenter("180 Degrees", 0, 0, Display.X, PIXEL_1);
//    Oled_MemoryAccessControl(DISPLAY_90);
//    Oled_TextCenter("90 Degrees", 0, 0, Display.X, PIXEL_1);
//    Oled_MemoryAccessControl(DISPLAY_270);
//    Oled_TextCenter("270 Degrees", 0, 0, Display.X, PIXEL_1);
//    Delay_ms(3000);
    
    // Blane addition 
    Oled_MemoryAccessControl(DISPLAY_0);
    Oled_TextCenter("", 32, 32, Display.X, PIXEL_1);
// Would you like a full image?
// Sure! but with inverse pixel.
//    Oled_MemoryAccessControl(DISPLAY_0);
//    Oled_FillScreen(0x00);
//    Oled_Image(truck_bmp, 0, 0, PIXEL_INVERSE);
//    Delay_ms(3000);

// How can I print an small image like an icon at x = 10, y = 5?.
// I think.
//    Oled_MemoryAccessControl(DISPLAY_0);
//    Oled_FillScreen(0x00);
//    //Oled_Image(IconTools, 10, 5, PIXEL_1);
//    Delay_ms(3000);
    
// What about fonts?
// Done!
//    Oled_MemoryAccessControl(DISPLAY_0);
//    Oled_FillScreen(0x00);
//    Oled_SetFont(Terminal11x16, 1);
//    Oled_TextCenter("Fonts", 0, 0, Display.X, PIXEL_INVERSE);
//    for(i = 0; i < 5; i++)
//    {
//        for(j = 0; j <= 10; j++)
//        {
//            sprintf(b, "%02d:%02d", i, j);
//            Oled_SetFont(Arial_Rounded_MT_Bold27x36, 2);
//            Oled_Text(b, 0, 25);
//            Delay_ms(200);
//        }
//    }
//    Delay_ms(3000);
//
//    Oled_MemoryAccessControl(DISPLAY_90);
//    Oled_FillScreen(0x00);
//    Oled_SetFont(Terminal11x16, 1);
//    Oled_TextCenter("Fonts", 0, 0, Display.X, PIXEL_INVERSE);
//    for(i = 0; i < 5; i++)
//    {
//        for(j = 0; j <= 10; j++)
//        {
//            sprintf(b, "%02d", j);
//            Oled_SetFont(Arial_Rounded_MT_Bold27x36, 2);
//            Oled_TextCenter(b, 0, 25, Display.X, PIXEL_1);
//            Oled_SetFont(Terminal11x16, 2);
//            Oled_TextCenter(b, 0, 70, Display.X, PIXEL_1);
//            Oled_SetFont(Terminal6x9, 2);
//            Oled_TextCenter(b, 0, 100, Display.X, PIXEL_1);
//            Delay_ms(200);
//        }
//    }
    //while(1);
}

void DispTransmitting(void) {
    char b[20];
    //int i, j;
    
    SPI1_Open(SPI1_DEFAULT);    // Comment this line if I2C is used.
    Oled_Init(DISPLAY_0);
    
// Do you need work on 90 degrees?
// No problem!
    Oled_SetFont(Terminal11x16, 0);
//    Oled_MemoryAccessControl(DISPLAY_0);
//    Oled_TextCenter("0 Degrees", 0, 0, Display.X, PIXEL_1);
//    Oled_MemoryAccessControl(DISPLAY_180);
//    Oled_TextCenter("180 Degrees", 0, 0, Display.X, PIXEL_1);
//    Oled_MemoryAccessControl(DISPLAY_90);
//    Oled_TextCenter("90 Degrees", 0, 0, Display.X, PIXEL_1);
//    Oled_MemoryAccessControl(DISPLAY_270);
//    Oled_TextCenter("270 Degrees", 0, 0, Display.X, PIXEL_1);
//    Delay_ms(3000);
    
    // Blane addition 
    Oled_MemoryAccessControl(DISPLAY_0);
    Oled_TextCenter("Send", 32, 32, Display.X, PIXEL_1);
// Would you like a full image?
// Sure! but with inverse pixel.
//    Oled_MemoryAccessControl(DISPLAY_0);
//    Oled_FillScreen(0x00);
//    Oled_Image(truck_bmp, 0, 0, PIXEL_INVERSE);
//    Delay_ms(3000);

// How can I print an small image like an icon at x = 10, y = 5?.
// I think.
//    Oled_MemoryAccessControl(DISPLAY_0);
//    Oled_FillScreen(0x00);
//    //Oled_Image(IconTools, 10, 5, PIXEL_1);
//    Delay_ms(3000);
    
// What about fonts?
// Done!
//    Oled_MemoryAccessControl(DISPLAY_0);
//    Oled_FillScreen(0x00);
//    Oled_SetFont(Terminal11x16, 1);
//    Oled_TextCenter("Fonts", 0, 0, Display.X, PIXEL_INVERSE);
//    for(i = 0; i < 5; i++)
//    {
//        for(j = 0; j <= 10; j++)
//        {
//            sprintf(b, "%02d:%02d", i, j);
//            Oled_SetFont(Arial_Rounded_MT_Bold27x36, 2);
//            Oled_Text(b, 0, 25);
//            Delay_ms(200);
//        }
//    }
//    Delay_ms(3000);
//
//    Oled_MemoryAccessControl(DISPLAY_90);
//    Oled_FillScreen(0x00);
//    Oled_SetFont(Terminal11x16, 1);
//    Oled_TextCenter("Fonts", 0, 0, Display.X, PIXEL_INVERSE);
//    for(i = 0; i < 5; i++)
//    {
//        for(j = 0; j <= 10; j++)
//        {
//            sprintf(b, "%02d", j);
//            Oled_SetFont(Arial_Rounded_MT_Bold27x36, 2);
//            Oled_TextCenter(b, 0, 25, Display.X, PIXEL_1);
//            Oled_SetFont(Terminal11x16, 2);
//            Oled_TextCenter(b, 0, 70, Display.X, PIXEL_1);
//            Oled_SetFont(Terminal6x9, 2);
//            Oled_TextCenter(b, 0, 100, Display.X, PIXEL_1);
//            Delay_ms(200);
//        }
//    }
    //while(1);
}

void DispReady(void) {
    char b[20];
    //int i, j;
    
    SPI1_Open(SPI1_DEFAULT);    // Comment this line if I2C is used.
    Oled_Init(DISPLAY_0);
    
// Do you need work on 90 degrees?
// No problem!
    Oled_SetFont(Terminal11x16, 0);
//    Oled_MemoryAccessControl(DISPLAY_0);
//    Oled_TextCenter("0 Degrees", 0, 0, Display.X, PIXEL_1);
//    Oled_MemoryAccessControl(DISPLAY_180);
//    Oled_TextCenter("180 Degrees", 0, 0, Display.X, PIXEL_1);
//    Oled_MemoryAccessControl(DISPLAY_90);
//    Oled_TextCenter("90 Degrees", 0, 0, Display.X, PIXEL_1);
//    Oled_MemoryAccessControl(DISPLAY_270);
//    Oled_TextCenter("270 Degrees", 0, 0, Display.X, PIXEL_1);
//    Delay_ms(3000);
    
    // Blane addition 
    Oled_MemoryAccessControl(DISPLAY_0);
    Oled_TextCenter("Ready", 32, 32, Display.X, PIXEL_1);
// Would you like a full image?
// Sure! but with inverse pixel.
//    Oled_MemoryAccessControl(DISPLAY_0);
//    Oled_FillScreen(0x00);
//    Oled_Image(truck_bmp, 0, 0, PIXEL_INVERSE);
//    Delay_ms(3000);

// How can I print an small image like an icon at x = 10, y = 5?.
// I think.
//    Oled_MemoryAccessControl(DISPLAY_0);
//    Oled_FillScreen(0x00);
//    //Oled_Image(IconTools, 10, 5, PIXEL_1);
//    Delay_ms(3000);
    
// What about fonts?
// Done!
//    Oled_MemoryAccessControl(DISPLAY_0);
//    Oled_FillScreen(0x00);
//    Oled_SetFont(Terminal11x16, 1);
//    Oled_TextCenter("Fonts", 0, 0, Display.X, PIXEL_INVERSE);
//    for(i = 0; i < 5; i++)
//    {
//        for(j = 0; j <= 10; j++)
//        {
//            sprintf(b, "%02d:%02d", i, j);
//            Oled_SetFont(Arial_Rounded_MT_Bold27x36, 2);
//            Oled_Text(b, 0, 25);
//            Delay_ms(200);
//        }
//    }
//    Delay_ms(3000);
//
//    Oled_MemoryAccessControl(DISPLAY_90);
//    Oled_FillScreen(0x00);
//    Oled_SetFont(Terminal11x16, 1);
//    Oled_TextCenter("Fonts", 0, 0, Display.X, PIXEL_INVERSE);
//    for(i = 0; i < 5; i++)
//    {
//        for(j = 0; j <= 10; j++)
//        {
//            sprintf(b, "%02d", j);
//            Oled_SetFont(Arial_Rounded_MT_Bold27x36, 2);
//            Oled_TextCenter(b, 0, 25, Display.X, PIXEL_1);
//            Oled_SetFont(Terminal11x16, 2);
//            Oled_TextCenter(b, 0, 70, Display.X, PIXEL_1);
//            Oled_SetFont(Terminal6x9, 2);
//            Oled_TextCenter(b, 0, 100, Display.X, PIXEL_1);
//            Delay_ms(200);
//        }
//    }
    //while(1);
}

/*
 * File:   time_delay.h
 * Author: http://pic18fxx.blogspot.com
 */
#ifndef TIME_DELAY_H
#define TIME_DELAY_H
//==============================================================================
// Includes.
//==============================================================================
#include <stdint.h>
#include "ide.h"

#ifdef STM32CUBE_IDE
#include "main.h"
#endif
#ifdef MPLABX_IDE
#include <xc.h>
#define _XTAL_FREQ 64000000 // Select your XTAL
#endif
#ifdef RASPBERRY_IDE
#endif

//==============================================================================
// Defines, struct and functions.
// This section of code must not be changed.
//==============================================================================
#define TIMERMS_0				0

typedef struct{
	volatile uint16_t Cnt;
}STRUCT_TIMER;
extern STRUCT_TIMER TimerMs1;

void Delay_ms(uint16_t count_);
void TimerMs_Set(STRUCT_TIMER *p, uint16_t count_);
uint16_t TimerMs_Count(STRUCT_TIMER *p);
void TimerMs_INT(void);
#endif /* TIME_DELAY_H */

/*
 * File:   time_delay.c
 * Author: http://pic18fxx.blogspot.com
 */
#include "time_delay.h"

//==============================================================================
// Structure for the delay.
//==============================================================================
STRUCT_TIMER TimerMs1;

//==============================================================================
// This function does a simple delay.
// Examples:
// Your code!.
// Delay_ms(1200);
// Your code!
//==============================================================================
void Delay_ms(uint16_t count_) {
#ifdef STM32CUBE_IDE
    HAL_Delay(count_);
#endif
#ifdef MPLABX_IDE
    unsigned int i;
    for(i = 0; i < count_; i++) {
        __delay_ms(1);
    }
#endif
#ifdef RASPBERRY_IDE
#endif
}

//==============================================================================
// This function sets a timer.
// Example:
// TimerMs_Set(&TimerMs1, 1000);
// while(1)
// {
//	 if(TimerMs_Flag(&TimerMs1) == 0)
//	 {
//		 // Your code here!
//	 }
// }
//==============================================================================
void TimerMs_Set(STRUCT_TIMER *p, uint16_t count_) {
	p->Cnt = count_;
}

//==============================================================================
// This function returns the status of timer.
//==============================================================================
uint16_t TimerMs_Count(STRUCT_TIMER *p) {
    return p->Cnt;
}

//==============================================================================
// This is an interrupt function.
// This function is called from a timer.

// The timer must be configured to 1ms.
//==============================================================================
void TimerMs_INT(void) {
    if(TimerMs1.Cnt > 0)
    {
    	TimerMs1.Cnt--;
    }
}

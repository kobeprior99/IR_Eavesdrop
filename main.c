#include "mcc_generated_files/mcc.h"
// disable warnings
#pragma warning disable 373
#pragma warning disable 520
#pragma warning disable 751
#pragma warning disable 1498
// define statements
#define LED_ON 30
#define LED_OFF 0

// function prototypes
void myTMR1ISR(void);
//array that we will store samples in 
uint8_t recieve_array[256];
//----------------------------------------------
// Main "function"
//----------------------------------------------
void main(void)
{
    //high i'm blanke
   uint8_t i;
   // initialize system
   SYSTEM_Initialize();
   EPWM2_LoadDutyValue(LED_OFF);


   PIE1bits.TMR1IE = 0;
   TMR1_SetInterruptHandler(myTMR1ISR);
   PIE1bits.TMR1IE = 1;


   // allows interrupts to work:
   INTERRUPT_PeripheralInterruptEnable();
   INTERRUPT_GlobalInterruptEnable();


   for (;;)
   {
       
   } // end while
} // end main

// for FSM
typedef enum
{
   TX_IDLE,
   TX_DATA_BITS,
   TX_STOP_BITS,
   TX_START_BITS
} tmr1ISRstate_t;

//----------------------------------------------
// My TMR1 ISR to send outgoing characters through IR transmitter
// Format of the message
// SRC DST MSG CHECKSUM NULL
//----------------------------------------------
void myTMR1ISR(void)
{

   static uint8_t transmitBufferIndex = 0;
   static tmr1ISRstate_t tmr1ISRstate = TX_IDLE;
   static uint8_t tx_checksum = false;
   static uint8_t mask;
   static char letter;

   switch (tmr1ISRstate)
   {
   case TX_IDLE:
       if (transmitStart == true)
       {
           transmitStart = false;        // turn the flag to false
           tmr1ISRstate = TX_START_BITS; // change the state to the next state
           transmitBufferIndex = 0;      // clear your index to make it ready
       }
       else
       {
           EPWM2_LoadDutyValue(LED_OFF); // LED_OFF so EUSART2 Rx receives 1 when it's IDLE
       }
       break;

   // Single bit period to assert the start bit
   case TX_START_BITS:
       letter = transmitIRBuffer[transmitBufferIndex];
       EPWM2_LoadDutyValue(LED_ON); // When LED is on Decoder outputs 0 as the start bit for EUSART
       mask = 0b00000001;           // mask gets initiated
       tmr1ISRstate = TX_DATA_BITS; // move to the next state
       break;

   // Repeat for each of the 8-bits in the letter
   case TX_DATA_BITS:
       if (mask == 0)
       {
           tmr1ISRstate = TX_STOP_BITS; // move to the next state
       }
       else
       {
           // this is the shift, &, extract thing. Refer to the 10 / 7 lecture on my website
           if ((letter & mask) != 0)
               EPWM2_LoadDutyValue(LED_OFF);
           else
               EPWM2_LoadDutyValue(LED_ON);
           mask = mask << 1; // shift mask
       }
       break;

   // One bit period for stop bit
   case TX_STOP_BITS:
       EPWM2_LoadDutyValue(LED_OFF); // Decoder outputs 1, stop bit
       if (transmitIRBuffer[transmitBufferIndex] == '\0')
       {
           // if this already reaches NULL
           tmr1ISRstate = TX_START_BITS; // move to the n state
           tx_checksum = true;           // turn on the tx_checksum flag so next time it enters here it'll take the checksum data in.
       }
       else if (tx_checksum == true)
       {
           tmr1ISRstate = TX_IDLE; // which state would you switch to if tx_checksum is true?
           tx_checksum = false;    // turn off tx_checksum so it only enter here once per message
       }
       else
       {
           tmr1ISRstate = TX_START_BITS; // for normal message characters, which state should you switch to after the stop bit ?
       }
       transmitBufferIndex += 1; // don't forget to increment the index
       break;

   default:
       tmr1ISRstate = TX_IDLE;
       EPWM2_LoadDutyValue(LED_OFF);

   } // end switch

   TMR1_WriteTimer(0x10000 - sample_period);
   PIR1bits.TMR1IF = 0; // clear the TMR1 interrupt flag
} // end Timer ISR



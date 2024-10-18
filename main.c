#include <stdint.h>
#include "mcc_generated_files/mcc.h"
// disable warnings
#pragma warning disable 373
#pragma warning disable 520
#pragma warning disable 751
#pragma warning disable 1498
// define statements
#define IRLED_ON 25
#define IRLED_OFF 0
#define SAMPLE_PERIOD 1666 // sample rate close to 1200 baud for testing
#define NUM_SAMPLES 2048
#define NUM_BYTES 256

// function prototypes
void myTMR1ISR(void);
void setSample(uint16_t index, uint8_t value);
void sendSample(uint8_t recieveBuffer[], uint8_t currentByte, uint8_t currentBit);
// array that we will store samples in
uint8_t recieve_buffer[NUM_BYTES];

// flag to control TMR1 ISR will use 1:1 prescaler
uint8_t capture = false;
// flag to control TMR1 ISR
uint8_t transmit = false;
// flag to make sure we don't overwrite buffer
uint8_t bufferReady = false;

//----------------------------------------------
// Main "function"
//----------------------------------------------
void main(void)
{
    // initialize system
    SYSTEM_Initialize();
    // RC1 is connected to the IR LED CCP2 is the pwm used at this pin
    EPWM2_LoadDutyValue(IRLED_OFF);
    // set up timer1ISR
    PIE1bits.TMR1IE = 0;
    TMR1_SetInterruptHandler(myTMR1ISR);
    PIE1bits.TMR1IE = 1;

    // allows interrupts to work:
    INTERRUPT_PeripheralInterruptEnable();
    INTERRUPT_GlobalInterruptEnable();
    // infinite loop
    for (;;)
    {
        // check if holding capture button
        if (CAPTURE_BUTTON_GetValue() == 0)
        {
            // button is being pressed
            if (bufferReady == false)
            {
                capture = true;
            }
        }
        else
        {
            capture = false;
        }

        // check if pressed transmit button has been pressed
        if (TRANSMIT_BUTTON_GetValue() == 0)
        {
            transmit = true;
        }
        else
        {
            transmit = false;
        }
    } // end inf loop
} // end main

// for FSM
typedef enum
{
    TX_IDLE,
    TX_SAMPLE,
    TX_DONE_SAMPLING,
    TX_Transmit
} tmr1ISRstate_t;

//----------------------------------------------
// My TMR1 ISR to sample bits and transmit them
// Format of the message
// SRC DST MSG CHECKSUM NULL
//----------------------------------------------
void myTMR1ISR(void)
{
    // keep track of index in recieve buffer
    static tmr1ISRstate_t tmr1ISRstate = TX_IDLE;
    static uint16_t sampleIndex = 0;
    static uint8_t bitIndex = 0;
    static uint8_t byteIndex = 0;

    switch (tmr1ISRstate)
    {
    case TX_IDLE:
        // reset indecies for recieve buffer
        sampleIndex = 0;
        // if in the idle state we want to turn IR LED off
        if (transmit == true)
        {
            tmr1ISRstate = TX_Transmit; // move to the next state
        }
        else if (capture == true)
        {
            tmr1ISRstate = TX_SAMPLE; // switch to sample state
        }
        break;

    case TX_SAMPLE:
        if (!bufferReady)
        { // Ensure the buffer is not ready before sampling
            EPWM2_LoadDutyValue(IRLED_OFF);
            if (capture == false)
            {
                tmr1ISRstate = TX_IDLE;
            }
            else
            {
                if (sampleIndex < NUM_SAMPLES)
                {
                    setSample(sampleIndex++, PORTCbits.RC0);
                }
                else
                {
                    capture = false;
                    tmr1ISRstate = TX_DONE_SAMPLING;
                }
            }
        }
        break;

    case TX_DONE_SAMPLING:
        // TODO: Turn Green LED on to indicate done sampling
        // need another flag to indicate that we don't want to overwrite data in recieve_buffer
        bufferReady = true;
        CAP_LED_SetLow();
        // clear bit and byte indexes for the transmit state
        bitIndex = 0;
        byteIndex = 0;
        // return to idle state
        tmr1ISRstate = TX_IDLE;
        break;

    case TX_Transmit:
        // when we transmitting we can reasonably clear the constraint on writting to the buffer again
        bufferReady = false;
        CAP_LED_SetHigh();
        if (transmit == false)
        {
            // transmit false go to idle state
            tmr1ISRstate = TX_IDLE;
        }
        else
        {
            // transmit
            if (byteIndex < NUM_BYTES)
            {
                if (bitIndex == 8)
                {
                    // reset the bit index
                    // increment the byte
                    bitIndex = 0;
                    byteIndex++;
                }
                sendSample(recieve_buffer, byteIndex, bitIndex);
                // increment the bit index
                bitIndex++;
            }
            else
            {
                // if we get to the last index go ahead and reset
                bitIndex = 0;
                byteIndex = 0;
            }
        }
        break;

    default:
        tmr1ISRstate = TX_IDLE;
        EPWM2_LoadDutyValue(IRLED_OFF);

    } // end switch

    TMR1_WriteTimer(0x10000 - SAMPLE_PERIOD); // each sample will be roughly 833us
    PIR1bits.TMR1IF = 0;                      // clear the TMR1 interrupt flag
} // end Timer ISR

// this code is sick!!

// helper function to set the put the sample into the array
void setSample(uint16_t index, uint8_t value)
{
    uint16_t byteIndex = index >> 3; // find the corresponding byte using bit shifts is faster than division operator (divide by 8)
    uint8_t bitIndex = index & 7;    // index &7 is like index % 8 which is faster for embedded system
    // we create a unique bit mask depending on the the bit index
    if (value == 1)
    {
        recieve_buffer[byteIndex] |= (1 << bitIndex); // set the bit
    }
    else
    {
        recieve_buffer[byteIndex] &= ~(1 << bitIndex); // clear bit
    }
}

// helper function to transmit bit
void sendSample(uint8_t recieveBuffer[], uint8_t currentByte, uint8_t currentBit)
{
    // load PWM based on value of current bit of current byte
    // move the bit of interest to the least significant bit position
    uint8_t bitValue = (recieveBuffer[currentByte] >> currentBit) & 0x01;
    if (bitValue == 1)
    {
        EPWM2_LoadDutyValue(IRLED_OFF); // turn LED OFF sSO DECODER GETS gets output 1
    }
    else
    {
        EPWM2_LoadDutyValue(IRLED_ON); // turn LED ON SO DECODER GETS gets output 0
    }
}
/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC18F25K22
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.36 and above
        MPLAB 	          :  MPLAB X 6.00	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set CAP_LED aliases
#define CAP_LED_TRIS                 TRISAbits.TRISA1
#define CAP_LED_LAT                  LATAbits.LATA1
#define CAP_LED_PORT                 PORTAbits.RA1
#define CAP_LED_ANS                  ANSELAbits.ANSA1
#define CAP_LED_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define CAP_LED_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define CAP_LED_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define CAP_LED_GetValue()           PORTAbits.RA1
#define CAP_LED_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define CAP_LED_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define CAP_LED_SetAnalogMode()      do { ANSELAbits.ANSA1 = 1; } while(0)
#define CAP_LED_SetDigitalMode()     do { ANSELAbits.ANSA1 = 0; } while(0)

// get/set CAPTURE_BUTTON aliases
#define CAPTURE_BUTTON_TRIS                 TRISAbits.TRISA2
#define CAPTURE_BUTTON_LAT                  LATAbits.LATA2
#define CAPTURE_BUTTON_PORT                 PORTAbits.RA2
#define CAPTURE_BUTTON_ANS                  ANSELAbits.ANSA2
#define CAPTURE_BUTTON_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define CAPTURE_BUTTON_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define CAPTURE_BUTTON_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define CAPTURE_BUTTON_GetValue()           PORTAbits.RA2
#define CAPTURE_BUTTON_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define CAPTURE_BUTTON_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define CAPTURE_BUTTON_SetAnalogMode()      do { ANSELAbits.ANSA2 = 1; } while(0)
#define CAPTURE_BUTTON_SetDigitalMode()     do { ANSELAbits.ANSA2 = 0; } while(0)

// get/set TRANSMIT_BUTTON aliases
#define TRANSMIT_BUTTON_TRIS                 TRISAbits.TRISA3
#define TRANSMIT_BUTTON_LAT                  LATAbits.LATA3
#define TRANSMIT_BUTTON_PORT                 PORTAbits.RA3
#define TRANSMIT_BUTTON_ANS                  ANSELAbits.ANSA3
#define TRANSMIT_BUTTON_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define TRANSMIT_BUTTON_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define TRANSMIT_BUTTON_Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define TRANSMIT_BUTTON_GetValue()           PORTAbits.RA3
#define TRANSMIT_BUTTON_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define TRANSMIT_BUTTON_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define TRANSMIT_BUTTON_SetAnalogMode()      do { ANSELAbits.ANSA3 = 1; } while(0)
#define TRANSMIT_BUTTON_SetDigitalMode()     do { ANSELAbits.ANSA3 = 0; } while(0)

// get/set OLED_CS aliases
#define OLED_CS_TRIS                 TRISAbits.TRISA5
#define OLED_CS_LAT                  LATAbits.LATA5
#define OLED_CS_PORT                 PORTAbits.RA5
#define OLED_CS_ANS                  ANSELAbits.ANSA5
#define OLED_CS_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define OLED_CS_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define OLED_CS_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define OLED_CS_GetValue()           PORTAbits.RA5
#define OLED_CS_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define OLED_CS_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define OLED_CS_SetAnalogMode()      do { ANSELAbits.ANSA5 = 1; } while(0)
#define OLED_CS_SetDigitalMode()     do { ANSELAbits.ANSA5 = 0; } while(0)

// get/set OLED_DC aliases
#define OLED_DC_TRIS                 TRISAbits.TRISA6
#define OLED_DC_LAT                  LATAbits.LATA6
#define OLED_DC_PORT                 PORTAbits.RA6
#define OLED_DC_SetHigh()            do { LATAbits.LATA6 = 1; } while(0)
#define OLED_DC_SetLow()             do { LATAbits.LATA6 = 0; } while(0)
#define OLED_DC_Toggle()             do { LATAbits.LATA6 = ~LATAbits.LATA6; } while(0)
#define OLED_DC_GetValue()           PORTAbits.RA6
#define OLED_DC_SetDigitalInput()    do { TRISAbits.TRISA6 = 1; } while(0)
#define OLED_DC_SetDigitalOutput()   do { TRISAbits.TRISA6 = 0; } while(0)

// get/set IO_RC0 aliases
#define IO_RC0_TRIS                 TRISCbits.TRISC0
#define IO_RC0_LAT                  LATCbits.LATC0
#define IO_RC0_PORT                 PORTCbits.RC0
#define IO_RC0_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define IO_RC0_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define IO_RC0_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define IO_RC0_GetValue()           PORTCbits.RC0
#define IO_RC0_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define IO_RC0_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)

// get/set RC1 procedures
#define RC1_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define RC1_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define RC1_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define RC1_GetValue()              PORTCbits.RC1
#define RC1_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define RC1_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)

// get/set OLED_RST aliases
#define OLED_RST_TRIS                 TRISCbits.TRISC2
#define OLED_RST_LAT                  LATCbits.LATC2
#define OLED_RST_PORT                 PORTCbits.RC2
#define OLED_RST_ANS                  ANSELCbits.ANSC2
#define OLED_RST_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define OLED_RST_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define OLED_RST_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define OLED_RST_GetValue()           PORTCbits.RC2
#define OLED_RST_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define OLED_RST_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define OLED_RST_SetAnalogMode()      do { ANSELCbits.ANSC2 = 1; } while(0)
#define OLED_RST_SetDigitalMode()     do { ANSELCbits.ANSC2 = 0; } while(0)

// get/set RC3 procedures
#define RC3_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define RC3_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define RC3_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define RC3_GetValue()              PORTCbits.RC3
#define RC3_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define RC3_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define RC3_SetAnalogMode()         do { ANSELCbits.ANSC3 = 1; } while(0)
#define RC3_SetDigitalMode()        do { ANSELCbits.ANSC3 = 0; } while(0)

// get/set RC4 procedures
#define RC4_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define RC4_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define RC4_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define RC4_GetValue()              PORTCbits.RC4
#define RC4_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define RC4_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define RC4_SetAnalogMode()         do { ANSELCbits.ANSC4 = 1; } while(0)
#define RC4_SetDigitalMode()        do { ANSELCbits.ANSC4 = 0; } while(0)

// get/set RC5 procedures
#define RC5_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define RC5_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define RC5_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define RC5_GetValue()              PORTCbits.RC5
#define RC5_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define RC5_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define RC5_SetAnalogMode()         do { ANSELCbits.ANSC5 = 1; } while(0)
#define RC5_SetDigitalMode()        do { ANSELCbits.ANSC5 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/
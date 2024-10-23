#include <xc.h> 
#include "oled.h" 
 
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Define pin connections
#define OLED_CS     LATD0
#define OLED_DC     LATD1
#define OLED_RST    LATD2
#define BUTTON1_PIN PORTAbits.RA2  // Assume button 1 is connected to RB0
#define BUTTON2_PIN PORTAbits.RA3  // Assume button 2 is connected to RB1

void SPI_Init() {
    // Initialize SPI module to use FOSC/4
    SSPSTAT = 0x00; // Clear the status register
    SSPCON = 0x20;  // Set to Master mode, FOSC/4
}

void OLED_Init() {
    // Reset the OLED display
    OLED_RST = 0;   // Reset low
    __delay_ms(50); // Wait
    OLED_RST = 1;   // Reset high
    __delay_ms(50); // Wait

    // Initialization commands for the SSD1306
    OLED_WriteCommand(0xAE); // Display off
    OLED_WriteCommand(0x20); // Set Memory Addressing Mode
    OLED_WriteCommand(0x00); // Horizontal Addressing Mode
    // Add other initialization commands as needed...
    OLED_WriteCommand(0xAF); // Display on
}

void OLED_WriteCommand(unsigned char command) {
    OLED_CS = 0;            // Select OLED
    OLED_DC = 0;            // Command mode
    SSPBUF = command;       // Send command
    while (!SSPSTATbits.BF); // Wait for transmission to complete
    OLED_CS = 1;            // Deselect OLED
}

void OLED_WriteData(unsigned char data) {
    OLED_CS = 0;            // Select OLED
    OLED_DC = 1;            // Data mode
    SSPBUF = data;          // Send data
    while (!SSPSTATbits.BF); // Wait for transmission to complete
    OLED_CS = 1;            // Deselect OLED
}

void OLED_Clear() {
    for (int i = 0; i < (SCREEN_WIDTH * SCREEN_HEIGHT / 8); i++) {
        OLED_WriteData(0x00); // Clear display memory
    }
}

void DisplayMessage(const char *message) {
    OLED_Clear();            // Clear the display
    // Display the message (assuming a function that handles text display)
     You need to implement a way to convert a string to pixel data
    for (int i = 0; message[i] != '\0'; i++) {
        OLED_WriteData(message[i]); // This needs to handle actual character bitmaps
    }
} 

void main(void) {
// Configure oscillator, ports, etc.
    TRISAbits.TRISA2 = 1; // Set BUTTON1_PIN as input
    TRISAbits.TRISA3 = 1; // Set BUTTON2_PIN as input

    SPI_Init();    // Initialize SPI
    OLED_Init();   // Initialize OLED display

    while (1) {
         Check if button 1 is pressed
        if (BUTTON1_PIN == 0) { // Assuming active low
            DisplayMessage("Sampling...");
        } else {
            DisplayMessage("Ready!");
        }

        // Check if button 2 is pressed
       if (BUTTON2_PIN == 0) { // Assuming active low
            DisplayMessage("Transmitting...");
        }
    } 
}
#ifndef RGB_DISPLAY_H
#define RGB_DISPLAY_H

#include "config.h"

/* Custom board
#define R1_PIN 25
#define G1_PIN 26
#define B1_PIN 27
#define R2_PIN 14
#define G2_PIN 12
#define B2_PIN 13
#define A_PIN 23
#define B_PIN 19
#define C_PIN 5
#define D_PIN 17
#define E_PIN 32 
#define LAT_PIN 4
#define OE_PIN 15
#define CLK_PIN 16
*/

#define R1_PIN 25
#define G1_PIN 26
#define B1_PIN 27
//GND
#define R2_PIN 14
#define G2_PIN 12
#define B2_PIN 13
#define E_PIN 18 
#define A_PIN 23
#define B_PIN 19
#define C_PIN 5
#define D_PIN 17
#define CLK_PIN 16
#define LAT_PIN 4
#define OE_PIN 15
//E' or GND

/*
4 5 
12 13 14 15 16 17 18 19
23 25 26 27

free:
2
21 22 --> I2C
32 33 

TODO: 
JTAG: 15 14 13 12
*/

// #include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>
#include <ESP32-VirtualMatrixPanel-I2S-DMA.h>


#define MATRIX_WIDTH PANEL_WIDTH
#define MATRIX_HEIGHT PANEL_HEIGHT
#define NUM_LEDS PANEL_WIDTH*PANEL_HEIGHT
#define VIRTUAL_MATRIX_CHAIN_TYPE CHAIN_TOP_RIGHT_DOWN
#define PANEL_RES_X 64 // Number of pixels wide of each INDIVIDUAL panel module. 
#define PANEL_RES_Y 32 // Number of pixels tall of each INDIVIDUAL panel module.
#define NUM_ROWS 2 // Number of rows of chained INDIVIDUAL PANELS
#define NUM_COLS 2 // Number of INDIVIDUAL PANELS per ROW
#define PANEL_CHAIN NUM_ROWS*NUM_COLS    // total number of panels chained one to another

// #include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>
// #include <ESP32-VirtualMatrixPanel-I2S-DMA.h>
 

// #define PANEL_RES_X 64 // Number of pixels wide of each INDIVIDUAL panel module. 
//     #define PANEL_RES_Y 32 // Number of pixels tall of each INDIVIDUAL panel module.

//     #define NUM_ROWS 2 // Number of rows of chained INDIVIDUAL PANELS
//     #define NUM_COLS 2 // Number of INDIVIDUAL PANELS per ROW
//     #define PANEL_CHAIN NUM_ROWS*NUM_COLS    // total number of panels chained one to another
//     #define VIRTUAL_MATRIX_CHAIN_TYPE CHAIN_BOTTOM_LEFT_UP 



uint16_t colorWheel(uint8_t pos); 
//void drawText(int colorWheelOffset);
void display_init();
//void display_drawText();
void logStatusMessage(const char *message);
void logStatusMessage(String message);
void clearStatusMessage();
void displaySensorData();
void displayLightData(float luxValue);
void displayTest(int delayMs);

#endif

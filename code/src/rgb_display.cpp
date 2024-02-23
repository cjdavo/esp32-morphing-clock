
#include "rgb_display.h"

//#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>
#include <ESP32-VirtualMatrixPanel-I2S-DMA.h>

#include "common.h"

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
// From: https://gist.github.com/davidegironi/3144efdc6d67e5df55438cc3cba613c8
uint16_t colorWheel(uint8_t pos) {
  if(pos < 85) {
    return virtualDisp->color565(pos * 3, 255 - pos * 3, 0);
  } else if(pos < 170) {
    pos -= 85;
    return virtualDisp->color565(255 - pos * 3, 0, pos * 3);
  } else {
    pos -= 170;
    return virtualDisp->color565(0, pos * 3, 255 - pos * 3);
  }
}

void display_init() {
  HUB75_I2S_CFG::i2s_pins _pins={R1_PIN, G1_PIN, B1_PIN, R2_PIN, G2_PIN, B2_PIN, A_PIN, B_PIN, C_PIN, D_PIN, E_PIN, LAT_PIN, OE_PIN, CLK_PIN};
  
  HUB75_I2S_CFG mxconfig(
                PANEL_RES_X,   // module width
                PANEL_RES_Y,   // module height
                PANEL_CHAIN    // chain length
  );
  
  
  // HUB75_I2S_CFG mxconfig(
	// 128, // Module width
	// 64, // Module height
	// 1, // chain length
	// _pins // pin mapping
  // );
  // mxconfig.gpio.e = E_PIN;
  mxconfig.driver = HUB75_I2S_CFG::FM6124;
  dma_display = new MatrixPanel_I2S_DMA(mxconfig);
  

	// MUST DO THIS FIRST!
	dma_display->begin(); // Use default values for matrix dimentions and pins supplied within ESP32-HUB75-MatrixPanel-I2S-DMA.h
  //dma_display->setPanelBrightness(110);

  // create VirtualDisplay object based on our newly created dma_display object
  virtualDisp = new VirtualMatrixPanel((*dma_display), NUM_ROWS, NUM_COLS, PANEL_RES_X, PANEL_RES_Y, VIRTUAL_MATRIX_CHAIN_TYPE);
}

void logStatusMessage(const char *message) {
  Serial.println(message);
  // Clear the last line first!
  virtualDisp->fillRect(0, 56, 128, 8, 0);

  virtualDisp->setTextSize(1);     // size 1 == 8 pixels high
  virtualDisp->setTextWrap(false); // Don't wrap at end of line - will do ourselves

  virtualDisp->setCursor(0, 56);   // Write on last line

  virtualDisp->setTextColor(LOG_MESSAGE_COLOR);
  virtualDisp->print(message);

  messageDisplayMillis = millis();
  logMessageActive = true;
}


void logStatusMessage(String message) {
  Serial.println(message);
  // Clear the last line first!
  virtualDisp->fillRect(0, 56, 128, 8, 0);

  virtualDisp->setTextSize(1);     // size 1 == 8 pixels high
  virtualDisp->setTextWrap(false); // Don't wrap at end of line - will do ourselves

  virtualDisp->setCursor(0, 56);   // Write on last line

  virtualDisp->setTextColor(virtualDisp->color444(255,0,0));
  virtualDisp->print(message);

  messageDisplayMillis = millis();
  logMessageActive = true;
}

void clearStatusMessage() {
   virtualDisp->fillRect(0, 56, 128, 8, 0); 
   logMessageActive = false;
}

void displaySensorData() {
  if (sensorDead) {
    virtualDisp->fillRect(SENSOR_DATA_X, SENSOR_DATA_Y, SENSOR_DATA_WIDTH, SENSOR_DATA_HEIGHT, 0);
    virtualDisp->setTextSize(1);     // size 1 == 8 pixels high
    virtualDisp->setTextWrap(false); // Don't wrap at end of line - will do ourselves
    virtualDisp->setTextColor(SENSOR_ERROR_DATA_COLOR);
    
    virtualDisp->setCursor(SENSOR_DATA_X, SENSOR_DATA_Y);   
    virtualDisp->print("No sensor data!");
  }

  if (newSensorData) {
    virtualDisp->fillRect(SENSOR_DATA_X, SENSOR_DATA_Y, SENSOR_DATA_WIDTH, SENSOR_DATA_HEIGHT, 0);
    virtualDisp->setTextSize(1);     // size 1 == 8 pixels high
    virtualDisp->setTextWrap(false); // Don't wrap at end of line - will do ourselves
    virtualDisp->setTextColor(SENSOR_DATA_COLOR);
//    virtualDisp->setFont(&FreeSerifBold12pt7b);

    virtualDisp->setCursor(SENSOR_DATA_X, SENSOR_DATA_Y);   
    virtualDisp->printf("%4.1f C           %3d%%", sensorTemp, sensorHumi);
    
    // Draw the degree symbol manually
    virtualDisp->fillRect(SENSOR_DATA_X + 25, SENSOR_DATA_Y, 2, 2, SENSOR_DATA_COLOR);
    
    newSensorData = false;
  }
}

void displayLightData(float luxValue) {
  virtualDisp->fillRect(LIGHT_DATA_X, LIGHT_DATA_Y, LIGHT_DATA_WIDTH, LIGHT_DATA_HEIGHT, 0);
  
  virtualDisp->setTextSize(1);     // size 1 == 8 pixels high
  virtualDisp->setTextWrap(false); // Don't wrap at end of line - will do ourselves
  virtualDisp->setTextColor(SENSOR_DATA_COLOR);
  //    virtualDisp->setFont(&FreeSerifBold12pt7b);

  virtualDisp->setCursor(LIGHT_DATA_X, LIGHT_DATA_Y);   
  virtualDisp->printf("%4.1f lx", luxValue);
    

}

void displayForecastData() {

}

// Simple R/G/B screen fill, for testing displays
void displayTest(int delayMs) {
  virtualDisp->fillRect(0, 0, MATRIX_WIDTH, MATRIX_HEIGHT, virtualDisp->color565(255, 0, 0));
  delay(delayMs);
  virtualDisp->fillRect(0, 0, MATRIX_WIDTH, MATRIX_HEIGHT, virtualDisp->color565(0, 255, 0));
  delay(delayMs);
  virtualDisp->fillRect(0, 0, MATRIX_WIDTH, MATRIX_HEIGHT, virtualDisp->color565(0, 0, 255));
  delay(delayMs);
  virtualDisp->fillRect(0, 0, MATRIX_WIDTH, MATRIX_HEIGHT, virtualDisp->color565(0, 0, 0));
}
#include "Arduboy2Ext.h"
#include "Enums.h"

Arduboy2Ext::Arduboy2Ext() : Arduboy2Base() { }

uint8_t Arduboy2Ext::justPressedButtons() const {

  return (~previousButtonState & currentButtonState);

}

uint8_t Arduboy2Ext::pressedButtons() const {

  return currentButtonState;

}

void Arduboy2Ext::clearButtonState() {

  currentButtonState = previousButtonState = 0;

}


void Arduboy2Ext::resetFrameCount() {

  frameCount = 0;

}

uint16_t Arduboy2Ext::getFrameCount() const {

  return frameCount;

}

uint8_t Arduboy2Ext::getFrameCount(uint8_t mod) const {

  return frameCount % mod;

}

bool Arduboy2Ext::getFrameCountHalf(uint8_t mod) const {

	return getFrameCount(mod) > (mod / 2);

}

bool Arduboy2Ext::isFrameCount(uint8_t mod) const {

  return (frameCount % mod) == 0;

}

bool Arduboy2Ext::isFrameCount(uint8_t mod, uint8_t val) const {

  return (frameCount % mod) == val;

}


void Arduboy2Ext::displayWithBackground(TimeOfDay timeOfDay) {
  paintScreenWithBackground(sBuffer, timeOfDay);
}


void Arduboy2Ext::paintScreenWithBackground(uint8_t image[], TimeOfDay timeOfDay) {

  uint8_t c;
  int i = 0;

  SPDR = image[i]; // set the first SPI data byte to get things started
  image[i++] = (timeOfDay == TimeOfDay::Night ? 0x00 : 0xFF);  // clear the first image byte

  // the code to iterate the loop and get the next byte from the buffer is
  // executed while the previous byte is being sent out by the SPI controller

  while (i < (HEIGHT * WIDTH) / 8) {
    // get the next byte. It's put in a local variable so it can be sent as
    // as soon as possible after the sending of the previous byte has completed
    c = image[i];
    // clear the byte in the image buffer

    switch (timeOfDay) {

      case TimeOfDay::Day:
        image[i++] = 0xFF;
        break;

      case TimeOfDay::Night:
        image[i++] = 0x00;
        break;

      case TimeOfDay::Mixed:
        if (i < (128*3)) {
          image[i++] = 0xFF;
        }
        else {
          image[i++] = 0x00;
        }
        break;
      
    }

    while (!(SPSR & _BV(SPIF))) { } // wait for the previous byte to be sent

    // put the next byte in the SPI data register. The SPI controller will
    // clock it out while the loop continues and gets the next byte ready
    SPDR = c;

  }
  
  while (!(SPSR & _BV(SPIF))) { } // wait for the last byte to be sent
  
}


/* ----------------------------------------------------------------------------
 *  Draw a horizontal dotted line. 
 */
void Arduboy2Ext::drawHorizontalDottedLine(uint8_t x1, uint8_t x2, uint8_t y, uint8_t colour) {

	uint8_t diff = (x2 - x1);

	for (uint8_t x = 0; x <= diff; x += 2) {

		drawPixel(x1 + x, y, colour);

  }

}


/* ----------------------------------------------------------------------------
 *  Draw a vertical dotted line. 
 */
void Arduboy2Ext::drawVerticalDottedLine(uint8_t y1, uint8_t y2, uint8_t x, uint8_t colour) {

	uint8_t diff = (y2 - y1);

	for (uint8_t y = 0; y <= diff; y += 2) {

		drawPixel(x, y1 + y, colour);

  }
  
}
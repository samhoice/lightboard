#include "Adafruit_WS2801.h"
#include "SPI.h"

// buttons
const uint8_t whiteButtonPin = 8;
const uint8_t yellowButtonPin = 10;
const uint8_t blueButtonPin = 11;
const uint8_t redButtonPin = 12;

// LEDs
const uint8_t dataPin = 2;
const uint8_t clockPin = 3;

// Adafruit Pixel Library
Adafruit_WS2801 field = Adafruit_WS2801(25, dataPin, clockPin);

// colors
const uint32_t WHITE = Color(255, 255, 255);
const uint32_t RED = Color(255, 0, 0);
const uint32_t YELLOW = Color(255, 200, 0);
const uint32_t BLUE = Color(0, 0, 255);
const uint32_t GREEN = Color(0, 255, 0);
const uint32_t ORANGE = Color(255, 64, 0);
const uint32_t PURPLE = Color(255, 0, 255);
const uint32_t OFF = Color(0, 0, 0);

void setup() {
  // buttons
  pinMode(redButtonPin, INPUT);
  pinMode(blueButtonPin, INPUT);
  pinMode(yellowButtonPin, INPUT);
  pinMode(whiteButtonPin, INPUT);
  
  // LEDs
  field.begin();
  field.show();
}

int redState = 0;
int blueState = 0;
int yellowState = 0;
long pushTime = 0;

void loop() {
  uint8_t change = 0;

  if(digitalRead(redButtonPin)) {
    redState = redState ? 0 : 1;
    change = 1;
  }
  if(digitalRead(blueButtonPin)) {
    blueState = blueState ? 0 : 1;
    change = 1;
  }
  if(digitalRead(yellowButtonPin)) {
    yellowState = yellowState ? 0 : 1;
    change = 1;
  }
  if(digitalRead(whiteButtonPin)) {
    if(redState && blueState && yellowState) {
      redState = blueState = yellowState = 0;
      change = 1;
    }
    else {
      redState = 1;
      blueState = 1;
      yellowState = 1;
      change = 1;
    }
  }
  
  if(change) {
    if(redState && blueState && yellowState) {
      setAll(WHITE);
    } else if(redState && blueState) {
      setAll(PURPLE);
    } else if(redState && yellowState) {
      setAll(ORANGE);
    } else if(blueState && yellowState) {
      setAll(GREEN);
    } else if(redState) {
      setAll(RED);
    } else if(yellowState) {
      setAll(YELLOW);
    } else if(blueState) {
      setAll(BLUE);
    } else {
      setAll(OFF);      
    }
    delay(250);
  }
}

void setAll(uint32_t c) {
  for(int i=0; i < field.numPixels(); ++i) {
    field.setPixelColor(i, c);
  }
  field.show();
}

// Create a 24 bit color value from R,G,B
uint32_t Color(byte r, byte g, byte b)
{
  uint32_t c;
  c = r;
  c <<= 8;
  c |= g;
  c <<= 8;
  c |= b;
  return c;
}


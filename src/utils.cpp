#include "Adafruit_WS2801.h"
#include "SPI.h"

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


void setAll(Adafruit_WS2801 field, uint32_t c) {
    for(int i=0; i < field.numPixels(); ++i) {
        field.setPixelColor(i, c);
    }
    field.show();
}
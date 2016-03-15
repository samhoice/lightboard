#include "Adafruit_WS2801.h"
#include "draw.h"

void setAll(Adafruit_WS2801 field, uint32_t c) {
    for(uint32_t i=0; i < field.numPixels(); ++i) {
        field.setPixelColor(i, c);
    }
    field.show();
}
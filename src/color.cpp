#include "SPI.h"

#include "color.h"


Color::Color(int r, int g, int b, float scale) {
	this->red = r;
	this->green = g;
	this->blue = b;
	this->scale = scale;

	this->c = this->calcRep();
}

uint32_t Color::calcRep() {
    uint32_t c = 0;
    c = uint32_t(this->red * this->scale);
    c <<= 8;
    c |= uint32_t(this->green * this->scale);
    c <<= 8;
    c |= uint32_t(this->blue * this->scale);
    
    this->c = c;
    return c;
}

uint32_t Color::getRep() {
	return this->c;
}
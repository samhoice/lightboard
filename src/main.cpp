#include "Adafruit_WS2801.h"
#include "SPI.h"

#include "utils.h"
#include "color.h"

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


float scale = 0.2;

Color WHITE = Color(255, 255, 255, scale);
Color RED = Color(255, 0, 0, scale);
Color YELLOW = Color(255, 200, 0, scale);
Color BLUE = Color(0, 0, 255, scale);
Color GREEN = Color(0, 255, 0, scale);
Color ORANGE = Color(255, 64, 0, scale);
Color PURPLE = Color(255, 0, 255, scale);
Color OFF = Color(0, 0, 0, 1);


typedef enum {
    WHITE_BUTTON = 1,
    RED_BUTTON = 2,
    YELLOW_BUTTON = 4,
    BLUE_BUTTON = 8
} buttonColors;

typedef enum {
    RELEASE = 0,
    DEBOUNCE = 1,
    PUSH = 2,
    HOLD = 3
} buttonState;

class ButtonStateMachine {
    buttonState stateLastCycle;
    buttonState state;
    long startTime;

    int debounceThreshold = 50;
    int holdThreshold = 3000;

    ButtonStateMachine() {
        this->stateLastCycle = RELEASE;
        this->state = RELEASE;
        this->startTime = 0;
    }
    
    buttonState getState() {
        return this->state;
    }
};

int redState = 0;
int blueState = 0;
int yellowState = 0;
long pushTime = 0;


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
            setAll(field, WHITE.getRep());
        } else if(redState && blueState) {
            setAll(field, PURPLE.getRep());
        } else if(redState && yellowState) {
            setAll(field, ORANGE.getRep());
        } else if(blueState && yellowState) {
            setAll(field, GREEN.getRep());
        } else if(redState) {
            setAll(field, RED.getRep());
        } else if(yellowState) {
            setAll(field, YELLOW.getRep());
        } else if(blueState) {
            setAll(field, BLUE.getRep());
        } else {
            setAll(field, OFF.getRep());
        }
        delay(250);
    }
}

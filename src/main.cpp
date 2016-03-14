#include "Adafruit_WS2801.h"
#include "SPI.h"

#include "utils.h"

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
            setAll(field, WHITE);
        } else if(redState && blueState) {
            setAll(field, PURPLE);
        } else if(redState && yellowState) {
            setAll(field, ORANGE);
        } else if(blueState && yellowState) {
            setAll(field, GREEN);
        } else if(redState) {
            setAll(field, RED);
        } else if(yellowState) {
            setAll(field, YELLOW);
        } else if(blueState) {
            setAll(field, BLUE);
        } else {
            setAll(field, OFF);      
        }
        delay(250);
    }
}

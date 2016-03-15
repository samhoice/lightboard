#include "Adafruit_WS2801.h"
#include "SPI.h"

#include "draw.h"
#include "color.h"
#include "buttonFSM.h"

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
    RED_BUTTON = 1,
    YELLOW_BUTTON = 2,
    BLUE_BUTTON = 4,
    WHITE_BUTTON = 7
} buttonColors;

typedef enum {
    RED_LED = 1,
    YELLOW_LED = 2,
    ORANGE_LED = 3,
    BLUE_LED = 4,
    PURPLE_LED = 5,
    GREEN_LED = 6,
    WHITE_LED = 7
} ledColors;


int pushedButtons = 0;
unsigned long pushTime = 0;
unsigned long pushTimeThreshold = 300;

ButtonStateMachine redButton = ButtonStateMachine();
ButtonStateMachine yellowButton = ButtonStateMachine();
ButtonStateMachine blueButton = ButtonStateMachine();
ButtonStateMachine whiteButton = ButtonStateMachine();

void compareNewButton(buttonColors button) {
    if(millis() - pushTime < pushTimeThreshold) {
        if(!(pushedButtons & button)) {
            pushTime = millis();
        }
        pushedButtons |= button;
    } else {
        // expired
        if(pushedButtons & button) {
            pushedButtons &= (~button & 7);
        } else {
            pushedButtons = button;
            pushTime = millis();
        }
    }
}

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

    // input
    redButton.input(digitalRead(redButtonPin));
    yellowButton.input(digitalRead(yellowButtonPin));
    blueButton.input(digitalRead(blueButtonPin));
    whiteButton.input(digitalRead(whiteButtonPin));

    // output
    if(PUSH == redButton.getState()) {
        compareNewButton(RED_BUTTON);
    }
    if(PUSH == yellowButton.getState()) {
        compareNewButton(YELLOW_BUTTON);
    }
    if(PUSH == blueButton.getState()) {
        compareNewButton(BLUE_BUTTON);
    }
    if(PUSH == whiteButton.getState()) {
        compareNewButton(WHITE_BUTTON);
    }


    switch(pushedButtons) {
        case RED_LED:
        setAll(field, RED.getRep());
        break;
        case YELLOW_LED:
        setAll(field, YELLOW.getRep());
        break;
        case BLUE_LED:
        setAll(field, BLUE.getRep());
        break;
        case GREEN_LED:
        setAll(field, GREEN.getRep());
        break;
        case ORANGE_LED:
        setAll(field, ORANGE.getRep());
        break;
        case PURPLE_LED:
        setAll(field, PURPLE.getRep());
        break;
        case WHITE_LED:
        setAll(field, WHITE.getRep());
        break;
    }


    field.show();
    change = 0;
}

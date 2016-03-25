#include <Arduino.h>
#include "Adafruit_WS2801.h"
#include "SPI.h"

#include "draw.h"
#include "color.h"
#include "buttonFSM.h"
#include "patternFSM.h"

// buttons
const uint8_t whiteButtonPin = 8;
const uint8_t yellowButtonPin = 10;
const uint8_t blueButtonPin = 11;
const uint8_t redButtonPin = 12;

const uint8_t potPin = 2;

// LEDs
const uint8_t dataPin = 2;
const uint8_t clockPin = 3;

// Adafruit Pixel Library
Adafruit_WS2801 field = Adafruit_WS2801(25, dataPin, clockPin);

float scale = 1;
const uint32_t potMin = 10;
const uint32_t potMax = 1000;

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

PatternStateMachine patternMaker = PatternStateMachine();

void setup() {
    // buttons
    pinMode(redButtonPin, INPUT);
    pinMode(blueButtonPin, INPUT);
    pinMode(yellowButtonPin, INPUT);
    pinMode(whiteButtonPin, INPUT);

    // pinMode(potPin, INPUT);
    
    // LEDs
    field.begin();
    field.show();
}

void loop() {
    // input
    redButton.input(digitalRead(redButtonPin));
    yellowButton.input(digitalRead(yellowButtonPin));
    blueButton.input(digitalRead(blueButtonPin));
    whiteButton.input(digitalRead(whiteButtonPin));

    int32_t pot = analogRead(potPin);
    pot = pot < potMin ? potMin : pot;
    pot = pot > potMax ? potMax : pot;
    
    // pot = 500;

    scale = float(pot) / 1000.0;

    Color WHITE = Color(255, 255, 255, scale);
    Color RED = Color(255, 0, 0, scale);
    Color YELLOW = Color(255, 200, 0, scale);
    Color BLUE = Color(0, 0, 255, scale);
    Color GREEN = Color(0, 255, 0, scale);
    Color ORANGE = Color(255, 64, 0, scale);
    Color PURPLE = Color(255, 0, 255, scale);
    Color OFF = Color(0, 0, 0, 1);

    patternMaker.input();
    patternMaker.input(RED_BUTTON, redButton.getState());
    patternMaker.input(YELLOW_BUTTON, yellowButton.getState());
    patternMaker.input(BLUE_BUTTON, blueButton.getState());
    patternMaker.input(WHITE_BUTTON, whiteButton.getState());

    switch(patternMaker.getPushedButtons()) {
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
        default:
        setAll(field, OFF.getRep());
    }
}

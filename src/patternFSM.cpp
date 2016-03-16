#include <Arduino.h>

#include "buttonFSM.h"
#include "patternFSM.h"

PatternStateMachine::PatternStateMachine() {
    this->lastState_Red = RELEASE;
    this->lastState_Blue = RELEASE;
    this->lastState_Yellow = RELEASE;
    this->lastState_White = RELEASE;

    this->pushTime = 0;
    this->patternTime = 0;

    this->pushedButtons = 0;
    this->output = 0;

    // this->pushThreshold = 300;
    // this->patternThreshold = 300;
}

void PatternStateMachine::input() {
    // time only
    if(millis() - this->pushTime > this->pushThreshold) {
        this->output = this->pushedButtons;
    }
}

void PatternStateMachine::input(buttonColors button, buttonState state) {
    // Look for pushes and releases
    switch(button) {
        case RED_BUTTON:
            if(this->lastState_Red != state) {
                if(state == PUSH) {
                    this->handlePush(button);
                } else if(state == RELEASE) {
                    this->handleRelease(button);
                }
                this->lastState_Red = state;
            }
            break;
        case YELLOW_BUTTON:
            if(this->lastState_Yellow != state) {
                if(state == PUSH) {
                    this->handlePush(button);
                } else if(state == RELEASE) {
                    this->handleRelease(button);
                }
                this->lastState_Yellow = state;
            }
            break;
        case BLUE_BUTTON:
            if(this->lastState_Blue != state) {
                if(state == PUSH) {
                    this->handlePush(button);
                } else if(state == RELEASE) {
                    this->handleRelease(button);
                }
                this->lastState_Blue = state;
            }
            break;
        case WHITE_BUTTON:
            if(this->lastState_White != state) {
                if(state == PUSH) {
                    this->handlePush(button);
                } else if(state == RELEASE) {
                    this->handleRelease(button);
                }
                this->lastState_White = state;
            }
            break;
    }
}

void PatternStateMachine::handlePush(buttonColors button) {
    // push for "button"
    if(millis() - this->pushTime < this->pushThreshold) {
        // within the current push event
        this->pushedButtons |= button;
    } else {
        // new push event
        if(this->pushedButtons == button) {
            this->pushedButtons = 0;
        } else {
            this->pushedButtons = button;
        }
    }
    this->pushTime = millis();
}

void PatternStateMachine::handleRelease(buttonColors button) {

}

void PatternStateMachine::patternComplete() {

}

int PatternStateMachine::getPushedButtons() {
    return this->output;
}

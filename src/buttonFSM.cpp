#include <Arduino.h>

#include "buttonFSM.h"

ButtonStateMachine::ButtonStateMachine() {
    this->lastHardwareState = 0;
    this->state = RELEASE;
    this->startTime = 0;
}

void ButtonStateMachine::input(int hardwareState) {
	switch(this->state) {
		case RELEASE:
			if(hardwareState) {
				this->transitionDebounce(RELEASE);
			}
			break;
		case DEBOUNCE:
			if(hardwareState != this->lastHardwareState) {
				// bounce
				this->transitionDebounce(hardwareState);
			}
			if((millis() - this->startTime) > this->debounceThreshold) {
				// stable
				if(hardwareState)
					this->transitionPush();
				else
					this->transitionRelease();
			}
			break;
		case PUSH:
			if(!hardwareState) {
				this->transitionDebounce(hardwareState);
			} else if((millis() - this->startTime) > this->holdThreshold) {
				this->transitionHold();
			}
			break;
		case HOLD:
			if(!hardwareState) {
				this->transitionDebounce(hardwareState);
			}
			break;
	}
}

void ButtonStateMachine::transitionDebounce(int lastHardwareState) {
	this->state = DEBOUNCE;
	this->lastHardwareState = lastHardwareState;
	this->startTime = millis();
}

void ButtonStateMachine::transitionPush() {
	this->state = PUSH;
	this->startTime = millis();
}

void ButtonStateMachine::transitionRelease() {
	this->state = RELEASE;
	this->startTime = millis();
}

void ButtonStateMachine::transitionHold() {
	this->state = HOLD;
	this->startTime = millis();
}

buttonState ButtonStateMachine::getState() {
    return this->state;
}
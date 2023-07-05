#pragma once
#include <Arduino.h>
#include "components/pins.h"
#include "game.h"

#include "components/adkeyboard.h"
#include "components/joystick.h"
#include "components/relays.h"
#include "components/matrix.h"
#include "components/lcd.h"
#include "components/keypad.h"


struct EventHandlerInfo {
    int emergency_button = LOW;

    struct Joystick joy;
};

struct EventHandlerInfo ehi;


void raiseKeypadPressed( const char x ) {
    switch(x) {
        case '1':
            Manager::dispatch( KeypadOnePressed() );
            break;
        case '2':
            Manager::dispatch( KeypadTwoPressed() );
            break;
        case '3':
            Manager::dispatch( KeypadThreePressed() );
            break;
        case '4':
            Manager::dispatch( KeypadFourPressed() );
            break;
        case '5':
            Manager::dispatch( KeypadFivePressed() );
            break;
        case '6':
            Manager::dispatch( KeypadSixPressed() );
            break;
        case '7':
            Manager::dispatch( KeypadSevenPressed() );
            break;
        case '8':
            Manager::dispatch( KeypadEightPressed() );
            break;
        case '9':
            Manager::dispatch( KeypadNinePressed() );
            break;
        case '0':
            Manager::dispatch( KeypadZeroPressed() );
            break;
        default:
            break;

    }
}

void raiseKeypadMatch() {
    Manager::dispatch( KeypadMatched() );
}

void raiseKeypadNoMatch() {
    Manager::dispatch( KeypadNotMatched() );
}

void raiseKeypadCleared() {
    Manager::dispatch( KeypadCleared() );
}

void raiseKeypadOverflowed() {
    Manager::dispatch( KeypadOverflowed() );
}


void setupEventHandler() {
    Manager::start();

    char t[1];
    setSequence(t, 1, raiseKeypadPressed, raiseKeypadMatch, raiseKeypadNoMatch, raiseKeypadCleared, raiseKeypadOverflowed);
}


void checkEvents() {
    /* Emergency button */
    if( ehi.emergency_button != digitalRead(BUTTON_IN) ) {
        ehi.emergency_button = digitalRead(BUTTON_IN);
        if( ehi.emergency_button == HIGH ) {
            Manager::dispatch( EmergencyPressed() );
        }
        else {
            Manager::dispatch( EmergencyReleased() );
        }
    }

    /* Joystick */
    const int tolerance = 6;
    uint16_t x_diff = abs(ehi.joy.x - joystick.x);
    uint16_t y_diff = abs(ehi.joy.y - joystick.y);

    if( x_diff > tolerance || y_diff > tolerance ) {
        ehi.joy.x = joystick.x;
        ehi.joy.y = joystick.y;
        Manager::dispatch( JoystickMoved(joystick.x, joystick.y) );
    }

}
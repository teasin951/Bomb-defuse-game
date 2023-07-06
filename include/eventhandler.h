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
    uint8_t joy_button = RELEASED;

    int16_t pot1 = 4;
    int16_t pot2 = 4;
    int16_t pot3 = 4;

    struct Keyboard key;
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
    int eme_read = digitalRead(BUTTON_IN);
    if( ehi.emergency_button != eme_read ) {
        ehi.emergency_button = eme_read;
        if( ehi.emergency_button == HIGH ) {
            Manager::dispatch( EmergencyPressed() );
        }
        else {
            Manager::dispatch( EmergencyReleased() );
        }
    }

    /* Joystick */
    const int joystick_tolerance = 12;  // Give ingame tolerance of 15
    uint16_t x_diff = abs(ehi.joy.x - joystick.x);
    uint16_t y_diff = abs(ehi.joy.y - joystick.y);

    if( x_diff > joystick_tolerance || y_diff > joystick_tolerance ) {
        ehi.joy.x = joystick.x;
        ehi.joy.y = joystick.y;
        Manager::dispatch( JoystickMoved(joystick.x, joystick.y) );
    }

    int joy_button_read = joystick.button;
    if( ehi.joy_button != joy_button_read ) {
        ehi.joy_button = joy_button_read;
        if( ehi.joy_button == PRESSED ) {
            Manager::dispatch( JoystickPressed() );
        }
        else {
            Manager::dispatch( JoystickReleased() );
        }
    }

    /* Potenciometers */
    const int pot_tolerance = 18;  // Give ingame tolerance of 20

    int16_t pot1_read = analogRead(POTENCIOMETER1);
    uint16_t pot1_diff = abs(ehi.pot1 - pot1_read);

    if( pot1_diff > pot_tolerance ) {
        ehi.pot1 = pot1_read;
        Manager::dispatch( Potenciometer1Moved(pot1_read) );

    }

    int16_t pot2_read = analogRead(POTENCIOMETER2);
    uint16_t pot2_diff = abs(ehi.pot2 - pot2_read);

    if( pot2_diff > pot_tolerance ) {
        ehi.pot2 = pot2_read;
        Manager::dispatch( Potenciometer2Moved(pot2_read) );

    }

    int16_t pot3_read = analogRead(POTENCIOMETER3);
    uint16_t pot3_diff = abs(ehi.pot3 - pot3_read);

    if( pot3_diff > pot_tolerance ) {
        ehi.pot3 = pot3_read;
        Manager::dispatch( Potenciometer3Moved(pot3_read) );

    }

    /* ADKeyboard */
    if(adkeyboard.left != ehi.key.left) {
        ehi.key.left = adkeyboard.left;

        if(ehi.key.left == PRESSED ) {
            Manager::dispatch( ADKeyboardLeftPressed() );
        }
        else {
            Manager::dispatch( ADKeyboardLeftReleased() );
        }
    }

    if(adkeyboard.right != ehi.key.right) {
        ehi.key.right = adkeyboard.right;

        if(ehi.key.right == PRESSED ) {
            Manager::dispatch( ADKeyboardRightPressed() );
        }
        else {
            Manager::dispatch( ADKeyboardRightReleased() );
        }
    }

    if(adkeyboard.up != ehi.key.up) {
        ehi.key.up = adkeyboard.up;

        if(ehi.key.up == PRESSED ) {
            Manager::dispatch( ADKeyboardUpPressed() );
        }
        else {
            Manager::dispatch( ADKeyboardUpReleased() );
        }
    }

    if(adkeyboard.down != ehi.key.down) {
        ehi.key.down = adkeyboard.down;

        if(ehi.key.down == PRESSED ) {
            Manager::dispatch( ADKeyboardDownPressed() );
        }
        else {
            Manager::dispatch( ADKeyboardDownReleased() );
        }
    }

    if(adkeyboard.enter != ehi.key.enter) {
        ehi.key.enter = adkeyboard.enter;

        if(ehi.key.enter == PRESSED ) {
            Manager::dispatch( ADKeyboardEnterPressed() );
        }
        else {
            Manager::dispatch( ADKeyboardEnterReleased() );
        }
    }

    Manager::dispatch( Update() );
}

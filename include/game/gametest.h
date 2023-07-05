#pragma once
#include <Arduino.h>
#include <tinyfsm.hpp>

#include "game/events.h"
#include "components/lcd.h"
#include "components/buzzer.h"

/**
 * @file State machine implementation of game one
*/


class TestGame : public tinyfsm::Fsm<TestGame> {
public:
    /* General update event */
    void react( Update const & ) {};

    /* Keypad */
    void react( KeypadPressed const & ) {};
    void react( KeypadZeroPressed const & ) {};
    void react( KeypadOnePressed const & ) {};
    void react( KeypadTwoPressed const & ) {};
    void react( KeypadThreePressed const & ) {};
    void react( KeypadFourPressed const & ) {};
    void react( KeypadFivePressed const & ) {};
    void react( KeypadSixPressed const & ) {};
    void react( KeypadSevenPressed const & ) {};
    void react( KeypadEightPressed const & ) {};
    void react( KeypadNinePressed const & ) {};

    void react( KeypadMatched const & ) {};
    void react( KeypadNotMatched const & ) {};
    void react( KeypadCleared const & ) {};
    void react( KeypadOverflowed const & ) {};

    /* Emergency button */
    void react( EmergencyPressed const & ) {
        resetDisplay();
        tone(BUZZER_2, 200, 200);
        lcd.print("Emergency press!");
    }
    void react( EmergencyReleased const & ) {
        resetDisplay();
        tone(BUZZER_2, 800, 200);
        lcd.print("Emergency freed!");
    }

    /* Potenciometers */
    void react( Potenciometer1Moved const & ) {};
    void react( Potenciometer2Moved const & ) {};
    void react( Potenciometer3Moved const & ) {};

    /* Joystick */
    void react( JoystickMoved const & e ) {
        resetDisplay();
        tone(BUZZER_1, 50, 10);

        lcd.print("Joystick moved");
        lcd.setCursor(0,1);
        lcd.print("x: ");
        lcd.print(e.x);
        lcd.print(", y: ");
        lcd.print(e.y);
    }
    void react( JoystickPressed const & ) {};
    
    /* ADKeyboard */
    void react( ADKeyboardPressed const & ) {};
    void react( ADKeyboardLeftPressed const & ) {};
    void react( ADKeyboardRightPressed const & ) {};
    void react( ADKeyboardUpPressed const & ) {};
    void react( ADKeyboardDownPressed const & ) {};
    void react( ADKeyboardEnterPressed const & ) {};
    void react( ADKeyboardLeftHeld const & ) {};
    void react( ADKeyboardRightHeld const & ) {};
    void react( ADKeyboardUpHeld const & ) {};
    void react( ADKeyboardDownHeld const & ) {};
    void react( ADKeyboardEnterHeld const & ) {};

    /* Actions on entering/exiting a state */
    void entry() {};
    void exit() {};
};

class UndefinedState : public TestGame {

};

FSM_INITIAL_STATE(TestGame, UndefinedState);

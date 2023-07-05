#pragma once
#include <Arduino.h>
#include <tinyfsm.hpp>

#include "game/events.h"
#include "components/lcd.h"

/**
 * @file State machine implementation of game one
*/


class GameOne : public tinyfsm::Fsm<GameOne> {
public:
    /* General update event */
    virtual void react( Update const & ) {};

    /* Keypad */
    virtual void react( KeypadPressed const & ) {};
    virtual void react( KeypadZeroPressed const & ) {};
    virtual void react( KeypadOnePressed const & ) {};
    virtual void react( KeypadTwoPressed const & ) {};
    virtual void react( KeypadThreePressed const & ) {};
    virtual void react( KeypadFourPressed const & ) {};
    virtual void react( KeypadFivePressed const & ) {};
    virtual void react( KeypadSixPressed const & ) {};
    virtual void react( KeypadSevenPressed const & ) {};
    virtual void react( KeypadEightPressed const & ) {};
    virtual void react( KeypadNinePressed const & ) {};

    virtual void react( KeypadMatched const & ) {};
    virtual void react( KeypadNotMatched const & ) {};
    virtual void react( KeypadCleared const & ) {};
    virtual void react( KeypadOverflowed const & ) {};

    /* Emergency button */
    virtual void react( EmergencyPressed const & ) {}
    virtual void react( EmergencyReleased const & ) {}

    /* Potenciometers */
    virtual void react( Potenciometer1Moved const & ) {};
    virtual void react( Potenciometer2Moved const & ) {};
    virtual void react( Potenciometer3Moved const & ) {};

    /* Joystick */
    virtual void react( JoystickMoved const & ) {};
    virtual void react( JoystickPressed const & ) {};
    
    /* ADKeyboard */
    virtual void react( ADKeyboardPressed const & ) {};
    virtual void react( ADKeyboardLeftPressed const & ) {};
    virtual void react( ADKeyboardRightPressed const & ) {};
    virtual void react( ADKeyboardUpPressed const & ) {};
    virtual void react( ADKeyboardDownPressed const & ) {};
    virtual void react( ADKeyboardEnterPressed const & ) {};
    virtual void react( ADKeyboardLeftHeld const & ) {};
    virtual void react( ADKeyboardRightHeld const & ) {};
    virtual void react( ADKeyboardUpHeld const & ) {};
    virtual void react( ADKeyboardDownHeld const & ) {};
    virtual void react( ADKeyboardEnterHeld const & ) {};

    /* Actions on entering/exiting a state */
    virtual void entry() {};
    virtual void exit() {};
};

class UndefinedState1 : public GameOne {

};

FSM_INITIAL_STATE(GameOne, UndefinedState1);
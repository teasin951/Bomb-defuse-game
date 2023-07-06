#pragma once
#include <Arduino.h>
#include <tinyfsm.hpp>

#include "game/events.h"
#include "game/gameone.h"
#include "game/gametest.h"

#include "components/lcd.h"

/**
 * @file Finite state machines running the game
 */


/**
 * @brief FSM class
*/
class Manager : public tinyfsm::Fsm<Manager> {
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
    virtual void react( EmergencyPressed const & ) {};
    virtual void react( EmergencyReleased const & ) {};

    /* Potenciometers */
    virtual void react( Potenciometer1Moved const & ) {};
    virtual void react( Potenciometer2Moved const & ) {};
    virtual void react( Potenciometer3Moved const & ) {};

    /* Joystick */
    virtual void react( JoystickMoved const & ) {};
    virtual void react( JoystickPressed const & ) {};
    virtual void react( JoystickReleased const & ) {};
    
    /* ADKeyboard */
    virtual void react( ADKeyboardPressed const & ) {};
    virtual void react( ADKeyboardLeftPressed const & ) {};
    virtual void react( ADKeyboardRightPressed const & ) {};
    virtual void react( ADKeyboardUpPressed const & ) {};
    virtual void react( ADKeyboardDownPressed const & ) {};
    virtual void react( ADKeyboardEnterPressed const & ) {};
    virtual void react( ADKeyboardLeftReleased const & ) {};
    virtual void react( ADKeyboardRightReleased const & ) {};
    virtual void react( ADKeyboardUpReleased const & ) {};
    virtual void react( ADKeyboardDownReleased const & ) {};
    virtual void react( ADKeyboardEnterReleased const & ) {};

    virtual void entry() = 0;  // every option has to implement this
    void exit() {};
};


// ------------ Manager states --------------- //

// TODO change this to void react (tinyfsm::Event const & ), with the proper change in Manager

class PickGameTest : public Manager {
    void entry() {
        char tmp[16] = {1};
        setSequence(tmp, 16);
        resetDisplay();
        lcd.print("-- Game test! --");

        TestGame::start();
    }
    /* General update event */
    void react( Update const & e ) override { TestGame::dispatch(e); };

    /* Keypad */
    void react( KeypadPressed const & e ) override { TestGame::dispatch(e); }
    void react( KeypadZeroPressed const & e ) override { TestGame::dispatch(e); };
    void react( KeypadOnePressed const & e ) override { TestGame::dispatch(e); };
    void react( KeypadTwoPressed const & e ) override { TestGame::dispatch(e); };
    void react( KeypadThreePressed const & e ) override { TestGame::dispatch(e); };
    void react( KeypadFourPressed const & e ) override { TestGame::dispatch(e); };
    void react( KeypadFivePressed const & e ) override { TestGame::dispatch(e); };
    void react( KeypadSixPressed const & e ) override { TestGame::dispatch(e); };
    void react( KeypadSevenPressed const & e ) override { TestGame::dispatch(e); };
    void react( KeypadEightPressed const & e ) override { TestGame::dispatch(e); };
    void react( KeypadNinePressed const & e ) override { TestGame::dispatch(e); };

    void react( KeypadMatched const & e ) override { TestGame::dispatch(e); };
    void react( KeypadNotMatched const & e ) override { TestGame::dispatch(e); };
    void react( KeypadCleared const & e ) override { TestGame::dispatch(e); };
    void react( KeypadOverflowed const & e ) override { TestGame::dispatch(e); };

    /* Emergency button */
    void react( EmergencyPressed const & e ) override { TestGame::dispatch(e); };
    void react( EmergencyReleased const & e ) override { TestGame::dispatch(e); };

    /* Potenciometers */
    void react( Potenciometer1Moved const & e ) override { TestGame::dispatch(e); };
    void react( Potenciometer2Moved const & e ) override { TestGame::dispatch(e); };
    void react( Potenciometer3Moved const & e ) override { TestGame::dispatch(e); };

    /* Joystick */
    void react( JoystickMoved const & e ) override { TestGame::dispatch(e); };
    void react( JoystickPressed const & e ) override { TestGame::dispatch(e); };
    void react( JoystickReleased const & e ) override { TestGame::dispatch(e); };
    
    /* ADKeyboard */
    void react( ADKeyboardPressed const & e ) override { TestGame::dispatch(e); };
    void react( ADKeyboardLeftPressed const & e ) override { TestGame::dispatch(e); };
    void react( ADKeyboardRightPressed const & e ) override { TestGame::dispatch(e); };
    void react( ADKeyboardUpPressed const & e ) override { TestGame::dispatch(e); };
    void react( ADKeyboardDownPressed const & e ) override { TestGame::dispatch(e); };
    void react( ADKeyboardEnterPressed const & e ) override { TestGame::dispatch(e); };
    void react( ADKeyboardLeftReleased const & e ) override { TestGame::dispatch(e); };
    void react( ADKeyboardRightReleased const & e ) override { TestGame::dispatch(e); };
    void react( ADKeyboardUpReleased const & e ) override { TestGame::dispatch(e); };
    void react( ADKeyboardDownReleased const & e ) override { TestGame::dispatch(e); };
    void react( ADKeyboardEnterReleased const & e ) override { TestGame::dispatch(e); };
};

/**
 * @brief Choose state
*/
class Choose : public Manager {
    void entry() { 
        resetDisplay();
        lcd.print("Choose game mode");
    }

    void react( KeypadZeroPressed const & ) override {
        tone(BUZZER_1, 400, 50);
        transit<PickGameTest>();
    }

    void react( KeypadOnePressed const & ) override {};
    void react( KeypadTwoPressed const & ) override {};
    void react( KeypadThreePressed const & ) override {};
    void react( KeypadFourPressed const & ) override {};
    void react( KeypadFivePressed const & ) override {};
    void react( KeypadSixPressed const & ) override {};
    void react( KeypadSevenPressed const & ) override {};
    void react( KeypadEightPressed const & ) override {};
    void react( KeypadNinePressed const & ) override {};
};

FSM_INITIAL_STATE(Manager, Choose);

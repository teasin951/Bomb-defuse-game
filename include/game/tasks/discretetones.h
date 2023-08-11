#pragma once
#include <Arduino.h>
#include <tinyfsm.hpp>
#include "../variables.h"
#include "../events.h"
#include "components/pins.h"
#include "components/matrix.h"
#include "components/relays.h"
#include "components/buzzer.h"
#include "components/keypad.h"
#include "components/joystick.h"
#include "components/button.h"


/**
 * @file Discrete Tones implementation
*/

uint8_t discrete_tones_difficulty = 0;  /**< Should be set by GameXXX, 1 allows for numbers past 4 */

/* Forward state declaration */
class InitDiscrete;
class PlayDiscrete;
class MistakeDiscrete;
class CompletedDiscrete;


/**
 * @brief Discrete task FSM
*/
class Discrete : public tinyfsm::Fsm<Discrete> {
public:

    virtual void react( Update const & ) {};

    /* Keypad */
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

    /* ADKeyboard */
    virtual void react( ADKeyboardEnterPressed const & ) {};
    virtual void react( ADKeyboardEnterReleased const & ) {};

    /* Actions on entering/exiting a state */
    virtual void entry() {};
    virtual void exit() {};
};


/**
 * @brief The player is trying to push the button
*/
class PlayDiscrete : public Discrete {
public:
    void entry() override {}

};


/**
 * @brief The player has made a mistake
*/
class MistakeDiscrete : public Discrete {
public:

    void entry() override {
        bomb_beep = false;

        noTone(BUZZER_1);
        tone(BUZZER_1, 200);

        start_millis = millis();
    }

    void exit() {
        noTone(BUZZER_1);
        bomb_beep = true;
    }

    void react( Update const & ) {}

private:
    uint32_t start_millis = 0;
    const uint32_t blink_delay = 500;
};


/**
 * @brief Discrete has been completed
*/
class CompletedDiscrete : public Discrete {
public:
    void entry() {
        task_completed = true;
    }
};


/**
 * @brief Initialize the game
*/
class InitDiscrete : public Discrete {
public:
    void entry() {
        // Set the stage for Discrete
        setRelays(0,1,0,0);
        clearMatrix();
    }

    void react( Update const & ) {
        transit<PlayDiscrete>();
    }
};


FSM_INITIAL_STATE(Discrete, InitDiscrete);

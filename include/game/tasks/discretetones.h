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
#include "components/matrix/loadingcircle.h"


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

    /**
     * @brief Shuffle the array
     * 
     * Uses Knuth algorithm
    */
    void shuffleTones() {
        for( int i = 0; i < 3; i++ ) {
            int j = random(i, 4);

            uint8_t tmp = tones[i];
            tones[i] = tones[j];
            tones[j] = tmp;
        }
    }

    /**
     * @brief Generate displayed number based on difficulty set
    */
    uint8_t genNumber() {
        if( !discrete_tones_difficulty ) {
            return random(1, 5);
        }
        else {
            return random(0, 10);
        }
    }

    void playTones() {
        delay(500);
        for( uint8_t i = 0; i < 4; i++ ) {
            tone(BUZZER_1, 200 * tones[i], 600);
            delay(900);
        }
    }

    /**
     * @brief Check the input against the table A
     * 
     * @param tone Which tone in the sequence to check
     * @param number_pressed User inputed number
    */
    bool checkTableA( uint8_t tone, uint8_t number_pressed ) {
        uint8_t pos = 0;
        switch(number_pressed) {
            case 2:
                pos = 1;
                break;
            case 5:
                pos = 2;
                break;
            case 8:
                pos = 3;
                break;
            case 0:
                pos = 4;
                break;
            default:
                return false;
        }

        if( tones[tone] == pos ) {
            return true;
        }
        else {
            return false;
        }
    }

    /**
     * @brief Check if inputed number is correct
     * 
     * This is blocking for animation
     * 
     * @param x Inputed number
    */
    bool checkNumber( uint8_t x ) {
        loading_circle.setAnimation();
        while( !loading_circle.isFinished() ) {
            loading_circle.proceed();
        }

        switch(number) {
            case 1:
                return checkTableA(3, x);
            case 2:
                break;
            case 3:
                return checkTableA(4, x);
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            case 8:
                break;
            case 9:
                break;
            case 0:
                break;
        }
        return false;
    }

    virtual void react( Update const & ) {};

    /* Keypad */
    virtual void react( KeypadZeroPressed const & ) {
        if( checkNumber(0) ) {
            transit<CompletedDiscrete>();
        }
        else {
            transit<MistakeDiscrete>();
        }
    };
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


    uint8_t tones[4] = {1, 2, 3, 4};  /**< The tone pitches */
    uint8_t number = 1;  /**< Displayed number */
};


/**
 * @brief The player is trying to push the button
*/
class PlayDiscrete : public Discrete {
public:

    void entry() override {}

    void react( ADKeyboardEnterPressed const & ) override {
        shuffleTones();
        number = genNumber();

        canvas.drawChar(1, 1, number + 48, CRGB::DarkGray, CRGB::Black, 1);
        FastLED.show();

        playTones();

        canvas.fillScreen(CRGB::Black);
        FastLED.show();
    }

    /* Keypad */
    void react( KeypadZeroPressed const & ) override {
        if( checkNumber(0) ) {
            transit<CompletedDiscrete>();
        }
        else {
            transit<MistakeDiscrete>();
        }
    };
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
    void entry() {}

    /* Completing the task after update
       to catch up to the real time after the blocking animation 
       when checking for the number
       
       This mean you will loose if you press even the correct answer at 0:01 */
    void react( Update const & ) override {
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

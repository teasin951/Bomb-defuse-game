#pragma once
#include <Arduino.h>
#include <tinyfsm.hpp>

#include "components/buzzer.h"
#include "game/events.h"
#include "components/lcd.h"
#include "variables.h"


/**
 * @file State machine implementation of game one
*/

/* Forward declaration of stages */
class G1Task1;
class G1Detonated;

/* ----------------------- State machine ------------------------- */
class GameOne : public tinyfsm::Fsm<GameOne> {
public:
    void printTime() {
        lcd.setCursor(6,1);
        lcd.print(game_time.minutes);
        lcd.print(":");
        if( game_time.seconds < 10 ) {
            lcd.print("0");
            lcd.print(game_time.seconds);
        }
        else {
            lcd.print(game_time.seconds);
        }
        lcd.print("  ");
    }

    void updateGameTime() {
        uint32_t time_remaining = game_countdown_amount - (millis() - game_start_millis);
        game_time.minutes = time_remaining / 60000;
        game_time.seconds = time_remaining / 1000 - game_time.minutes * 60;
    }

    /* General update event */
    void react( Update const & ) {
        // Check if we need to do anything
        if( !game_is_live ) { return; }

        // check for completed tasks
        if( task_completed ) {
            task_completed = false;
            GameOne::dispatch( Advance() );
        }

        if( millis() - last_time_update > time_update_delay ) {
            updateGameTime();
            printTime();
            if( game_time.minutes <= 0 && game_time.seconds <= 0 ) {
                transit<G1Detonated>();
            }
        }

        // update the current task as well
        GameOne::dispatch( UpdateTask() );
    }

    virtual void react( UpdateTask const & ) {};
    virtual void react( Advance const & ) {};

    /* Keypad */
    virtual void react( KeypadPressed const & ) {};
    virtual void react( KeypadZeroPressed const & ) {
        updateGameTime();
        printTime();
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

    /* Actions on entering/exiting a state */
    virtual void entry() {};
    virtual void exit() {};

protected:
    GAMETIME game_time;
    uint32_t last_time_update = 0;
    const uint32_t time_update_delay = 250;
};


/* ---------------------- States ---------------------- */
/* First task of the game one */
class G1Task1 : public GameOne {
    void react( Advance const & ) {
        // transit<G1Task2>();
        transit<G1Detonated>();
    }

    void entry() override {
        /* Start the game */
        game_time.minutes = 0;
        game_time.seconds = 0;
        game_countdown_amount = game_time.minutes * 60000;

        resetDisplay();
        printTime();

        game_start_millis = millis();
    }
};


/* The bomb has exploded */
class G1Detonated : public GameOne {
    void entry() override {
        rtttl::stop();


        game_is_live = false;
        game_time.minutes = 0;
        game_time.seconds = 0;

        resetDisplay();
        printTime();

        lcd.setCursor(0,0);
        lcd.print("   You failed   ");
    }

    void resetEverything() {
        tone(BUZZER_1, 800, 1000);
        delay(1200);
        resetArduino();
    }

    void react( KeypadMatched const & ) {
        resetEverything();
    }

    void react( KeypadNotMatched const & ) {
        resetEverything();
    }
};

FSM_INITIAL_STATE(GameOne, G1Task1);
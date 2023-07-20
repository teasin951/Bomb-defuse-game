#pragma once
#include <Arduino.h>
#include <tinyfsm.hpp>

#include "components/buzzer.h"
#include "components/relays.h"
#include "components/matrix.h"
#include "components/keypad.h"
#include "game/events.h"
#include "components/lcd.h"
#include "variables.h"


#include "tasks/simonsays.h"
#include "tasks/maze.h"
#include "tasks/patterns.h"
#include "tasks/button.h"



/**
 * @file State machine implementation of game one
*/

/* Forward declaration of states */
class G1Patterns;
class G1Maze;
class G1SimonSays;
class G1Detonated;
class G1Defused;

/* ----------------------- State machine ------------------------- */

/**
 * @brief Game One FSM class 
*/
class GameOne : public tinyfsm::Fsm<GameOne> {
public:

    /**
     * @brief Print current remaining time to the LCD
    */
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

    /**
     * @brief Calculate and save the current time
    */
    void updateGameTime() {
        game_countdown_amount -= game_countdown_penalty;  // to speed up countdown
        int32_t time_remaining = game_countdown_amount - (millis() - game_start_millis);
        game_time.minutes = time_remaining / 60000;
        game_time.seconds = time_remaining / 1000 - game_time.minutes * 60;
    }

    /**
     * @brief reset Arduino with a beep
    */
    void resetEverything() {
        tone(BUZZER_1, 800, 1000);
        delay(1200);
        resetArduino();
    }

    void react( Update const & ) {
        // Check if we need to do anything
        if( !game_is_live ) { return; }

        // Check for completed tasks
        if( task_completed ) {
            task_completed = false;
            GameOne::dispatch( Advance() );
        }

        // Certain games can tolerate only certain number of mistakes
        if( mistakes_count >= 3 ) {
            transit<G1Detonated>();
        }

        // Update time
        if( millis() - last_time_update > time_update_delay ) {
            updateGameTime();
            printTime();

            // Beep every second
            if( game_time.seconds != last_second_buzzer ) {
                if( bomb_beep ) {
                    tone(BUZZER_2, 4000, 20);
                    last_second_buzzer = game_time.seconds;
                }
            }

            // transit<>() should be at the end of react() call
            if( game_time.minutes <= 0 && game_time.seconds <= 0 ) {
                transit<G1Detonated>();
            }
        }

        // Update the current task as well
        GameOne::dispatch( UpdateTask() );
    }

    virtual void react( UpdateTask const & ) {};
    virtual void react( Advance const & ) {};

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
    uint32_t last_time_update = 0;
    const uint32_t time_update_delay = 250;
    uint8_t last_second_buzzer = 0;
};


/* ---------------------- States ---------------------- */

/* Forward declare the game class */
class Button;

/**
 * @brief Button game state 
 */
class G1Button : public GameOne {
    void entry() {
        Button::start();
    }

    void react( Advance const & e ) {
        transit<G1Defused>();
    }

    /* General update event */
    void react( UpdateTask const & e ) override { Button::dispatch( Update() ); };

    /* Keypad */
    void react( KeypadZeroPressed const & e ) override { Button::dispatch(e); };
    void react( KeypadOnePressed const & e ) override { Button::dispatch(e); };
    void react( KeypadTwoPressed const & e ) override { Button::dispatch(e); };
    void react( KeypadThreePressed const & e ) override { Button::dispatch(e); };
    void react( KeypadFourPressed const & e ) override { Button::dispatch(e); };
    void react( KeypadFivePressed const & e ) override { Button::dispatch(e); };
    void react( KeypadSixPressed const & e ) override { Button::dispatch(e); };
    void react( KeypadSevenPressed const & e ) override { Button::dispatch(e); };
    void react( KeypadEightPressed const & e ) override { Button::dispatch(e); };
    void react( KeypadNinePressed const & e ) override { Button::dispatch(e); };
    void react( KeypadMatched const & e ) override { Button::dispatch(e); };
    void react( KeypadNotMatched const & e ) override { Button::dispatch(e); };
    void react( KeypadOverflowed const & e ) override { Button::dispatch(e); };
    void react( KeypadCleared const & e ) override { Button::dispatch(e); };

    /* Emergency button */
    void react( EmergencyPressed const & e ) override { Button::dispatch(e); };
    void react( EmergencyReleased const & e ) override { Button::dispatch(e); };

    /* Potenciometers */
    void react( Potenciometer1Moved const & e ) override { Button::dispatch(e); };
    void react( Potenciometer2Moved const & e ) override { Button::dispatch(e); };
    void react( Potenciometer3Moved const & e ) override { Button::dispatch(e); };

    /* Joystick */
    void react( JoystickMoved const & e ) override { Button::dispatch(e); };
    void react( JoystickPressed const & e ) override { Button::dispatch(e); };
    void react( JoystickReleased const & e ) override { Button::dispatch(e); };
    
    /* ADKeyboard */
    void react( ADKeyboardPressed const & e ) override { Button::dispatch(e); };
    void react( ADKeyboardLeftPressed const & e ) override { Button::dispatch(e); };
    void react( ADKeyboardRightPressed const & e ) override { Button::dispatch(e); };
    void react( ADKeyboardUpPressed const & e ) override { Button::dispatch(e); };
    void react( ADKeyboardDownPressed const & e ) override { Button::dispatch(e); };
    void react( ADKeyboardEnterPressed const & e ) override { Button::dispatch(e); };
    void react( ADKeyboardLeftReleased const & e ) override { Button::dispatch(e); };
    void react( ADKeyboardRightReleased const & e ) override { Button::dispatch(e); };
    void react( ADKeyboardUpReleased const & e ) override { Button::dispatch(e); };
    void react( ADKeyboardDownReleased const & e ) override { Button::dispatch(e); };
    void react( ADKeyboardEnterReleased const & e ) override { Button::dispatch(e); };
};


/* Forward declare the game class */
class Patterns;

/**
 * @brief Patterns game state 
 */
class G1Patterns : public GameOne {
    void entry() {
        Patterns::start();
    }

    void react( Advance const & e ) {
        transit<G1Button>();
    }

    /* General update event */
    void react( UpdateTask const & e ) override { Patterns::dispatch( Update() ); };
    
    /* ADKeyboard */
    void react( ADKeyboardLeftPressed const & e ) override { Patterns::dispatch(e); };
    void react( ADKeyboardRightPressed const & e ) override { Patterns::dispatch(e); };
    void react( ADKeyboardUpPressed const & e ) override { Patterns::dispatch(e); };
    void react( ADKeyboardDownPressed const & e ) override { Patterns::dispatch(e); };
};


/* Forward declare the game class */
class Maze;

/**
 * @brief Maze game state 
 */
class G1Maze : public GameOne {
    void entry() {
        Maze::start();
    }

    void react( Advance const & e ) {
        transit<G1Patterns>();
    }

    /* General update event */
    void react( UpdateTask const & e ) override { Maze::dispatch( Update() ); };

    /* Joystick */
    void react( JoystickMoved const & e ) override { Maze::dispatch(e); };
};


/**
 * @brief Simon Says game state 
 */
class G1SimonSays : public GameOne {
    void entry() {
        SimonSays::start();
    }

    void react( Advance const & e ) {
        transit<G1Maze>();
    }

    /* General update event */
    void react( UpdateTask const & e ) override { SimonSays::dispatch( Update() ); };

    /* Keypad */
    void react( KeypadZeroPressed const & e ) override { SimonSays::dispatch(e); };
    void react( KeypadOnePressed const & e ) override { SimonSays::dispatch(e); };
    void react( KeypadTwoPressed const & e ) override { SimonSays::dispatch(e); };
    void react( KeypadThreePressed const & e ) override { SimonSays::dispatch(e); };
    void react( KeypadFourPressed const & e ) override { SimonSays::dispatch(e); };
    void react( KeypadFivePressed const & e ) override { SimonSays::dispatch(e); };
    void react( KeypadSixPressed const & e ) override { SimonSays::dispatch(e); };
    void react( KeypadSevenPressed const & e ) override { SimonSays::dispatch(e); };
    void react( KeypadEightPressed const & e ) override { SimonSays::dispatch(e); };
    void react( KeypadNinePressed const & e ) override { SimonSays::dispatch(e); };

    /* Emergency button */
    void react( EmergencyPressed const & e ) override { SimonSays::dispatch(e); };
    void react( EmergencyReleased const & e ) override { SimonSays::dispatch(e); };

    /* Potenciometers */
    void react( Potenciometer1Moved const & e ) override { SimonSays::dispatch(e); };
    void react( Potenciometer2Moved const & e ) override { SimonSays::dispatch(e); };
    void react( Potenciometer3Moved const & e ) override { SimonSays::dispatch(e); };

    /* Joystick */
    void react( JoystickMoved const & e ) override { SimonSays::dispatch(e); };
    void react( JoystickPressed const & e ) override { SimonSays::dispatch(e); };
    void react( JoystickReleased const & e ) override { SimonSays::dispatch(e); };
    
    /* ADKeyboard */
    void react( ADKeyboardPressed const & e ) override { SimonSays::dispatch(e); };
    void react( ADKeyboardLeftPressed const & e ) override { SimonSays::dispatch(e); };
    void react( ADKeyboardRightPressed const & e ) override { SimonSays::dispatch(e); };
    void react( ADKeyboardUpPressed const & e ) override { SimonSays::dispatch(e); };
    void react( ADKeyboardDownPressed const & e ) override { SimonSays::dispatch(e); };
    void react( ADKeyboardEnterPressed const & e ) override { SimonSays::dispatch(e); };
    void react( ADKeyboardLeftReleased const & e ) override { SimonSays::dispatch(e); };
    void react( ADKeyboardRightReleased const & e ) override { SimonSays::dispatch(e); };
    void react( ADKeyboardUpReleased const & e ) override { SimonSays::dispatch(e); };
    void react( ADKeyboardDownReleased const & e ) override { SimonSays::dispatch(e); };
    void react( ADKeyboardEnterReleased const & e ) override { SimonSays::dispatch(e); };
};


/**
 * @brief State initializing the game 
 */
class G1Init : public GameOne {
    void entry() override {
        /* Wait for emergency button release */
        while( digitalRead(BUTTON_IN) == HIGH ) {
            lcd.print(" Release button ");
        }

        /* Start the game */
        game_time.minutes = 15;
        game_time.seconds = 0;
        game_countdown_amount = game_time.minutes * 60000;

        resetDisplay();
        printTime();

        delay(3000);  // wait a bit

        game_start_millis = millis();
    }

    void react( UpdateTask const & ) override {
        transit<G1SimonSays>();
    }
};

/**
 * @brief The bomb has exploded state
 */
class G1Detonated : public GameOne {
    void entry() override {
        rtttl::stop();
        setRelays(0,0,0,0);
        clearMatrix();

        noTone(BUZZER_1);
        tone(BUZZER_1, 4000, 3000);


        game_is_live = false;
        game_time.minutes = 0;
        game_time.seconds = 0;

        resetDisplay();
        printTime();

        lcd.setCursor(0,0);
        lcd.print("   You failed   ");
    }

    void react( KeypadMatched const & ) {
        resetEverything();
    }

    void react( KeypadNotMatched const & ) {
        resetEverything();
    }
};


/** 
 * @brief The bomb has been defused state 
 */
class G1Defused : public GameOne {
    void entry() override {
        rtttl::stop();
        setRelays(0,0,0,0);
        clearMatrix();

        noTone(BUZZER_1);

        game_is_live = false;
        resetDisplay();
        printTime();

        lcd.setCursor(0,0);
        lcd.print("  Bomb defused  ");

        rtttl::begin(BUZZER_1, bomb_defused);
    }

    void react( KeypadMatched const & ) {
        resetEverything();
    }

    void react( KeypadNotMatched const & ) {
        resetEverything();
    }
};


FSM_INITIAL_STATE(GameOne, G1Init);

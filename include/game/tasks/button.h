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


bool first_is_true;
bool second_is_true;
bool third_is_true;
bool fourth_is_true;


/* Forward state declaration */
class InitButton;
class PlayButton;
class MistakeButton;
class CompletedButton;


class Button : public tinyfsm::Fsm<Button> {
public:
    int16_t first_pot = 250;
    int16_t second_pot = 250;
    int16_t third_pot = 250;

    bool joystick_is_left = false;
    bool joystick_is_pressed = false;
    bool right_pressed = false;


    bool checkFirst() {
        if( third_pot > 1000 && first_pot < 40 ) {
            if(first_is_true) {
                setButtonLEDs(255, 0, 0);
            }
            else {
                setButtonLEDs(0, 0, 0);
            }
            return true;
        }        
        else {
            return false;
        }
    }

    bool checkSecond() {
        if( joystick_is_pressed ) {
            if(second_is_true) {
                setButtonLEDs(0, 255, 0);
            }
            else {
                setButtonLEDs(255, 0, 0);
            }
            return true;
        }        
        else {
            return false;
        }
    }

    bool checkThird() {
        if( first_pot > 430 && first_pot < 580 && second_pot > 430 && second_pot < 580 ) {
            if(third_is_true) {
                setButtonLEDs(255, 0, 255);
            }
            else {
                setButtonLEDs(160, 255, 0);
            }
            return true;
        }        
        else {
            return false;
        }
    }

    bool checkFourth() {
        if( joystick_is_left && right_pressed ) {
            if(fourth_is_true) {
                setButtonLEDs(0, 0, 255);
            }
            else {
                setButtonLEDs(0, 255, 255);
            }
            return true;
        }        
        else {
            return false;
        }
    }

    void displayColour() {
        if( checkFirst() ) {
            return;
        }
        else if ( checkSecond() ) {
            return;
        }
        else if( checkThird() ) {
            return;
        }
        else if( checkFourth() ) {
            return;
        }
        setButtonLEDs(0, 255, 0);
    }

    /* General update event */
    virtual void react( Update const & ) {}

    void react( tinyfsm::Event const & ) {};

    /* Keypad */
    virtual void react( KeypadPressed const & ) {
        tone(BUZZER_1, 200, 100);
        game_countdown_penalty += 10;
    };

    virtual void react( KeypadMatched const & ) {
        tone(BUZZER_1, 200, 100);
        game_countdown_penalty += 10;
    };
    virtual void react( KeypadNotMatched const & ) {
        tone(BUZZER_1, 200, 100);
        game_countdown_penalty += 10;
    };
    virtual void react( KeypadCleared const & ) {
        tone(BUZZER_1, 200, 100);
        game_countdown_penalty += 10;
    };
    virtual void react( KeypadOverflowed const & ) {
        tone(BUZZER_1, 200, 100);
        game_countdown_penalty += 10;
    };

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
    virtual void react( ADKeyboardPressed const & ) {
        tone(BUZZER_1, 200, 100);
        game_countdown_penalty += 10;
    };
    virtual void react( ADKeyboardRightPressed const & ) {};
    virtual void react( ADKeyboardRightReleased const & ) {};
    
    /* Actions on entering/exiting a state */
    virtual void entry() {};
    virtual void exit() {};
};


/**
 * @brief The player is trying to push the button
*/
class PlayButton : public Button {
public:
    void entry() {}

    /* Potenciometers */
    void react( Potenciometer1Moved const & e ) override {
        first_pot = e.current_amount;
        displayColour();
    }

    void react( Potenciometer2Moved const & e ) override {
        second_pot = e.current_amount;
        displayColour();
    }
    void react( Potenciometer3Moved const & e ) override {
        third_pot = e.current_amount;
        displayColour();
    }

    /* ADKeyboard */
    void react( ADKeyboardRightPressed const & ) override {
        right_pressed = true;
        displayColour();
    }
    void react( ADKeyboardRightReleased const & ) override {
        right_pressed = false;
        displayColour();
    }

    /* Joystick */
    void react( JoystickMoved const & e ) override {
        if( e.x > 1000 ) {
            joystick_is_left = true;
        }
        else {
            joystick_is_left = false;
        }
        displayColour();
    }
    void react( JoystickPressed const & ) override {
        joystick_is_pressed = true;
        displayColour();
    }
    void react( JoystickReleased const & ) override {
        joystick_is_pressed = false;
        displayColour();
    }

    /* Return if the answer is C */
    bool isC() {
        if( (!first_is_true && !second_is_true && !third_is_true && !fourth_is_true ) ||
            (!first_is_true && third_is_true && fourth_is_true ) || 
            ( first_is_true && second_is_true && !third_is_true && !fourth_is_true ) 
            ) {
                return true;
            }
            return false;
    }

    bool isD() {
        if( ( !first_is_true && !second_is_true && third_is_true && !fourth_is_true ) || 
            ( first_is_true && !second_is_true && third_is_true && fourth_is_true ) ||
            ( first_is_true && second_is_true && third_is_true && !fourth_is_true ) 
        ) {
            return true;
        }
        return false;
    }

    bool isS() {
        if( ((!first_is_true && second_is_true && !third_is_true && fourth_is_true) || 
			(!first_is_true && second_is_true && third_is_true && !fourth_is_true) || 
			(first_is_true && !second_is_true && !third_is_true && !fourth_is_true)) 
        ) {
            return true;
        }
        return false;
    }

    bool isP() {
        if( ((!first_is_true && second_is_true && !third_is_true && !fourth_is_true) ||
			(first_is_true && second_is_true && fourth_is_true)) 
        ) {
            return true;
        }
        return false;
    }

    bool isB() {
        if( ((!second_is_true && !third_is_true && fourth_is_true) ||
			(first_is_true && !second_is_true && third_is_true && !fourth_is_true)) ) {
            return true;
        }
        return false;
    }

    /* Emergency button */
    void react( EmergencyPressed const & ) override {
        if( isC() ) {
            if( game_time.seconds / 10 == 5 ) {
                transit<CompletedButton>();
            }
            else {
                transit<MistakeButton>();
            }
        }
        else if( isD() ) {
            if( game_time.seconds / 10 == 1 ) {
                transit<CompletedButton>();
            }
            else {
                transit<MistakeButton>();
            }
        }
        else if( isS() ) {
            if( game_time.seconds / 10 == 0 ) {
                transit<CompletedButton>();
            }
            else {
                transit<MistakeButton>();
            }
        }
        else if( isP() ) {
            if( game_time.seconds / 10 == 3 ) {
                transit<CompletedButton>();
            }
            else {
                transit<MistakeButton>();
            }
        }
        else if( isB() ) {
            if( game_time.seconds / 10 == 2 ) {
                transit<CompletedButton>();
            }
            else {
                transit<MistakeButton>();
            }
        }
    }
};


/**
 * @brief The player has made a mistake
*/
class MistakeButton : public Button {
public:
    void entry() override {
        bomb_beep = false;
        game_countdown_penalty += 40;  // faster countdown
        mistakes_count++;
        noTone(BUZZER_1);
        tone(BUZZER_1, 200);

        setButtonLEDs(255, 0, 0);
        turned_on = true;
        start_millis = millis();
    }

    void exit() {
        noTone(BUZZER_1);
        bomb_beep = true;
    }

    void react( Update const & ) {
        if( millis() - start_millis > blink_delay ) {
            if( turned_on ) {
                setButtonLEDs(0, 0, 0);
                turned_on = false;
            }
            else {
                setButtonLEDs(255, 0, 0);
                turned_on = true;
            }
            start_millis = millis();
        }
    }

    void react( EmergencyReleased const & ) {
        transit<PlayButton>();
    }

private:
    bool turned_on = false;
    uint32_t start_millis = 0;
    const uint32_t blink_delay = 500;
};


/**
 * @brief Button has been completed
*/
class CompletedButton : public Button {
public:
    void entry() {
        bomb_beep = false;
        setRelays(0,0,0,0);
        setButtonLEDs(0, 0, 0);
        rtttl::begin(BUZZER_1, task_finished);
        start_millis = millis();
    }

    void react( Update const & ) {
        if( millis() - start_millis > finish_delay ) {
            bomb_beep = true;
            task_completed = true;
        }
    }

private:
    uint32_t start_millis = 0;
    const uint32_t finish_delay = 1000;
};


/**
 * @brief Initialize the game
*/
class InitButton : public Button {
public:
    void entry() {
        // Set the stage for Button
        setRelays(0,0,0,1);
        clearMatrix();

        /* generate random configuration */
        first_is_true = random(0, 2);
        second_is_true = random(0, 3);
        third_is_true = random(0, 2);
        fourth_is_true = random(0, 3);

        setButtonLEDs(0, 255, 0);
    }

    void react( Update const & ) {
        transit<PlayButton>();
    }
};


FSM_INITIAL_STATE(Button, InitButton);

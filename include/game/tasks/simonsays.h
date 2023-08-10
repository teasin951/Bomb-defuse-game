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


/**
 * @file The SimonSays task implementation
*/


/**
 * @brief Struct holding all info needed for Simon Says
*/
struct SimonInfo {
    /* config */
    static const int lower_seq_bound = 3;  /**< The shortest possible sequence */
    static const int high_seq_bound = 5;  /**< The longest possible sequence */
    // ------ //

    uint8_t seq_length = 3;  /**< The actual length of the sequence for the user */
    uint8_t in_pos = 0;  /**< Input position */
    uint8_t pos = 0;  /**< Position in the expected sequence */

    static const int max_sequence = 8;  /**< maximal length of the sequence */
    uint8_t input[max_sequence] = { 0 };  /**< Inputed sequence for comparison */
    uint8_t seq[max_sequence] = {63};  /**< Expected sequence */

    bool joystick_used = false;  /**< Check if the joystick has returned to the default position after move */
};
struct SimonInfo simon_info;


/* Forward declaration */
class BasicInput;
class ResetSimon;
class InitSimon;
class SimonCompleted;


/**
 * Each sequence entry is encoded like so:
 * 
 * ADKeyboard = 10
 * Keypad = 20
 * Joystick = 30
 * 
 * Left = 1
 * Right = 2
 * Up = 3
 * Down = 4
*/
class SimonSays : public tinyfsm::Fsm<SimonSays> {
public:
    /**
     * @brief Generate a random new entry and save to seq[]
    */
    void genEntry() {
        simon_info.seq[simon_info.pos] = random(1, 4) * 10 + random(1, 5);
    }

    /**
     * @brief Based on the sequence entry, decide the colour for the ADKeyboard symbol
    */
    CRGB decideADKeyboardColour( uint8_t x ) {
        switch(x) {
            case 1:
                return CRGB::Green;
            case 2:
                return CRGB::Yellow;
            case 3:
                return CRGB::Blue;
            case 4:
                return CRGB::Red;
        }
        return CRGB::Black;
    }

    /**
     * @brief Based on the sequence entry, decide the colour for the Keypad symbol
    */
    CRGB decideKeypadColour( uint8_t x ) {
        switch(x) {
            case 1:
                return CRGB::Green;
            case 2:
                return CRGB::Blue;
            case 3:
                return CRGB::Red;
            case 4:
                return CRGB::Yellow;
        }
        return CRGB::Black;
    }

    /**
     * @brief Based on the sequence entry, decide the colour for the Joystick symbol
    */
    CRGB decideJoystickColour( uint8_t x ) {
        switch(x) {
            case 1:
                return CRGB::Red;
            case 2:
                return CRGB::Green;
            case 3:
                return CRGB::Yellow;
            case 4:
                return CRGB::Blue;
        }
        return CRGB::Black;
    }

    /**
     * @brief Display the symbol that should be currently added to the input sequence
    */
    void displayCurrentSymbol() {
        uint8_t first = simon_info.seq[simon_info.pos] / 10;
        uint8_t second = simon_info.seq[simon_info.pos] % 10;

        canvas.fillScreen(CRGB::Black);

        /* Draw the expected symbol */
        switch(first) {
            case 1:
                canvas.fillRect(2, 2, 4, 4, decideADKeyboardColour(second));
                break;

            case 2:
                canvas.fillTriangle(0, 5, 6, 5, 3, 2, decideKeypadColour(second));
                break;

            case 3:
                canvas.fillCircle(3, 3, 2, decideJoystickColour(second));
                break;
        }

        FastLED.show();
    }

    /**
     * @brief Compare the inputed and expected sequence
     * 
     * @return bool They match or do not
    */
    bool compareSequences() {
        for( uint8_t i = 0; i < simon_info.in_pos + 1; i++ ) {
            if( simon_info.seq[i] != simon_info.input[i] ) {
                return false;
            }
        }
        return true;
    }

    /**
     * @brief Check the inputed and expected sequences and perform actions based on the results and the current state of the game
    */
    void checkSequence() {
        // The entered sequence is wrong
        if( !compareSequences() ) {
            transit<ResetSimon>();
            return;
        }

        // The currently entered sequence is as long as the displayed one
        if( simon_info.in_pos == simon_info.pos ) {
            simon_info.in_pos = 0;
            simon_info.pos++;

            // The entire task sequence has been entered correctly
            if( simon_info.pos == simon_info.seq_length ) {
                transit<SimonCompleted>();
            }
            
            // We are not at the end of the task yet
            else {
                tone(BUZZER_1, 400, 50);  // indicate correct entry

                genEntry();
                clearMatrix();
                displayCurrentSymbol();
            }
        }
        // Another correct symbol of the given sequence
        else {
            tone(BUZZER_1, 400, 50);  // indicate correct entry
            simon_info.in_pos++;
        }
    }

    /* General update event */
    virtual void react( Update const & ) {}

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

};

//------------------ States ------------------//

/**
 * @brief Wait and react to input from user
*/
class BasicInput : public SimonSays {
    /* Keypad */
    void react( KeypadZeroPressed const & ) override {
        clearSequence();
        transit<ResetSimon>(); 
    }
    void react( KeypadOnePressed const & ) override {
        clearSequence();
        transit<ResetSimon>(); 
    }
    void react( KeypadTwoPressed const & ) override {
        clearSequence();
        simon_info.input[simon_info.in_pos] = 23;
        checkSequence();
    }
    void react( KeypadThreePressed const & ) override {
        clearSequence();
        transit<ResetSimon>(); 
    }
    void react( KeypadFourPressed const & ) override {
        clearSequence();
        simon_info.input[simon_info.in_pos] = 21;
        checkSequence();
    }
    void react( KeypadFivePressed const & ) override {
        clearSequence();
        transit<ResetSimon>(); 
    }
    void react( KeypadSixPressed const & ) override {
        clearSequence();
        simon_info.input[simon_info.in_pos] = 22;
        checkSequence();
    }
    void react( KeypadSevenPressed const & ) override {
        clearSequence();
        transit<ResetSimon>(); 
    }
    void react( KeypadEightPressed const & ) override {
        clearSequence();
        simon_info.input[simon_info.in_pos] = 24;
        checkSequence();
    }
    void react( KeypadNinePressed const & ) override {
        clearSequence();
        transit<ResetSimon>(); 
    }

    /* Joystick */
    void react( JoystickMoved const & e ) override {
        if( !simon_info.joystick_used ) {

            /* Left */
            if( e.x > 1000 && e.y < 600 && e.y > 400 ) {
                simon_info.input[simon_info.in_pos] = 31;
                checkSequence();

                simon_info.joystick_used = true;
            }
            /* Right */
            else if( e.x < 40 && e.y < 600 && e.y > 400 ) {
                simon_info.input[simon_info.in_pos] = 32;
                checkSequence();

                simon_info.joystick_used = true;
            }
            /* Up */
            else if( e.y > 1000 && e.x < 600 && e.x > 400 ) {
                simon_info.input[simon_info.in_pos] = 33;
                checkSequence();

                simon_info.joystick_used = true;
            }
            /* Down */
            else if( e.y < 40 && e.x < 600 && e.x > 400 ) {
                simon_info.input[simon_info.in_pos] = 34;
                checkSequence();

                simon_info.joystick_used = true;
            }

        }
        else if( e.x < 600 && e.x > 400 && e.y < 600 && e.y > 400 ) {
            simon_info.joystick_used = false;
        }
    }
    
    /* ADKeyboard */
    void react( ADKeyboardLeftPressed const & ) override {
        simon_info.input[simon_info.in_pos] = 11;
        checkSequence();
    }
    void react( ADKeyboardRightPressed const & ) override {
        simon_info.input[simon_info.in_pos] = 12;
        checkSequence();
    }
    void react( ADKeyboardUpPressed const & ) override {
        simon_info.input[simon_info.in_pos] = 13;
        checkSequence();
    }
    void react( ADKeyboardDownPressed const & ) override {
        simon_info.input[simon_info.in_pos] = 14;
        checkSequence();
    }
};

/**
 * @brief Set up Simon Says
*/
class InitSimon : public SimonSays {
public:    
    /* Setup the game */
    void entry() override {
        simon_info = SimonInfo();

        setRelays(0, 0, 1, 1);
        clearSequence();

        simon_info.seq_length = random(simon_info.lower_seq_bound, simon_info.high_seq_bound + 1);

        genEntry();
        displayCurrentSymbol();
    }

    void react( Update const & ) {
        transit<BasicInput>();
    }

};

/**
 * @brief The user inputed sequence was incorrect, reset 
*/
class ResetSimon : public SimonSays {
    /**
     * @brief Draw a cross to matrix
    */
    void drawCross() {
        canvas.fillScreen(CRGB::Black);
        canvas.drawLine(1, 1, 6, 6, CRGB::Red);
        canvas.drawLine(1, 6, 6, 1, CRGB::Red);
        FastLED.show();
    }


    void react( Update const & ) {
        if( millis() - start_millis > hide_delay && !hidden) {
            clearMatrix();
        }

        if( millis() - start_millis > restart_delay ) {
            transit<BasicInput>();
        }

    }

    void entry() {
        bomb_beep = false;
        game_countdown_amount -= 30000;  // penalize the mistaky -30s
        tone(BUZZER_1, 200, 300);
        
        drawCross();
        start_millis = millis();

        for( uint8_t i = 0; i < simon_info.max_sequence; i++ ) {
            simon_info.input[i] = 0;
            simon_info.seq[i] = 63;
        }

        simon_info.pos = 0;
        simon_info.in_pos = 0;
    }

    void exit() {
        bomb_beep = true;
        hidden = false;
        genEntry();
        tone(BUZZER_1, 400, 100);
        displayCurrentSymbol();
    }

private:
    uint32_t start_millis = 0;
    const uint32_t restart_delay = 500;
    const uint32_t hide_delay = 300;
    bool hidden = false;

};

/**
 * @brief The sequence has been inputed correctly
*/
class SimonCompleted : public SimonSays {
public:
    void entry() {
        task_completed = true;
    }
};

FSM_INITIAL_STATE(SimonSays, InitSimon);

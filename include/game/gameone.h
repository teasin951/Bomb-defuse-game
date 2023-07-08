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



/**
 * @file State machine implementation of game one
*/

/* Forward declaration of stages */
class G1SimonSays;
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

            if( game_time.seconds != last_second_buzzer ) {
                tone(BUZZER_2, 4000, 20);
                last_second_buzzer = game_time.seconds;
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
    uint32_t last_time_update = 0;
    const uint32_t time_update_delay = 250;
    uint8_t last_second_buzzer = 0;
};


/* ---------------------- States ---------------------- */
/* First task: Simon says */
// Possibly templatable later
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
class G1SimonSays : public GameOne {

    /**
     * @brief Generate a random new entry and save to seq[]
    */
    void genEntry() {
        seq[pos] = random(1, 4) * 10 + random(1, 5);
    }

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

    void displayCurrentSymbol() {
        uint8_t first = seq[pos] / 10;
        uint8_t second = seq[pos] % 10;

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

    void resetSimon() {
        tone(BUZZER_1, 200, 200);
        canvas.fillScreen(CRGB::Black);
        canvas.drawLine(1, 1, 6, 6, CRGB::Red);
        canvas.drawLine(1, 6, 6, 1, CRGB::Red);
        FastLED.show();
        delay(200);

        clearMatrix();

        for( uint8_t i = 0; i < max_sequence; i++ ) {
            input[i] = 0;
            seq[i] = 63;
        }

        pos = 0;
        genEntry();
        displayCurrentSymbol();
    }

    bool compareSequences() {
        for( uint8_t i = 0; i < pos + 1; i++ ) {
            if( seq[i] != input[i] ) {
                return false;
            }
        }
        return true;
    }

    void checkSequence() {
        if( !compareSequences() ) {
            resetSimon();
        }
        else {
            pos++;
            if( pos == seq_length ) {
                //DONE
                tone(BUZZER_1, 400, 200);
            }

            genEntry();
            clearMatrix();
            displayCurrentSymbol();
        }
    }

    void react( KeypadTwoPressed const & ) {
        clearSequence();
        input[pos] = 23;
        checkSequence();
    }

    /* Setup the game */
    void entry() override {
        setRelays(0, 0, 1, 1);
        seq_length = random(lower_seq_bound, high_seq_bound + 1);

        genEntry();
        displayCurrentSymbol();
    }

private:
    /* config */
    static const int lower_seq_bound = 3;  /**< The shortest possible sequence */
    static const int high_seq_bound = 4;  /**< The longest possible sequence */
    // ------ //

    uint8_t seq_length = 3;  /**< The actuall length of the sequence for the user */
    uint8_t pos = 0;

    static const int max_sequence = 6;  /**< maximal length of the sequence */
    uint8_t input[max_sequence] = { 0 };  /**< Inputed sequence for comparison */
    uint8_t seq[max_sequence] = {63};  /**< Expected sequence */
};


/* Initialize the game */
class G1Init : public GameOne {
    void entry() override {
        /* Start the game */
        game_time.minutes = 0;
        game_time.seconds = 30;
        game_countdown_amount = game_time.minutes * 60000 + game_time.seconds * 1000;

        resetDisplay();
        printTime();

        delay(3000);  // wait a bit

        game_start_millis = millis();
    }

    void react( UpdateTask const & ) override {

        transit<G1SimonSays>();
    }
};

/* The bomb has exploded */
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


FSM_INITIAL_STATE(GameOne, G1Init);

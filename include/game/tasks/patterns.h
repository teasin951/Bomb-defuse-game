#pragma once
#include <Arduino.h>
#include <tinyfsm.hpp>
#include "../variables.h"
#include "../events.h"
#include "components/pins.h"
#include "components/matrix.h"
#include "components/relays.h"
#include "components/buzzer.h"
#include "components/adkeyboard.h"


/**
 * @file Implementation of the Pattern task
*/

/* pattern_number % 5 -> left - 1; right - 2; up - 3; down - 4 */
uint8_t pattern_number = 0;  /**< specific number for a pattern, modulo 5 gives the direction */


/* Forward state declaration */
class InitPatterns;
class PlayPatterns;
class MistakePatterns;
class CompletedPatterns;


/**
 * @brief FSM for Patterns task
*/
class Patterns : public tinyfsm::Fsm<Patterns> {
public:

    /**
     * @brief Display one of the patterns
    */
    void displayPattern() {
        CRGB col = CRGB::Magenta;
        canvas.fillScreen( CRGB::Black );

        switch( pattern_number ) {
            case 1:
                canvas.drawLine(0, 0, 0, 1, col);
                canvas.drawLine(0, 6, 0, 7, col);
                canvas.drawLine(1, 2, 1, 5, col);
                canvas.drawLine(2, 0, 2, 1, col);
                canvas.drawRect(2, 6, 2, 2, col);
                canvas.drawLine(3, 2, 3, 3, col);
                canvas.drawRect(4, 0, 2, 2, col);
                canvas.drawLine(4, 4, 4, 5, col);
                canvas.drawRect(5, 6, 2, 2, col);
                canvas.drawLine(6, 2, 6, 3, col);
                canvas.drawLine(7, 0, 7, 1, col);
                canvas.drawLine(7, 4, 7, 5, col);
                break;
            case 2:
                canvas.drawRect(0, 0, 4, 2, col);
                canvas.drawLine(0, 4, 0, 5, col);
                canvas.drawLine(1, 6, 1, 7, col);
                canvas.drawRect(2, 4, 3, 2, col);
                canvas.drawLine(4, 2, 4, 3, col);
                canvas.drawLine(5, 6, 5, 7, col);
                canvas.drawRect(5, 0, 2, 2, col);
                canvas.drawRect(6, 4, 2, 2, col);
                canvas.drawLine(7, 2, 7, 3, col);
                break;
            case 3:
                canvas.drawRect(0, 0, 3, 2, col);
                canvas.drawLine(0, 4, 0, 5, col);
                canvas.drawLine(1, 6, 1, 7, col);
                canvas.drawRect(2, 4, 3, 2, col);
                canvas.drawLine(3, 2, 3, 3, col);
                canvas.drawRect(4, 0, 3, 2, col);
                canvas.drawLine(5, 6, 5, 7, col);
                canvas.drawLine(6, 4, 6, 5, col);
                canvas.drawLine(7, 2, 7, 3, col);
                canvas.drawLine(7, 6, 7, 7, col);
                break;
            case 4:
                canvas.drawLine(0, 0, 0, 1, col);
                canvas.drawRect(0, 4, 2, 2, col);
                canvas.drawLine(1, 2, 1, 3, col);
                canvas.drawRect(2, 0, 2, 2, col);
                canvas.drawLine(2, 6, 2, 7, col);
                canvas.drawLine(3, 4, 3, 5, col);
                canvas.drawLine(4, 2, 4, 3, col);
                canvas.drawLine(4, 6, 4, 7, col);
                canvas.drawRect(5, 0, 3, 2, col);
                canvas.drawLine(5, 4, 5, 5, col);
                canvas.drawLine(6, 6, 6, 7, col);
                canvas.drawLine(7, 4, 7, 5, col);
                break;
            case 6:
                canvas.drawLine(0, 0, 0, 1, col);
                canvas.drawRect(0, 4, 2, 2, col);
                canvas.drawLine(1, 2, 1, 3, col);
                canvas.drawRect(2, 0, 2, 2, col);
                canvas.drawLine(2, 6, 2, 7, col);
                canvas.drawRect(3, 4, 2, 2, col);
                canvas.drawLine(4, 2, 4, 3, col);
                canvas.drawRect(5, 0, 3, 2, col);
                canvas.drawLine(5, 6, 5, 7, col);
                canvas.drawLine(6, 4, 6, 5, col);
                canvas.drawLine(7, 6, 7, 7, col);
                break;
            case 7:
                canvas.drawLine(0, 0, 0, 1, col);
                canvas.drawLine(0, 6, 0, 7, col);
                canvas.drawRect(1, 2, 2, 4, col);
                canvas.drawRect(3, 0, 2, 2, col);
                canvas.drawLine(3, 6, 3, 7, col);
                canvas.drawRect(4, 4, 3, 2, col);
                canvas.drawLine(5, 2, 5, 3, col);
                canvas.drawRect(6, 0, 2, 2, col);
                canvas.drawLine(7, 6, 7, 7, col);
                break;
            case 8:
                canvas.drawLine(0, 0, 0, 1, col);
                canvas.drawLine(0, 6, 0, 7, col);
                canvas.drawRect(1, 2, 3, 2, col);
                canvas.drawLine(1, 4, 1, 5, col);
                canvas.drawLine(2, 6, 2, 7, col);
                canvas.drawRect(3, 4, 3, 2, col);
                canvas.drawLine(4, 0, 4, 1, col);
                canvas.drawLine(5, 2, 5, 3, col);
                canvas.drawRect(6, 0, 2, 2, col);
                canvas.drawRect(6, 6, 2, 2, col);
                break;
            case 9:
                canvas.drawRect(0, 0, 3, 2, col);
                canvas.drawLine(0, 4, 0, 5, col);
                canvas.drawRect(1, 6, 2, 2, col);
                canvas.drawLine(3, 2, 3, 5, col);
                canvas.drawRect(4, 0, 3, 2, col);
                canvas.drawLine(4, 6, 4, 7, col);
                canvas.drawRect(5, 4, 2, 2, col);
                canvas.drawLine(7, 2, 7, 3, col);
                canvas.drawLine(7, 6, 7, 7, col);
                break;
        }
        FastLED.show();
    }

    /**
     * @brief Compare expected input to user input and transit accordingly
    */
    void checkEntry( uint8_t in ) {
        if( in == ( pattern_number % 5 ) ) {
            transit<CompletedPatterns>();
        }
        else {
            transit<MistakePatterns>();
        }
    }

    /* General update event */
    virtual void react( Update const & ) {}
    void react( tinyfsm::Event const & ) {};

    /* ADKeyboard */
    virtual void react( ADKeyboardLeftPressed const & ) {};
    virtual void react( ADKeyboardRightPressed const & ) {};
    virtual void react( ADKeyboardUpPressed const & ) {};
    virtual void react( ADKeyboardDownPressed const & ) {};
    
    /* Actions on entering/exiting a state */
    virtual void entry() {};
    virtual void exit() {};
};


/**
 * @brief Waiting for the user input
*/
class PlayPatterns : public Patterns {
public:
    void entry() {
        pattern_number = random(0, 2) * 5 + random(1, 5);  // Generates { 1 ... 9 } \ { 5 }
        displayPattern();
    }

    void react( ADKeyboardLeftPressed const & ) {
        checkEntry(1);
    }
    void react( ADKeyboardRightPressed const & ) {
        checkEntry(2);
    }
    void react( ADKeyboardUpPressed const & ) {
        checkEntry(3);
    }
    void react( ADKeyboardDownPressed const & ) {
        checkEntry(4);
    }
};


/**
 * @brief The player has made a mistake
*/
class MistakePatterns : public Patterns {
public:

    /**
     * @brief Draw a cross to the matrix
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
            transit<PlayPatterns>();
        }

    }

    void entry() {
        bomb_beep = false;
        game_countdown_amount -= 90000;  // penalize the mistake -30s
        tone(BUZZER_1, 200, 300);
        
        drawCross();
        start_millis = millis();
    }

    void exit() {
        bomb_beep = true;
        hidden = false;
        tone(BUZZER_1, 400, 100);
    }


private:
    uint32_t start_millis = 0;
    const uint32_t restart_delay = 500;
    const uint32_t hide_delay = 300;
    bool hidden = false;
};


/**
 * @brief Patterns has been completed
*/
class CompletedPatterns : public Patterns {
public:
    void entry() {
        task_completed = true;
    }
};


/**
 * @brief Initialize the game
*/
class InitPatterns : public Patterns {
public:
    void entry() {
        // Set the stage for Patterns
        setRelays(0,1,0,1);
        clearMatrix();
    }

    void react( Update const & ) {
        transit<PlayPatterns>();
    }
};


FSM_INITIAL_STATE(Patterns, InitPatterns);

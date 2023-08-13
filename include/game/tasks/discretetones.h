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

        if( tones[tone - 1] == pos ) {
            return true;
        }
        else {
            return false;
        }
    }

    /**
     * @brief Check the input against the table B
     * 
     * @param tone Which tone in the sequence to check
     * @param number_pressed User inputed number
    */
    bool checkTableB( uint8_t tone, uint8_t number_pressed ) {
        uint8_t pos = 0;
        switch(number_pressed) {
            case 6:
                pos = 1;
                break;
            case 8:
                pos = 2;
                break;
            case 0:
                pos = 3;
                break;
            case 1:
                pos = 4;
                break;
            default:
                return false;
        }

        if( tones[tone - 1] == pos ) {
            return true;
        }
        else {
            return false;
        }
    }

    /**
     * @brief returns which condition in the P table is met first
    */
    uint8_t checkPConditions() {
        if( tones[0] > tones[1] ) {
            return 0;
        }
        else if( tones[0] < tones[2] ) {
            return 1;
        }
        else if( tones[2] > tones[3] ) {
            return 2;
        }
        else if( tones[0] > tones[3] ) {
            return 3;
        }
        else {
            return 4;
        }
    }

    /**
     * @brief returns which condition in the P table is met first
    */
    uint8_t checkQConditions() {
        if( tones[1] > tones[2] ) {
            return 0;
        }
        else if( tones[3] < tones[1] ) {
            return 1;
        }
        else if( tones[0] > tones[2] ) {
            return 2;
        }
        else if( tones[2] > tones[3] ) {
            return 3;
        }
        else {
            return 4;
        }
    }

    /**
     * @brief Check the inputed number against the first index in P table
    */
    bool checkFirstPIndex( uint8_t number_pressed ) {
        switch( checkPConditions() ) {
            case 0:
                if( number_pressed == 1 ) { return true; }
            case 1:
                if( number_pressed == 9 ) { return true; }
            case 2:
                if( number_pressed == 5 ) { return true; }
            case 3:
                if( number_pressed == 8 ) { return true; }
            case 4:
                if( number_pressed == 3 ) { return true; }
        }
        return false;
    }

    /**
     * @brief Check the inputed number against the second index in P table
    */
    bool checkSecondPIndex( uint8_t number_pressed ) {
        switch( checkPConditions() ) {
            case 0:
                if( number_pressed == 4 ) { return true; }
            case 1:
                if( number_pressed == 0 ) { return true; }
            case 2:
                if( number_pressed == 7 ) { return true; }
            case 3:
                if( number_pressed == 9 ) { return true; }
            case 4:
                if( number_pressed == 8 ) { return true; }
        }
        return false;
    }

    /**
     * @brief Check the inputed number against the third index in P table
    */
    bool checkThirdPIndex( uint8_t number_pressed ) {
        switch( checkPConditions() ) {
            case 0:
                if( number_pressed == 0 ) { return true; }
            case 1:
                if( number_pressed == 2 ) { return true; }
            case 2:
                if( number_pressed == 1 ) { return true; }
            case 3:
                if( number_pressed == 3 ) { return true; }
            case 4:
                if( number_pressed == 0 ) { return true; }
        }
        return false;
    }

    /**
     * @brief Check the inputed number against the fourth index in P table
    */
    bool checkFourthPIndex( uint8_t number_pressed ) {
        switch( checkPConditions() ) {
            case 0:
                if( number_pressed == 9 ) { return true; }
            case 1:
                if( number_pressed == 7 ) { return true; }
            case 2:
                if( number_pressed == 8 ) { return true; }
            case 3:
                if( number_pressed == 0 ) { return true; }
            case 4:
                if( number_pressed == 4 ) { return true; }
        }
        return false;
    }

    /**
     * @brief Check the inputed number against the first index in Q table
    */
    bool checkFirstQIndex( uint8_t number_pressed ) {
        switch( checkQConditions() ) {
            case 0:
                if( number_pressed == 1 ) { return true; }
            case 1:
                if( number_pressed == 3 ) { return true; }
            case 2:
                if( number_pressed == 4 ) { return true; }
            case 3:
                if( number_pressed == 6 ) { return true; }
            case 4:
                if( number_pressed == 7 ) { return true; }
        }
        return false;
    }

    /**
     * @brief Check the inputed number against the second index in Q table
    */
    bool checkSecondQIndex( uint8_t number_pressed ) {
        switch( checkQConditions() ) {
            case 0:
                if( number_pressed == 5 ) { return true; }
            case 1:
                if( number_pressed == 0 ) { return true; }
            case 2:
                if( number_pressed == 9 ) { return true; }
            case 3:
                if( number_pressed == 2 ) { return true; }
            case 4:
                if( number_pressed == 5 ) { return true; }
        }
        return false;
    }

    /**
     * @brief Check the inputed number against the third index in Q table
    */
    bool checkThirdQIndex( uint8_t number_pressed ) {
        switch( checkQConditions() ) {
            case 0:
                if( number_pressed == 7 ) { return true; }
            case 1:
                if( number_pressed == 3 ) { return true; }
            case 2:
                if( number_pressed == 8 ) { return true; }
            case 3:
                if( number_pressed == 4 ) { return true; }
            case 4:
                if( number_pressed == 9 ) { return true; }
        }
        return false;
    }

    /**
     * @brief Check the inputed number against the fourth index in Q table
    */
    bool checkFourthQIndex( uint8_t number_pressed ) {
        switch( checkQConditions() ) {
            case 0:
                if( number_pressed == 9 ) { return true; }
            case 1:
                if( number_pressed == 4 ) { return true; }
            case 2:
                if( number_pressed == 0 ) { return true; }
            case 3:
                if( number_pressed == 1 ) { return true; }
            case 4:
                if( number_pressed == 6 ) { return true; }
        }
        return false;
    }

    /**
     * @brief Check the input against the table P
     * 
     * @param index What index to check
     * @param number_pressed User inputed number
    */
    bool checkTableP( uint8_t index, uint8_t number_pressed ) {
        switch( index ) {
            case 1:
                return checkFirstPIndex( number_pressed );

            case 2:
                return checkSecondPIndex( number_pressed );

            case 3:
                return checkThirdPIndex( number_pressed );

            case 4:
                return checkFourthPIndex( number_pressed );
        }
    }

    /**
     * @brief Check the input against the table P
     * 
     * @param index What index to check
     * @param number_pressed User inputed number
    */
    bool checkTableQ( uint8_t index, uint8_t number_pressed ) {
        switch( index ) {
            case 1:
                return checkFirstQIndex( number_pressed );

            case 2:
                return checkSecondQIndex( number_pressed );

            case 3:
                return checkThirdQIndex( number_pressed );

            case 4:
                return checkFourthQIndex( number_pressed );
        }
    }

    /**
     * @brief return what index to follow according to the E table
     * 
     * @param tone Which tone to check for ( 1 to 4 )
    */
    uint8_t getEIndex( uint8_t tone ) {
        switch(tones[tone-1]) {
            case 0:
                return 3;
            case 1:
                return 1;
            case 2:
                return 4;
            case 3:
                return 2;
        }
    }

    /**
     * @brief return what index to follow according to the F table
     * 
     * @param tone Which tone to check for ( 1 to 4 )
    */
    uint8_t getFIndex( uint8_t tone ) {
        switch(tones[tone-1]) {
            case 0:
                return 3;
            case 1:
                return 2;
            case 2:
                return 4;
            case 3:
                return 1;
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
                return checkTableB(1, x);
            case 3:
                return checkTableA(4, x);
            case 4:
                return checkTableB(2, x);
            case 5:
                uint8_t i = getEIndex(2);
                if( i == 1 || i == 4 ) {
                    return checkTableP(i, x);
                }
                else {
                    return checkTableQ(i ,x);
                }
            case 6:
                uint8_t i = getFIndex(4);
                if( i == 3 || i == 2 ) {
                    return checkTableP(i, x);
                }
                else {
                    return checkTableQ(i ,x);
                }
            case 7:
                uint8_t i = getFIndex(3);
                if( i == 3 || i == 2 ) {
                    return checkTableP(i, x);
                }
                else {
                    return checkTableQ(i ,x);
                }
            case 8:
                uint8_t i = getEIndex(1);
                if( i == 1 || i == 4 ) {
                    return checkTableP(i, x);
                }
                else {
                    return checkTableQ(i ,x);
                }
            case 9:
                uint8_t i = getFIndex(2);
                if( i == 3 || i == 2 ) {
                    return checkTableP(i, x);
                }
                else {
                    return checkTableQ(i ,x);
                }
            case 0:
                uint8_t i = getEIndex(4);
                if( i == 1 || i == 4 ) {
                    return checkTableP(i, x);
                }
                else {
                    return checkTableQ(i ,x);
                }
        }
        return false;
    }

    virtual void react( Update const & ) {};

    /* Keypad */
    virtual void react( KeypadZeroPressed const & ) {}
    virtual void react( KeypadOnePressed const & ) {}
    virtual void react( KeypadTwoPressed const & ) {}
    virtual void react( KeypadThreePressed const & ) {}
    virtual void react( KeypadFourPressed const & ) {}
    virtual void react( KeypadFivePressed const & ) {}
    virtual void react( KeypadSixPressed const & ) {}
    virtual void react( KeypadSevenPressed const & ) {}
    virtual void react( KeypadEightPressed const & ) {}
    virtual void react( KeypadNinePressed const & ) {}

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
        clearSequence();
        if( checkNumber(0) ) {
            transit<CompletedDiscrete>();
        }
        else {
            transit<MistakeDiscrete>();
        }
    }

    void react( KeypadOnePressed const & ) override {
        clearSequence();
        if( checkNumber(1) ) {
            transit<CompletedDiscrete>();
        }
        else {
            transit<MistakeDiscrete>();
        }
    }

    void react( KeypadTwoPressed const & ) override {
        clearSequence();
        if( checkNumber(2) ) {
            transit<CompletedDiscrete>();
        }
        else {
            transit<MistakeDiscrete>();
        }
    }

    void react( KeypadThreePressed const & ) override {
        clearSequence();
        if( checkNumber(3) ) {
            transit<CompletedDiscrete>();
        }
        else {
            transit<MistakeDiscrete>();
        }
    }

    void react( KeypadFourPressed const & ) override {
        clearSequence();
        if( checkNumber(4) ) {
            transit<CompletedDiscrete>();
        }
        else {
            transit<MistakeDiscrete>();
        }
    }

    void react( KeypadFivePressed const & ) override {
        clearSequence();
        if( checkNumber(5) ) {
            transit<CompletedDiscrete>();
        }
        else {
            transit<MistakeDiscrete>();
        }
    }

    void react( KeypadSixPressed const & ) override {
        clearSequence();
        if( checkNumber(6) ) {
            transit<CompletedDiscrete>();
        }
        else {
            transit<MistakeDiscrete>();
        }
    }

    void react( KeypadSevenPressed const & ) override {
        clearSequence();
        if( checkNumber(7) ) {
            transit<CompletedDiscrete>();
        }
        else {
            transit<MistakeDiscrete>();
        }
    }

    void react( KeypadEightPressed const & ) override {
        clearSequence();
        if( checkNumber(8) ) {
            transit<CompletedDiscrete>();
        }
        else {
            transit<MistakeDiscrete>();
        }
    }

    void react( KeypadNinePressed const & ) override {
        clearSequence();
        if( checkNumber(9) ) {
            transit<CompletedDiscrete>();
        }
        else {
            transit<MistakeDiscrete>();
        }
    }
};


/**
 * @brief The player has made a mistake
*/
class MistakeDiscrete : public Discrete {
public:
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
            transit<PlayDiscrete>();
        }

    }

    void entry() {
        bomb_beep = false;
        game_countdown_amount -= 30000;  // penalize the mistake -30s
        tone(BUZZER_1, 200, 300);
        
        drawCross();
        start_millis = millis();
    }

    void exit() {
        bomb_beep = true;
        hidden = false;
    }

private:
    uint32_t start_millis = 0;
    const uint32_t restart_delay = 500;
    const uint32_t hide_delay = 300;
    bool hidden = false;
};


/**
 * @brief Discrete has been completed
*/
class CompletedDiscrete : public Discrete {
public:
    /* Give a little time for the bomb to recover from the delays 
       before marking the task as completed */
    void entry() {
        start_millis = millis();
        cleared = false;

        /* Display a tick */
        canvas.drawLine(0, 4, 2, 6, CRGB::Green);
        canvas.drawLine(3, 5, 7, 1, CRGB::Green);
        FastLED.show();
        tone(BUZZER_1, 1000, 200);
    }

    void react( Update const & ) override {
        if( millis() > start_millis + complete_timeout ) {
            task_completed = true;
        }
        if(millis() > start_millis + show_timeout && !cleared ) {
            canvas.fillScreen(CRGB::Black);
            FastLED.show();
            cleared = true;
        }
    }

private:
    uint32_t start_millis = 0;
    const uint32_t complete_timeout = 600;
    const uint32_t show_timeout = 300;
    bool cleared = false;
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

#pragma once
#include <Arduino.h>
#include <tinyfsm.hpp>

#include "game/events.h"
#include "components/adkeyboard.h"
#include "components/joystick.h"
#include "components/relays.h"
#include "components/matrix.h"
#include "components/lcd.h"
#include "components/keypad.h"
#include "components/buzzer.h"

/**
 * @file State machine implementation of game one
*/


class TestGame : public tinyfsm::Fsm<TestGame> {
public:
    void clearTests() {
        tone(BUZZER_2, 400, 20);

        fill_solid(canvas.m_LED, NUM_LEDS, CRGB::Black);
        FastLED.show();

        setRelays(0, 0, 0, 0);

        matrix = false;
        relays = false;
    }

    /* General update event */
    void react( Update const & ) {};

    /* Keypad */
    void react( KeypadPressed const & ) {};
    void react( KeypadZeroPressed const & ) {};
    void react( KeypadOnePressed const & ) {
        rtttl::begin(BUZZER_1, test_mario);
    };
    void react( KeypadTwoPressed const & ) {
        tone(BUZZER_2, 1000, 100);

        if( !matrix ) {
            fill_solid(canvas.m_LED, NUM_LEDS, CRGB::Green);
            canvas.m_LED[0] = CRGB::Red;
            FastLED.show();

            matrix = true;
        }
        else {
            fill_solid(canvas.m_LED, NUM_LEDS, CRGB::Black);
            FastLED.show();

            matrix = false;
        }
    };
    void react( KeypadThreePressed const & ) {
        if( !relays ) {
            setRelays(1, 1, 1, 1);
            relays = true;
        }
        else {
            setRelays(0,0,0,0);
            relays = false;
        }
    };
    void react( KeypadFourPressed const & ) {};
    void react( KeypadFivePressed const & ) {};
    void react( KeypadSixPressed const & ) {};
    void react( KeypadSevenPressed const & ) {};
    void react( KeypadEightPressed const & ) {};
    void react( KeypadNinePressed const & ) {};

    void react( KeypadMatched const & ) {
        clearTests();
    };
    void react( KeypadNotMatched const & ) {
        clearTests();
    };
    void react( KeypadCleared const & ) {
        clearTests();
    };
    void react( KeypadOverflowed const & ) {
        rtttl::begin(BUZZER_2, test_overflow);
    }

    /* Emergency button */
    void react( EmergencyPressed const & ) {
        resetDisplay();
        tone(BUZZER_2, 200, 200);
        lcd.print("Emergency press!");
    }
    void react( EmergencyReleased const & ) {
        resetDisplay();
        tone(BUZZER_2, 800, 200);
        lcd.print("Emergency freed!");
    }

    /* Potenciometers */
    void react( Potenciometer1Moved const & e ) {
        resetDisplay();
        tone(BUZZER_2, 60, 10);

        lcd.print("Pot1 moved");
        lcd.setCursor(0,1);
        lcd.print("amount: ");
        lcd.print(e.current_amount);
    }

    void react( Potenciometer2Moved const & e ) {
        resetDisplay();
        tone(BUZZER_2, 60, 10);

        lcd.print("Pot2 moved");
        lcd.setCursor(0,1);
        lcd.print("amount: ");
        lcd.print(e.current_amount);
    };

    void react( Potenciometer3Moved const & e ) {
        resetDisplay();
        tone(BUZZER_2, 60, 10);

        lcd.print("Pot3 moved");
        lcd.setCursor(0,1);
        lcd.print("amount: ");
        lcd.print(e.current_amount);
    };

    /* Joystick */
    void react( JoystickMoved const & e ) {
        resetDisplay();
        tone(BUZZER_1, 50, 10);

        lcd.print("Joystick moved");
        lcd.setCursor(0,1);
        lcd.print("x: ");
        lcd.print(e.x);
        lcd.print(", y: ");
        lcd.print(e.y);
    }
    void react( JoystickPressed const & ) {};
    void react( JoystickReleased const & ) {};
    
    /* ADKeyboard */
    void react( ADKeyboardPressed const & ) {};
    void react( ADKeyboardLeftPressed const & ) {};
    void react( ADKeyboardRightPressed const & ) {};
    void react( ADKeyboardUpPressed const & ) {};
    void react( ADKeyboardDownPressed const & ) {};
    void react( ADKeyboardEnterPressed const & ) {};
    void react( ADKeyboardLeftReleased const & ) {};
    void react( ADKeyboardRightReleased const & ) {};
    void react( ADKeyboardUpReleased const & ) {};
    void react( ADKeyboardDownReleased const & ) {};
    void react( ADKeyboardEnterReleased const & ) {};

    /* Actions on entering/exiting a state */
    void entry() {};
    void exit() {};

    bool matrix = false;
    bool relays = false;
};

class UndefinedState : public TestGame {
public:

};

FSM_INITIAL_STATE(TestGame, UndefinedState);

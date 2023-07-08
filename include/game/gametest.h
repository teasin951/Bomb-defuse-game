#pragma once
#include <Arduino.h>
#include <tinyfsm.hpp>

#include "game/events.h"
#include "components/adkeyboard.h"
#include "components/joystick.h"
#include "components/relays.h"
#include "components/lcd.h"
#include "components/keypad.h"
#include "components/buzzer.h"
#include "components/button.h"

#include "components/matrix/movingarrowup.h"
#include "components/matrix/movingarrowleft.h"
#include "components/matrix/movingarrowright.h"
#include "components/matrix/movingarrowdown.h"



/**
 * @file State machine implementation of game one
*/


class TestGame : public tinyfsm::Fsm<TestGame> {
public:
    void clearTests() {
        tone(BUZZER_2, 400, 20);

        display_up = false;
        display_down = false;
        display_right = false;
        display_left = false;
        fill_solid(canvas.m_LED, NUM_LEDS, CRGB::Black);
        FastLED.show();

        setRelays(0, 0, 0, 0);

        matrix = false;
        relays = false;

        rtttl::stop();
    }

    void clearMatrix() {
        stopOthersDisplaying();
        canvas.fillScreen(CRGB::Black);
        FastLED.show();
    }

    /* General update event */
    void react( Update const & ) {
        if( display_up ) {
            moving_arrow_up.proceed();
        }
        else if( display_left ) {
            moving_arrow_left.proceed();
        }
        else if( display_right ) {
            moving_arrow_right.proceed();
        }
        else if( display_down ) {
            moving_arrow_down.proceed();
        }

    };

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
    void react( KeypadFourPressed const & ) {
        clearMatrix();

        CRGB terminal_colour = CRGB::Amethyst;

        canvas.drawPixel(0, 0, terminal_colour);
        canvas.drawPixel(0, 3, terminal_colour);
        canvas.drawPixel(0, 6, terminal_colour);
        canvas.drawPixel(7, 0, terminal_colour);
        canvas.drawPixel(7, 3, terminal_colour);
        canvas.drawPixel(7, 6, terminal_colour);

        canvas.drawLine(1, 0, 6, 6, CRGB::Yellow);
        canvas.drawLine(1, 3, 6, 6, CRGB::Blue);
        canvas.drawLine(1, 6, 6, 0, CRGB::Red);

        FastLED.show();
    };
    void react( KeypadFivePressed const & ) {
        clearMatrix();

        CRGB terminal_colour = CRGB::Amethyst;

        canvas.drawPixel(0, 0, terminal_colour);
        canvas.drawPixel(0, 3, terminal_colour);
        canvas.drawPixel(0, 6, terminal_colour);
        canvas.drawPixel(7, 0, terminal_colour);
        canvas.drawPixel(7, 3, terminal_colour);
        canvas.drawPixel(7, 6, terminal_colour);

        canvas.drawLine(1, 0, 6, 6, CRGB::Yellow);
        // canvas.drawLine(1, 3, 6, 6, CRGB::Blue);
        canvas.drawPixel(1, 3, CRGB::Blue);
        canvas.drawPixel(6, 6, CRGB::Blue);
        canvas.drawLine(1, 6, 6, 0, CRGB::Red);

        FastLED.show();
    };
    void react( KeypadSixPressed const & ) {
        clearMatrix();

        CRGB terminal_colour = CRGB::Amethyst;

        canvas.drawPixel(0, 0, terminal_colour);
        canvas.drawPixel(0, 3, terminal_colour);
        canvas.drawPixel(0, 6, terminal_colour);
        canvas.drawPixel(7, 0, terminal_colour);
        canvas.drawPixel(7, 3, terminal_colour);
        canvas.drawPixel(7, 6, terminal_colour);

        // canvas.drawLine(1, 0, 6, 6, CRGB::Yellow);
        canvas.drawPixel(1, 0, CRGB::Yellow);
        canvas.drawPixel(6, 6, CRGB::Yellow);
        canvas.drawLine(1, 3, 6, 6, CRGB::Blue);
        canvas.drawLine(1, 6, 6, 0, CRGB::Red);

        FastLED.show();
    }

    void react( KeypadSevenPressed const & ) {
        canvas.fillTriangle(0, 5, 6, 5, 3, 2, CRGB::Red);
        FastLED.show();
    }

    void react( KeypadEightPressed const & ) {
        canvas.fillCircle(3, 3, 2, CRGB::Blue);
        FastLED.show();
    };
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
    void react( JoystickPressed const & ) {
        tone(BUZZER_2, 150, 200);
        lcd.setBacklight(false);
    };
    void react( JoystickReleased const & ) {};
    
    /* ADKeyboard */
    void stopOthersDisplaying() {        
        display_up = false;
        display_down = false;
        display_right = false;
        display_left = false;

    }

    void react( ADKeyboardPressed const & ) {};
    void react( ADKeyboardLeftPressed const & ) {
        stopOthersDisplaying();
        tone(BUZZER_1, 400, 100);
        moving_arrow_left.setAnimation();
        display_left = true;
    };
    void react( ADKeyboardLeftReleased const & ) {
        clearMatrix();
    };

    void react( ADKeyboardRightPressed const & ) {
        stopOthersDisplaying();
        tone(BUZZER_1, 400, 100);
        moving_arrow_right.setAnimation();
        display_right = true;
    };
    void react( ADKeyboardRightReleased const & ) {
        clearMatrix();
    };

    void react( ADKeyboardUpPressed const & ) {
        stopOthersDisplaying();
        tone(BUZZER_1, 400, 100);
        moving_arrow_up.setAnimation();
        display_up = true;
    }
    void react( ADKeyboardUpReleased const & ) {
        clearMatrix();
    }

    void react( ADKeyboardDownPressed const & ) {
        stopOthersDisplaying();
        tone(BUZZER_1, 400, 100);
        moving_arrow_down.setAnimation();
        display_down = true;
    }
    void react( ADKeyboardDownReleased const & ) {
        clearMatrix();
    }

    void react( ADKeyboardEnterPressed const & ) {
        setButtonLEDs(255, 0, 255);
    };
    void react( ADKeyboardEnterReleased const & ) {
        setButtonLEDs(0, 0, 0);
    };

    /* Actions on entering/exiting a state */
    void entry() {};
    void exit() {};

    bool matrix = false;
    bool relays = false;

    bool display_up = false;
    bool display_down = false;
    bool display_right = false;
    bool display_left = false;
};

class UndefinedState : public TestGame {
public:

};

FSM_INITIAL_STATE(TestGame, UndefinedState);

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


uint8_t maze_difficulty = 1; // Game should change this, 1 - easy, 2 - medium, 3 - hard
uint8_t maze_number = 0;


/* Forward state declaration */
class InitMaze;
class PlayMaze;
class MistakeMaze;
class CompletedMaze;


class Maze : public tinyfsm::Fsm<Maze> {
public:

    // Would love to seperate to .cpp but it stops working
    void drawMaze() {
        canvas.fillScreen(CRGB::Black);

        switch(maze_number) {
            case 1:
                canvas.drawPixel(0, 0, CRGB::Red);
                canvas.drawPixel(7, 7, CRGB::Red);
                break;
            case 2:
                canvas.drawPixel(7, 0, CRGB::Red);
                break;
            case 3:
                canvas.drawPixel(7, 0, CRGB::Red);
                canvas.drawPixel(7, 7, CRGB::Red);
                canvas.drawPixel(0, 7, CRGB::Red);
                break;
            case 4:
                canvas.drawPixel(0, 7, CRGB::Red);
                break;
            case 5:
                canvas.drawPixel(0, 7, CRGB::Red);
                canvas.drawPixel(0, 0, CRGB::Red);
                break;
            case 6:
                canvas.drawPixel(0, 0, CRGB::Red);
                break;
            case 7:
                canvas.drawPixel(0, 0, CRGB::Red);
                canvas.drawPixel(0, 7, CRGB::Red);
                canvas.drawPixel(7, 7, CRGB::Red);
                break;
            case 8:
                canvas.drawPixel(0, 0, CRGB::Red);
                canvas.drawPixel(7, 0, CRGB::Red);
                canvas.drawPixel(0, 7, CRGB::Red);
                canvas.drawPixel(7, 7, CRGB::Red);
                break;
            case 9:
                canvas.drawPixel(7, 7, CRGB::Red);
                break;
        }
    }

    void checkMaze() {
        switch(maze_number) {
            case 1:
                checkMaze1();
                break;
            case 2:
                checkMaze2();
                break;
            case 3:
                checkMaze3();
                break;
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
        }
    }

    /**
     * Each bracket defines boundries of a coridor
    */
    void checkMaze1() {
        if( !(
            ( joystick.x > 510 && joystick.y < 640 && joystick.y > 510 ) ||
            ( joystick.x > 895 && joystick.y > 510 && joystick.y < 896 ) ||
            ( joystick.x > 510 && joystick.y < 896 && joystick.y > 767 )
        ) ) {
            transit<MistakeMaze>();
        }

        else if( joystick.x > 510 && joystick.x < 640 && joystick.y < 896 && joystick.y > 767 ) {
            transit<CompletedMaze>();
        }
    }

    void checkMaze2() {
        // Serial.print( joystick.x );
        // Serial.print( ": ");
        // Serial.print( map(joystick.x - 126, 898, 0, 0, 7) );
        // Serial.print( ", " );
        // Serial.print( joystick.y );
        // Serial.print( ": ");
        // Serial.println( map(joystick.y - 126, 898, 0, 0, 7) );

        if( !(
            ( joystick.x < 768 && joystick.x > 510 && joystick.y < 640 && joystick.y > 510 ) ||
            ( joystick.x < 768 && joystick.x > 639 && joystick.y > 510 ) ||
            ( joystick.x < 768 && joystick.x > 254 && joystick.y > 895 ) ||
            ( joystick.x < 383 && joystick.x > 254 && joystick.y > 382 )
        ) ) {
            transit<MistakeMaze>();
        }

        else if( joystick.x < 383 && joystick.x > 254 && joystick.y < 511 && joystick.y > 382 ) {
            transit<CompletedMaze>();
        }
    }

    void checkMaze3() {
        if( !(
            ( joystick.x < 640 && joystick.y < 640 && joystick.y > 510 ) || 
            ( joystick.x < 127 && joystick.y < 640 && joystick.y > 254 ) || 
            ( joystick.x < 383 && joystick.y < 383 && joystick.y > 254 ) || 
            ( joystick.x < 383 && joystick.x > 254 && joystick.y < 383 ) ||
            ( joystick.x < 640 && joystick.x > 254 && joystick.y < 127 ) ||
            ( joystick.x < 640 && joystick.x > 510 && joystick.y < 383 ) ||
            ( joystick.x < 768 && joystick.x > 510 && joystick.y < 383 && joystick.y > 254 )
        ) ) {
            transit<MistakeMaze>();
        }

        else if( joystick.x < 768 && joystick.x > 639 && joystick.y < 383 && joystick.y > 254 ) {
            transit<CompletedMaze>();
        }
    }

    void checkMaze4() {
        if( !(
            ( joystick.x < 768 && joystick.x > 510 && joystick.y < 640 && joystick.y > 510 ) || 
            ( joystick.x < 768 && joystick.x > 639 && joystick.y < 640 && joystick.y > 254 ) ||
            ( joystick.x < 768 && joystick.x > 254 && joystick.y < 383 && joystick.y > 254 ) ||
            ( joystick.x < 383 && joystick.x > 254 && joystick.y < 768 && joystick.y > 254 ) || 
            ( joystick.x < 383 && joystick.x > 126 && joystick.y < 768 && joystick.y > 639 )
        ) ) {
            transit<MistakeMaze>();
        }

        else if( joystick.x < 255 && joystick.x > 126 && joystick.y < 768 && joystick.y > 639 ) {
            transit<CompletedMaze>();
        }
    }

    void displayPlayer() {
        drawMaze();
        /* https://www.geogebra.org/calculator/pfzc5w4c */
        canvas.drawPixel( map(joystick.x - 126, 898, 0, 0, 7), map(joystick.y - 126, 898, 0, 0, 7), CRGB::Blue);
        FastLED.show();
    }

    /* General update event */
    virtual void react( Update const & ) {}

    void react( tinyfsm::Event const & ) {};

    /* Joystick */
    virtual void react( JoystickMoved const & ) {};
    
    /* Actions on entering/exiting a state */
    virtual void entry() {};
    virtual void exit() {};
};


/**
 * @brief The player is trying to go through the maze
*/
class PlayMaze : public Maze {
public:
    void entry() {
        displayPlayer();
    }

    void react( JoystickMoved const & ) {
        displayPlayer();
        checkMaze4();
    }

};


/**
 * @brief The player has made a mistake
*/
class MistakeMaze : public Maze {
public:
    void entry() override {
        bomb_beep = false;
        game_countdown_amount -= 15000;
    }

    void react( Update const & ) {
        if( !rtttl::isPlaying() ) {
            rtttl::begin(BUZZER_1, fail_waiting);
        }
    }

    void react( JoystickMoved const & ) {
        displayPlayer();
        if( joystick.x < 640 && joystick.x > 510 && joystick.y < 640 && joystick.y > 510 ) {
            transit<PlayMaze>();
        }
    }

    void exit() {
        bomb_beep = true;
        tone(BUZZER_1, 800, 100);
    }
};


/**
 * @brief Maze has been completed
*/
class CompletedMaze : public Maze {
public:
    void entry() {
        clearMatrix();
        setRelays(0,0,0,0);
        rtttl::begin(BUZZER_1, task_finished);
        start_millis = millis();
    }

    void react( Update const & ) {
        if( millis() - start_millis > finish_delay ) {
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
class InitMaze : public Maze {
public:
    void entry() {
        // Set the stage for Maze
        setRelays(0,1,1,1);
        clearMatrix();

        // decide what maze it will be based on difficulty
        maze_number = random(1, maze_difficulty*3 + 1);
    }

    void react( Update const & ) {
        transit<PlayMaze>();
    }
};


FSM_INITIAL_STATE(Maze, InitMaze);

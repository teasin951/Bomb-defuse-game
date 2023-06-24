#pragma once
#include <Arduino.h>
#include "game.h"

/**
 * @file Everything needed for joystick
*/

/**
 * @brief Joystick state struct
*/
struct Joystick {
    uint8_t button = ButtonState::RELEASED;
    int16_t x = 0;
    int16_t y = 0;
};
typedef struct Joystick Joystick;


/**
 * @brief Read joystick state
 * 
 * Pins are expected to be set up, use pins.h
 * 
 * @param joy Joystick struct holding all the information
 * @param p_button Pin where the joystick button is connected
 * @param p_x Pin where the x axes is connected (analog)
 * @param p_y Pin where the y axes is connected (analog)
*/
Joystick & readJoystick( Joystick & joy, int p_button, int p_x, int p_y ) {
    if( digitalRead(p_button) == HIGH ) 
        joy.button = ButtonState::PRESSED;
    else
        joy.button = ButtonState::RELEASED;

    joy.x = analogRead(p_x);
    joy.y = analogRead(p_y);
}

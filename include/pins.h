#include <Arduino.h>

/**
 * @file definitions of pins and their setup
*/

#define ADKEYBOARD A1

#define JOYSTICK_SW A2
#define JOYSTICK_Y A3
#define JOYSTICK_X A4



/**
 * @brief Set all pins to their respective modes
 * 
 * You need to set the corrent amount of pins and list them accordingly
*/
void pinSetup() {
    const int INPIN = 4;
    const int OUTPIN = 0;

    int input_pin[INPIN] = { ADKEYBOARD, JOYSTICK_SW, JOYSTICK_X, JOYSTICK_Y };  // fill input pins!!
    int output_pin[OUTPIN] = { };  // fill output pins!!

    // set pins
    for( int i = 0; i < INPIN; i++ ) {
        pinMode(input_pin[i], INPUT);
    }

    for( int i = 0; i < OUTPIN; i++ ) {
        pinMode(output_pin[i], OUTPUT);
    }
}
#pragma once
#include <Arduino.h>

/**
 * @file definitions of pins and their setup
*/

#define ADKEYBOARD A1

#define JOYSTICK_SW A2
#define JOYSTICK_Y A3
#define JOYSTICK_X A4

#define RELAY_1 28
#define RELAY_2 29
#define RELAY_3 30
#define RELAY_4 31

#define BUTTON_IN 22
#define BUTTON_R 11
#define BUTTON_G 12
#define BUTTON_B 13

#define BUZZER_1 9
#define BUZZER_2 10


/**
 * @brief Set all pins to their respective modes
 * 
 * You need to set the corrent amount of pins and list them accordingly
*/
void pinSetup() {
    const int INPIN = 5;
    const int OUTPIN = 9;

    int input_pin[INPIN] = { ADKEYBOARD, JOYSTICK_SW, JOYSTICK_X, JOYSTICK_Y, BUTTON_IN };  // fill input pins!!
    int output_pin[OUTPIN] = { RELAY_1, RELAY_2, RELAY_3, RELAY_4, BUTTON_R, BUTTON_G, BUTTON_B, BUZZER_1, BUZZER_2 };  // fill output pins!!

    // set pins
    for( int i = 0; i < INPIN; i++ ) {
        pinMode(input_pin[i], INPUT);
    }

    for( int i = 0; i < OUTPIN; i++ ) {
        pinMode(output_pin[i], OUTPUT);
    }

    digitalWrite(RELAY_1, HIGH);
    digitalWrite(RELAY_2, HIGH);
    digitalWrite(RELAY_3, HIGH);
    digitalWrite(RELAY_4, HIGH);
}
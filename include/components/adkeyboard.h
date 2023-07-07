#pragma once
#include <Arduino.h>
#include <Keypad.h>

#include "game.h"
#include "pins.h"

/**
 * @file Handeling of ADKeyboard
 * 
 * Only one adkeaboard can be used currently :)
*/

/**
 * @brief ADKeypad state
*/
struct Keyboard {
    uint8_t left = RELEASED;
    uint8_t right = RELEASED;
    uint8_t up = RELEASED;
    uint8_t down = RELEASED;
    uint8_t enter = RELEASED;
};

/* 
   These are global 
   as you can't pass arguments to the functions below 
*/
struct Keyboard adkeyboard;  

uint16_t lastDebounceMillis = 0;
const uint16_t debounceDelay = 50;

/* 
 * To prevent ex. left button release
 * trigger right button due to parasitic capacitance 
 */
uint8_t button_pressed = 0;  /**< A button was down last reading 0 - nothing, 1 - left, ...*/

/**
 * To decrease the likelyhood of sampeling before a button pulls the value low enough
 * Used to take two debounced samples before calling the click function
*/
uint8_t button_read = 0;  /**< A button was down last reading 0 - nothing, 1 - left, ...*/

  
void leftButtonClick() {
    adkeyboard.left = PRESSED;
    button_pressed = 1;
}  
  
void leftButtonHold() {
    adkeyboard.left = HOLD;
    button_pressed = 1;
}  
  
void rightButtonClick() {
    adkeyboard.right = PRESSED;
    button_pressed = 2;
}  
  
void rightButtonHold() {
    adkeyboard.right = HOLD;
    button_pressed = 2;
}  
  
void upButtonClick() {
    adkeyboard.up = PRESSED;
    button_pressed = 3;
}  
  
void upButtonHold() {
    adkeyboard.up = HOLD;
    button_pressed = 3;
}  
  
void downButtonClick() {
    adkeyboard.down = PRESSED;
    button_pressed = 4;
}  
  
void downButtonHold() {
    adkeyboard.down = HOLD;
    button_pressed = 4;
}  
  
void enterButtonClick() {
    adkeyboard.enter = PRESSED;
    button_pressed = 5;
}  
  
void enterButtonHold() {
    adkeyboard.enter = HOLD;
    button_pressed = 5;
}  
  
void buttonRelease() {
    adkeyboard.left = RELEASED;
    adkeyboard.right = RELEASED;
    adkeyboard.up = RELEASED;
    adkeyboard.down = RELEASED;
    adkeyboard.enter = RELEASED;

    button_pressed = 0;
}     
   
/**
 * @brief read ADKeaboard, call periodically
*/
void readADKeyboard() {
    /* Debounce */
    if( millis() - lastDebounceMillis > debounceDelay ) {

        uint16_t value = analogRead(ADKEYBOARD);

        /* enter button */
        if( 635 < value && value <= 900 && ( button_pressed == 0 || button_pressed == 5 ) ) {
            if( adkeyboard.enter == RELEASED ) {
                if( button_read == 5 ) {
                    enterButtonClick();
                }
                else {
                    button_read = 5;
                }
                lastDebounceMillis = millis();
            }
        }

        /* right button */
        else if( 400 < value && value <= 635 && ( button_pressed == 0 || button_pressed == 2 ) ) {
            if( adkeyboard.right == RELEASED ) {
                if( button_read == 2 ) {
                    rightButtonClick();
                }
                else {
                    button_read = 2;
                }
                lastDebounceMillis = millis();
            }
        }

        /* down button */
        else if( 230 < value && value <= 400 && ( button_pressed == 0 || button_pressed == 4 ) ) {
            if( adkeyboard.down == RELEASED ) {
                if( button_read == 4 ) {
                    downButtonClick();
                }
                else {
                    button_read = 4;
                }
                lastDebounceMillis = millis();
            }
        }

        /* up button */
        else if( 75 < value && value <= 230 && ( button_pressed == 0 || button_pressed == 3 ) ) {
            if( adkeyboard.up == RELEASED ) {
                if( button_read == 3 ) {
                    upButtonClick();
                }
                else {
                    button_read = 3;
                }
                lastDebounceMillis = millis();
            }
        }

        /* left button */
        else if( value <= 75 && ( button_pressed == 0 || button_pressed == 1 ) ) {
            if( adkeyboard.left == RELEASED ) {
                if( button_read == 1 ) {
                    leftButtonClick();
                }
                else {
                    button_read = 1;
                }
                lastDebounceMillis = millis();
            }
        }

        else if( 900 < value && !(button_pressed == 0) ) {
            if( button_read == 0 ) {
                buttonRelease();
            }
            else {
                button_read = 0;
            }
            lastDebounceMillis = millis();
        }
    }
}

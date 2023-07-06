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
uint16_t debounceDelay = 50;

  
void leftButtonClick() {
    adkeyboard.left = PRESSED;
}  
  
void leftButtonHold() {
    adkeyboard.left = HOLD;
}  
  
void rightButtonClick() {
    adkeyboard.right = PRESSED;
}  
  
void rightButtonHold() {
    adkeyboard.right = HOLD;
}  
  
void upButtonClick() {
    adkeyboard.up = PRESSED;
}  
  
void upButtonHold() {
    adkeyboard.up = HOLD;
}  
  
void downButtonClick() {
    adkeyboard.down = PRESSED;
}  
  
void downButtonHold() {
    adkeyboard.down = HOLD;
}  
  
void enterButtonClick() {
    adkeyboard.enter = PRESSED;
}  
  
void enterButtonHold() {
    adkeyboard.enter = HOLD;
}  
  
void buttonRelease() {
    adkeyboard.left = RELEASED;
    adkeyboard.right = RELEASED;
    adkeyboard.up = RELEASED;
    adkeyboard.down = RELEASED;
    adkeyboard.enter = RELEASED;
}     
   
/**
 * @brief read ADKeaboard, call periodically
*/
void readADKeyboard() {
    /* Debounce */
    if( millis() - lastDebounceMillis > debounceDelay ) {

        uint16_t value = analogRead(ADKEYBOARD);

        /* left button */
        if( value < 20 ) {
            if( adkeyboard.left == RELEASED ) {
                leftButtonClick();
                lastDebounceMillis = millis();
            }
        }
        
        /* right button */
        else if( 485 < value && value < 500 ) {
            if( adkeyboard.right == RELEASED ) {
                rightButtonClick();
                lastDebounceMillis = millis();
            }
        }

        /* up button */
        else if( 140 < value && value < 160 ) {
            if( adkeyboard.up == RELEASED ) {
                upButtonClick();
                lastDebounceMillis = millis();
            }
        }

        /* down button */
        else if( 295 < value && value < 325 ) {
            if( adkeyboard.down == RELEASED ) {
                downButtonClick();
                lastDebounceMillis = millis();
            }
        }

        /* enter button */
        else if( 775 < value && value < 800 ) {
            if( adkeyboard.enter == RELEASED ) {
                enterButtonClick();
                lastDebounceMillis = millis();
            }
        }

        else {
            buttonRelease();
        }
    }
}

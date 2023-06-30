#pragma once
#include <Arduino.h>
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
    uint8_t left = ButtonState::RELEASED;
    uint8_t right = ButtonState::RELEASED;
    uint8_t up = ButtonState::RELEASED;
    uint8_t down = ButtonState::RELEASED;
    uint8_t enter = ButtonState::RELEASED;
};

/* 
   These are global 
   as you can't pass arguments to the functions below 
*/
struct Keyboard adkeyboard;  

  
void leftButtonClick() {
    adkeyboard.left = ButtonState::PRESSED;
}  
  
void leftButtonHold() {
    adkeyboard.left = ButtonState::HELD;
}  
  
void rightButtonClick() {
    adkeyboard.right = ButtonState::PRESSED;
}  
  
void rightButtonHold() {
    adkeyboard.right = ButtonState::HELD;
}  
  
void upButtonClick() {
    adkeyboard.up = ButtonState::PRESSED;
}  
  
void upButtonHold() {
    adkeyboard.up = ButtonState::HELD;
}  
  
void downButtonClick() {
    adkeyboard.down = ButtonState::PRESSED;
}  
  
void downButtonHold() {
    adkeyboard.down = ButtonState::HELD;
}  
  
void enterButtonClick() {
    adkeyboard.enter = ButtonState::PRESSED;
}  
  
void enterButtonHold() {
    adkeyboard.enter = ButtonState::HELD;
}  
  
void buttonRelease() {
    adkeyboard.left = ButtonState::RELEASED;
    adkeyboard.right = ButtonState::RELEASED;
    adkeyboard.up = ButtonState::RELEASED;
    adkeyboard.down = ButtonState::RELEASED;
    adkeyboard.enter = ButtonState::RELEASED;
}     
   
/**
 * @brief read ADKeaboard, call periodically
*/
void readADKeyboard() {
    uint16_t value = analogRead(ADKEYBOARD);

    /* left button */
    if( value < 20 ) {
        if( adkeyboard.left == ButtonState::RELEASED ) {
            leftButtonClick();
        }
    }
    
    /* right button */
    else if( 485 < value && value < 500 ) {
        if( adkeyboard.right == ButtonState::RELEASED ) {
            rightButtonClick();
        }
    }

    /* up button */
    else if( 140 < value && value < 160 ) {
        if( adkeyboard.up == ButtonState::RELEASED ) {
            upButtonClick();
        }
    }

    /* down button */
    else if( 295 < value && value < 325 ) {
        if( adkeyboard.down == ButtonState::RELEASED ) {
            downButtonClick();
        }
    }

    /* enter button */
    else if( 775 < value && value < 800 ) {
        if( adkeyboard.enter == ButtonState::RELEASED ) {
            enterButtonClick();
        }
    }

    else {
        buttonRelease();
    }
}

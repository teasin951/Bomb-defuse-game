#pragma once
#include <Arduino.h>
#include <Keypad.h>

#include "pins.h"

/**
 * @brief Simplify keypad handeling
 * 
 * setupKeypad() has to be called once and keypad.getKey() periodically
*/

const uint8_t ROWS = 4; //four rows
const uint8_t COLS = 3; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {KEY_FIRST_ROW, KEY_SECOND_ROW, KEY_THIRD_ROW, KEY_FORTH_ROW}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {KEY_LEFT_COL, KEY_MID_COL, KEY_RIGHT_COL}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad keypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void nada() {}  // just nothing, placeholder

// Create a struct holding keypad info to verify sequences
struct KeypadInfo {
  char sequence[16];  /**< currently typed in sequence */
  uint8_t length = 0;  /**< current number of typed in characters */

  char match_sequence[16];  /**< sequence to match */
  uint8_t match_length = 16;  /**< length of the sequence to match */

  void (*pressed)(void) = nada;  /**< pointer to a function called when a button is pressed */
  void (*matched)(void) = nada;  /**< pointer to a function called when sequences match */
  void (*noMatch)(void) = nada;  /**< pointer to a function called when sequences do not match */
  void (*clear)(void) = nada;  /**< pointer to a function called when the sequence is manually cleared */
  void (*overflow)(void) = nada;  /**< pointer to a function called when the sequence entered is too long */
};

struct KeypadInfo keypad_info;


/**
 * @brief Verifies that 'sequence' and 'match_sequence' match in 'match_length' number of characters
 * 
 * Also calls noMatch() or matched()
*/
bool verifyMatch() {
  for( uint8_t i = 0; i < keypad_info.match_length; i++ ) {
    if( !( keypad_info.sequence[i] == keypad_info.match_sequence[i] ) ) {
      keypad_info.noMatch();
      return false;
    }
  }

  keypad_info.matched();
  return true;
}

/**
 * @brief Sets 'sequence' to all spaces and length = 0
*/
void clearSequence() {
  for( uint8_t i = 0; i < 16; i++ ) {
    keypad_info.sequence[i] = ' ';
  }
  keypad_info.length = 0;
}


/**
 * @brief Event called when button is pressed, adds symbols to 'sequence'
 * 
 * @param x KeypadEvent passed from event listener of Keypad.h
*/
void eventHandler( KeypadEvent x ) {
  KeypadInfo & k = keypad_info;

  // Verify that it is a press
  if( keypad.isPressed(x) ) {

    // Enter pressed
    if( x == '#' ) {
      verifyMatch();
      clearSequence();
    }

    // Clear pressed 
    else if( x == '*' ) {
      clearSequence();
      k.clear();
    }

    // Number pressed
    else {

      // We are not at the end of the sequence yet
      if( k.length < k.match_length ) {
        k.sequence[k.length] = x;
        k.length += 1;

        k.pressed();
      }

      // We are out of space
      else {
        // Not permisive, the sequence will not be checked when overflowed
        clearSequence();
        k.overflow();
      }

    }
  }
}

/**
 * @brief Set sequence to match and functions to be called when that happends (or does not)
 * 
 * // Can be made lenght non-disclosing by setting size = 16 and filling the not used part of the sequence by ' '
 * 
 * @param match sequence that shall be matched by the user
 * @param size length of the sequence
 * @param pressed function to call when a number button is pressed and added to the sequence
 * @param s_matched function to call when the correct sequence is entered
 * @param s_did_not_match function to call when an incorrect sequence is entered
 * @param s_cleared function to call when the sequence is manually cleared
 * @param s_overflowed function to call when the user tries to enter a too long sequence
*/
void setSequence( char * match, uint8_t size, 
    void (*button_pressed)(void), void (*s_matched)(void), void (*s_did_not_match)(void), void (*s_cleared)(void), void (*s_overflowed)(void) ) {

  for( uint8_t i = 0; i < size; i++ ) {
    keypad_info.match_sequence[i] = match[i];
  }

  keypad_info.match_length = size;
  keypad_info.pressed = button_pressed;
  keypad_info.matched = s_matched;
  keypad_info.noMatch = s_did_not_match;
  keypad_info.clear = s_cleared;
  keypad_info.overflow = s_overflowed;
}


void setupKeypad() {
  keypad.addEventListener(eventHandler);
  clearSequence();
}
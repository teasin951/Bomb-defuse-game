#pragma once
#include <Arduino.h>
#include <Keypad.h>

#include "pins.h"

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

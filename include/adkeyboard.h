#pragma once
#include <Arduino.h>
#include <AnalogButtons.h>
#include "game.h"
#include "pins.h"

/**
 * @file Create ADKeyboard object and keypad struct
 * 
 * !!! ADKeyboard.check() has to be called in a loop() !!!
*/

AnalogButtons ADKeyboard(ADKEYBOARD, INPUT);
struct Keypad keypad;


void leftButtonClick() {
    keypad.left = ButtonState::PRESSED;
}

void leftButtonHold() {
    keypad.left = ButtonState::HELD;
}

void buttonRightClick() {
    keypad.right = ButtonState::PRESSED;
}

void buttonRightHold() {
    keypad.right = ButtonState::HELD;
}

void buttonUpClick() {
    keypad.up = ButtonState::PRESSED;
}

void buttonUpHold() {
    keypad.up = ButtonState::HELD;
}

void buttonDownClick() {
    keypad.down = ButtonState::PRESSED;
}

void buttonDownHold() {
    keypad.down = ButtonState::HELD;
}

void buttonEnterClick() {
    keypad.enter = ButtonState::PRESSED;
}

void buttonEnterHold() {
    keypad.enter = ButtonState::HELD;
}

void buttonRelease() {
    keypad.left = ButtonState::RELEASED;
    keypad.right = ButtonState::RELEASED;
    keypad.up = ButtonState::RELEASED;
    keypad.down = ButtonState::RELEASED;
    keypad.enter = ButtonState::RELEASED;
}

void initButtons( AnalogButtons & x ) {
    Button b_left = Button(0, &leftButtonClick, &leftButtonHold);
    Button b_right = Button(490, &buttonRightClick, &buttonRightHold);
    Button b_up = Button(145, &buttonUpClick, &buttonUpHold);
    Button b_down = Button(305, &buttonDownClick, &buttonDownHold);
    Button b_enter = Button(785, &buttonEnterClick, &buttonEnterHold);
    Button b_release = Button(1023, &buttonRelease);

    x.add(b_left);
    x.add(b_right);
    x.add(b_up);
    x.add(b_down);
    x.add(b_enter);  
}
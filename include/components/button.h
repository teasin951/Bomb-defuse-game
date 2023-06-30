#pragma once
#include <Arduino.h>
#include "pins.h"


/**
 * @brief sets the colour on the emergency button
 * 
 * @param r red rgb value
 * @param g green rgb value
 * @param b blue rgb value
*/
void setButtonLEDs( byte r, byte g, byte b ) {
    analogWrite(BUTTON_R, r);
    analogWrite(BUTTON_G, g);
    analogWrite(BUTTON_B, b);
}
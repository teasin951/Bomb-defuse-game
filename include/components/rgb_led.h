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
void setLED( byte r, byte g, byte b ) {
    analogWrite(LED_R, r);
    analogWrite(LED_G, g);
    analogWrite(LED_B, b);
}
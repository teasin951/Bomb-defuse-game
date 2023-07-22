#pragma once
#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include "pins.h"

// set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27,16,2);


/**
 * @brief Clear the LCD
*/
void resetDisplay() {
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
}
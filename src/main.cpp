#include <Arduino.h>
#include "pins.h"
#include "game.h"

#include "adkeyboard.h"
#include "joystick.h"

Joystick joystick;  /**< Create joystick struct */

void setup() {
  Serial.begin(9600);
  pinSetup();
}

void loop() {
  readADKeyboard();
  readJoystick(joystick, JOYSTICK_SW, JOYSTICK_X, JOYSTICK_Y);

  delay(50);
}

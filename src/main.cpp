#include <Arduino.h>
#include "pins.h"
#include "game.h"

#include "adkeyboard.h"
#include "joystick.h"
#include "relays.h"
#include "matrix.h"


Joystick joystick;  /**< Create joystick struct */

void setup() {
  Serial.begin(9600);
  pinSetup();
  setupFastLED();
}

void loop() {
  readADKeyboard();
  readJoystick(joystick, JOYSTICK_SW, JOYSTICK_X, JOYSTICK_Y);
  displayMatrix();

  if(adkeyboard.left == ButtonState::PRESSED ) {
    tone(BUZZER_1, 400, 50);
  }

  delay(50);
}
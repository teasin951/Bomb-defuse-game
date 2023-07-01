#include <Arduino.h>
#include "components/pins.h"
#include "game.h"

#include "components/adkeyboard.h"
#include "components/joystick.h"
#include "components/relays.h"
#include "components/matrix.h"


Joystick joystick;  /**< Create joystick struct */

int j = 0;

void setup() {
  Serial.begin(9600);
  pinSetup();
  setupFastLED();

}

void loop() {
  readADKeyboard();
  readJoystick(joystick, JOYSTICK_SW, JOYSTICK_X, JOYSTICK_Y);

  delay(50);
}
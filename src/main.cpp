#include <Arduino.h>
#include "components/pins.h"
#include "game.h"

#include "components/adkeyboard.h"
#include "components/joystick.h"
#include "components/relays.h"
#include "components/matrix.h"


Joystick joystick;  /**< Create joystick struct */

DancingCross c;
DancingExcle d;
Animation b;

int j = 0;

void setup() {
  Serial.begin(9600);
  pinSetup();
  setupFastLED();

}

void loop() {
  readADKeyboard();
  readJoystick(joystick, JOYSTICK_SW, JOYSTICK_X, JOYSTICK_Y);

  /* --- Experiment --- */
  if( adkeyboard.right == ButtonState::PRESSED ) {
    d.setAnimation(leds);
    j = 2;
  }
  else if( adkeyboard.left == ButtonState::PRESSED ) {
    j = 1;
  }
  else if( adkeyboard.up == ButtonState::PRESSED ) {
    j = 3;
  }
  else if( adkeyboard.enter == ButtonState::PRESSED ) {
    b.setAnimation(leds);
    j = 0;
  }

  if( j == 2 ) {
    display(d);
  }
  else if( j == 1 ) {
    display(c);
  }
  else if( j == 3 ) {
    joystickDisplay( joystick );
  }
  else {
    display(b);
  }
  /* --- ~Experiment --- */

  delay(50);
}
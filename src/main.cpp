#include <Arduino.h>

#include "components/pins.h"
#include "eventhandler.h"


void setup() {
  Serial.begin(9600);
  Wire.begin();

  pinSetup();
  setupKeypad();
  setupFastLED();
  lcd.init();
  randomSeed(analogRead(A15));

  setupEventHandler();
}

void loop() {
  /* Read periferies */
  readADKeyboard();
  readJoystick(joystick, JOYSTICK_SW, JOYSTICK_X, JOYSTICK_Y);
  keypad.getKey();

  /* Action */
  checkEvents();
  rtttl::play();
}
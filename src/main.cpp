#include <Arduino.h>
#include "components/pins.h"
#include "eventhandler.h"

#include "components/adkeyboard.h"
#include "components/joystick.h"
#include "components/relays.h"
#include "components/matrix.h"
#include "components/lcd.h"
#include "components/keypad.h"
#include "components/buzzer.h"



void setup() {
  Serial.begin(9600);
  Wire.begin();

  pinSetup();
  setupFastLED();
  setupKeypad();
  setupFastLED();
  lcd.init();

  setupEventHandler();
}

void loop() {
  readADKeyboard();
  readJoystick(joystick, JOYSTICK_SW, JOYSTICK_X, JOYSTICK_Y);
  keypad.getKey();

  checkEvents();
  rtttl::play();
}
#include <Arduino.h>
#include "components/pins.h"
#include "game.h"

#include "components/adkeyboard.h"
#include "components/joystick.h"
#include "components/relays.h"
#include "components/matrix.h"
#include "components/lcd.h"
#include "components/keypad.h"


Joystick joystick;  /**< Create joystick struct */

/* Experiment */
char test[2] = { '1', '2' };

void playSound0() {
  tone(BUZZER_1, 200, 100);
}
void playSound1() {
  tone(BUZZER_1, 400, 100);
}
void playSound2() {
  tone(BUZZER_1, 800, 100);
}
void playSound3() {
  tone(BUZZER_1, 1200, 100);
}
void playSound4() {
  tone(BUZZER_1, 1600, 100);
}

void setup() {
  Serial.begin(9600);
  Wire.begin();

  pinSetup();
  setupFastLED();
  setupKeypad();
  lcd.init();

  setSequence(test, 2, playSound0, playSound1, playSound2, playSound3, playSound4);  // Experiment
}

void loop() {
  readADKeyboard();
  readJoystick(joystick, JOYSTICK_SW, JOYSTICK_X, JOYSTICK_Y);
  keypad.getKey();

  delay(50);
}
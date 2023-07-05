#include <Arduino.h>
#include <tinyfsm.hpp>
#include "components/pins.h"
#include "game.h"

#include "components/adkeyboard.h"
#include "components/joystick.h"
#include "components/relays.h"
#include "components/matrix.h"
#include "components/lcd.h"
#include "components/keypad.h"


/* Experiment */

// Events
struct EnterPressed : tinyfsm::Event {};
struct RightPressed : tinyfsm::Event {};

// State machine
class Gate : public tinyfsm::Fsm<Gate> {
public:
  /* default reaction for unhandled events */
  void react(tinyfsm::Event const &) { };

  virtual void react(EnterPressed const &) {};
  virtual void react(RightPressed const &) {};

  virtual void entry(void) { };  /* Entry actions for states (override or this is the default) */
  virtual void exit(void)  { };  /* Exit action for states (states override or do nothing) */
};

class Opened;

// States
class Closed : public Gate {

  void react(EnterPressed const &) override {
    Serial.println("Opening the gate!");
    transit<Opened>(/* Optional transition action*/);
  }
};

class Opened : public Gate {

  void react(RightPressed const &) override {
    Serial.println("Closing the gate!");
    transit<Closed>(/* Optional transition action*/);
  }
};

// Define initial state
FSM_INITIAL_STATE(Gate, Closed)

/* ~Experiment */


Joystick joystick;  /**< Create joystick struct */

void setup() {
  Serial.begin(9600);
  Wire.begin();

  pinSetup();
  setupFastLED();
  setupKeypad();
  setupFastLED();
  lcd.init();

  Gate::start();  // For more state machines, use fsmlist to send an event to all
}

void loop() {
  readADKeyboard();
  readJoystick(joystick, JOYSTICK_SW, JOYSTICK_X, JOYSTICK_Y);
  keypad.getKey();

  if( adkeyboard.enter == PRESSED ) {
    Gate::dispatch( EnterPressed() );
  }
  else if( adkeyboard.right == PRESSED ) {
    Gate::dispatch( RightPressed() );
  }

  delay(50);
}
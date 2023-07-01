#include <unity.h>

#include "./tests/components/test_joystick.cpp"
#include "./tests/components/test_ADKeypad.cpp"
#include "./tests/components/test_relays.cpp"
#include "./tests/components/test_button.cpp"
#include "./tests/components/test_buzzers.cpp"
#include "./tests/components/test_matrix.cpp"
#include "./tests/components/test_lcd.cpp"


void setUp(void) {
  // set stuff up here
  pinSetup();
}

void tearDown(void) {
  // clean stuff up here
}


int runUnityTests() {
    UNITY_BEGIN();

    runKeyboardTests();
    runJoystickTests();
    runRelaysTest();
    runEmergencyButtonTest();
    runBuzzerTest();
    runMatrixTest();
    runLCDTest();

    return UNITY_END();
}



void setup(){
  // Wait ~1 seconds before the Unity test runner
  // establishes connection with a board Serial interface
  delay(2000);

  runUnityTests();
}

void loop() {}
#include "unity.h"
#include "components/pins.h"
#include "components/adkeyboard.h"
#include "components/button.h"
#include <Keypad.h>


void test_emebutton_press(void) {
    TEST_MESSAGE("Press the emergency button");

    uint16_t millis_start = millis();
    while( millis() < millis_start + 5000 ) {

        if( digitalRead(BUTTON_IN) == HIGH ) {
            TEST_ASSERT_TRUE(true);
            return;
        }
    }
    TEST_FAIL();
}

void test_emebutton_release(void) {
    TEST_MESSAGE("Disarm the emergency button");

    uint16_t millis_start = millis();
    while( millis() < millis_start + 5000 ) {

        if( digitalRead(BUTTON_IN) == LOW ) {
            TEST_ASSERT_TRUE(true);
            return;
        }
    }
    TEST_FAIL();
}

void test_leds() {
    const int time = 1000;

    setButtonLEDs(255, 0, 0);
    delay(time);

    setButtonLEDs(0, 255, 0);
    delay(time);

    setButtonLEDs(0, 0, 255);
    delay(time);

    setButtonLEDs(0, 0, 0);

    TEST_MESSAGE("Press the enter button on ADKeypad if all colours display");

    uint16_t millis_start = millis();
    while( millis() < millis_start + 5000 ) {
        readADKeyboard();

        if( adkeyboard.enter == PRESSED ) {
            TEST_ASSERT_TRUE(true);
            return;
        }
    }
    TEST_FAIL();
}


void runEmergencyButtonTest() {
    RUN_TEST(test_emebutton_press);
    RUN_TEST(test_emebutton_release);

    RUN_TEST(test_leds);
}

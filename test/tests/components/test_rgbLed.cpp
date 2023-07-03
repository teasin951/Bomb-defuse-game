#include "unity.h"
#include "components/rgb_led.h"
#include "components/adkeyboard.h"
#include <Keypad.h>


void test_rgb_led() {
    const int time = 1000;

    setLED(255, 0, 0);
    delay(time);

    setLED(0, 255, 0);
    delay(time);

    setLED(0, 0, 255);
    delay(time);

    setLED(0, 0, 0);

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


void runRgbLedTests() {
    RUN_TEST(test_rgb_led);
}

#include "unity.h"
#include "components/pins.h"
#include <Keypad.h>


void test_switch_press(void) {
    TEST_MESSAGE("Press the switch");

    uint16_t millis_start = millis();
    while( millis() < millis_start + 5000 ) {

        if( digitalRead(SWITCH) == HIGH ) {
            TEST_ASSERT_TRUE(true);
            return;
        }
    }
    TEST_FAIL();
}

void test_switch_release() {
    TEST_MESSAGE("Release the switch");

    uint16_t millis_start = millis();
    while( millis() < millis_start + 5000 ) {
        if( digitalRead(SWITCH) == LOW ) {
            TEST_ASSERT_TRUE(true);
            return;
        }
    }
    TEST_FAIL();
}


void runSwitchTests(void) {

  RUN_TEST(test_switch_press);
  RUN_TEST(test_switch_release);

}
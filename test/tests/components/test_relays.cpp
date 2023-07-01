#include "unity.h"
#include "components/relays.h"
#include "components/pins.h"
#include "components/adkeyboard.h"
#include <Keypad.h>


void test_relays() {
    const int time = 250;

    setRelays(1, 0, 0, 0);
    delay(time);

    setRelays(0, 1, 0, 0);
    delay(time);

    setRelays(0, 0, 1, 0);
    delay(time);

    setRelays(0, 0, 0, 1);
    delay(time);

    setRelays(0, 0, 1, 0);
    delay(time);

    setRelays(0, 1, 0, 0);
    delay(time);

    setRelays(1, 0, 0, 0);
    delay(time);

    setRelays(0, 0, 0, 0);
    delay(time);

    setRelays(1, 1, 1, 1);
    delay(4*time);

    setRelays(0, 0, 0, 0);
    delay(time);

    TEST_MESSAGE("Press the enter button on ADKeypad if all relays work");

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

void runRelaysTest() {
    RUN_TEST(test_relays);
}

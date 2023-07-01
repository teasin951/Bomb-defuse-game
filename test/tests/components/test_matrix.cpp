#include "unity.h"
#include "components/matrix.h"
#include "components/pins.h"
#include "components/adkeyboard.h"
#include <Keypad.h>


void test_matrix() {
    setupFastLED();
    
    for( int j = 0; j < 4; j++ ) {
        for( int i = 0; i < 255; i++ ) {

            fill_rainbow(canvas.m_LED, NUM_LEDS, i, 1);

            FastLED.show();
            delay(5);
        }
    }
    fill_solid(canvas.m_LED, NUM_LEDS, CRGB::Black);
    FastLED.show();


    TEST_MESSAGE("Press the enter button on ADKeypad if 8x8 matrix works");

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

void runMatrixTest() {
    RUN_TEST(test_matrix);
}
#include "unity.h"
#include "pins.h"
#include "adkeyboard.h"


void test_buzzer1() {
    uint16_t time = 200;

    tone(BUZZER_1, 200, 200);
    delay(time);

    tone(BUZZER_1, 400, 200);
    delay(time);
    
    tone(BUZZER_1, 600, 200);
    delay(time);

    tone(BUZZER_1, 800, 200);
    delay(time);

    tone(BUZZER_1, 1000, 200);
    delay(time);

    tone(BUZZER_1, 2000, 200);
    delay(time);

    tone(BUZZER_1, 4000, 200);
    delay(time);

    noTone(BUZZER_1);


    TEST_MESSAGE("Press the enter button on ADKeypad if buzzer 1 works");

    uint16_t millis_start = millis();
    while( millis() < millis_start + 5000 ) {
        readADKeyboard();

        if( adkeyboard.enter == ButtonState::PRESSED ) {
            TEST_ASSERT_TRUE(true);
            return;
        }
    }
    TEST_FAIL();
}


void test_buzzer2() {
    uint16_t time = 200;

    tone(BUZZER_2, 200, 200);
    delay(time);

    tone(BUZZER_2, 400, 200);
    delay(time);
    
    tone(BUZZER_2, 600, 200);
    delay(time);

    tone(BUZZER_2, 800, 200);
    delay(time);

    tone(BUZZER_2, 1000, 200);
    delay(time);

    tone(BUZZER_2, 2000, 200);
    delay(time);

    tone(BUZZER_2, 4000, 200);
    delay(time);

    noTone(BUZZER_2);


    TEST_MESSAGE("Press the enter button on ADKeypad if buzzer 2 works");

    uint16_t millis_start = millis();
    while( millis() < millis_start + 5000 ) {
        readADKeyboard();

        if( adkeyboard.enter == ButtonState::PRESSED ) {
            TEST_ASSERT_TRUE(true);
            return;
        }
    }
    TEST_FAIL();
}


void runBuzzerTest() {
    RUN_TEST(test_buzzer1);
    RUN_TEST(test_buzzer2);
}
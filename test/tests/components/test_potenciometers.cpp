#include "unity.h"
#include "components/pins.h"


void test_max_1() {

    TEST_MESSAGE("Turn the first potenciometer to it's maximum");

    uint16_t millis_start = millis();
    while( millis() < millis_start + 5000 ) {

        if( analogRead(POTENCIOMETER1) == 1023 ) {
            TEST_ASSERT_TRUE(true);
            return;
        }
    }
    TEST_FAIL();
}

void test_min_1() {

    TEST_MESSAGE("Turn the first potenciometer to it's minimum");

    uint16_t millis_start = millis();
    while( millis() < millis_start + 5000 ) {

        if( analogRead(POTENCIOMETER1) == 0 ) {
            TEST_ASSERT_TRUE(true);
            return;
        }
    }
    TEST_FAIL();
}


void test_max_2() {

    TEST_MESSAGE("Turn the second potenciometer to it's maximum");

    uint16_t millis_start = millis();
    while( millis() < millis_start + 5000 ) {

        if( analogRead(POTENCIOMETER2) == 1023 ) {
            TEST_ASSERT_TRUE(true);
            return;
        }
    }
    TEST_FAIL();
}

void test_min_2() {

    TEST_MESSAGE("Turn the second potenciometer to it's minimum");

    uint16_t millis_start = millis();
    while( millis() < millis_start + 5000 ) {

        if( analogRead(POTENCIOMETER2) == 0 ) {
            TEST_ASSERT_TRUE(true);
            return;
        }
    }
    TEST_FAIL();
}


void test_max_3() {

    TEST_MESSAGE("Turn the third potenciometer to it's maximum");

    uint16_t millis_start = millis();
    while( millis() < millis_start + 5000 ) {

        if( analogRead(POTENCIOMETER3) == 1023 ) {
            TEST_ASSERT_TRUE(true);
            return;
        }
    }
    TEST_FAIL();
}

void test_min_3() {

    TEST_MESSAGE("Turn the third potenciometer to it's minimum");

    uint16_t millis_start = millis();
    while( millis() < millis_start + 5000 ) {

        if( analogRead(POTENCIOMETER3) == 0 ) {
            TEST_ASSERT_TRUE(true);
            return;
        }
    }
    TEST_FAIL();
}

void runPotenciometeTest() {
    RUN_TEST(test_max_1);
    RUN_TEST(test_min_1);
    RUN_TEST(test_max_2);
    RUN_TEST(test_min_2);
    RUN_TEST(test_max_3);
    RUN_TEST(test_min_3);
}

#include "unity.h"
#include "components/keypad.h"
#include "components/pins.h"

bool t = false;

void failT() {
    t = false;
}

void passT() {
    t = true;
}

void test_press() {
    char s[2] = { 1, 2 };

    setSequence(s, 2, passT, failT, failT, failT, failT);

    TEST_MESSAGE("Press any number on the keypad");

    uint16_t millis_start = millis();
    while( millis() < millis_start + 5000 ) {
        keypad.getKey();

        if( t == true ) {
            TEST_ASSERT_TRUE(true);
            t = false;
            return;
        }
    }
    TEST_FAIL();
}

void test_sequence_match() {
    char s[10] = { '1', '2', '3', '4', '5', '6', '7', '8', '9', '0' };

    setSequence(s, 10, nada, passT, failT, failT, failT);

    TEST_MESSAGE("Type: '1 2 3 4 5 6 7 8 9 0 #' on the keypad");

    uint16_t millis_start = millis();
    while( millis() < millis_start + 10000 ) {
        keypad.getKey();

        if( t == true ) {
            TEST_ASSERT_TRUE(true);
            t = false;
            return;
        }
    }
    TEST_FAIL();
}

void test_sequence_no_match() {
    char s[10] = { '1', '2', '3', '4', '5', '6', '7', '8', '9', '0' };

    setSequence(s, 10, nada, failT, passT, failT, failT);

    TEST_MESSAGE("Type: '1 2 3 4 #' on the keypad");

    uint16_t millis_start = millis();
    while( millis() < millis_start + 10000 ) {
        keypad.getKey();

        if( t == true ) {
            TEST_ASSERT_TRUE(true);
            t = false;
            return;
        }
    }
    TEST_FAIL();
}

void test_clear() {
    char s[2] = { '1', '2' };

    setSequence(s, 2, nada, failT, failT, passT, failT);

    TEST_MESSAGE("Type: '1 2 *' on the keypad");

    uint16_t millis_start = millis();
    while( millis() < millis_start + 10000 ) {
        keypad.getKey();

        if( t == true ) {
            TEST_ASSERT_TRUE(true);
            t = false;
            return;
        }
    }
    TEST_FAIL();
}

void test_overflow() {
    char s[2] = { '1', '2' };

    setSequence(s, 2, nada, failT, failT, failT, passT);

    TEST_MESSAGE("Type: '1 2 3' on the keypad");

    uint16_t millis_start = millis();
    while( millis() < millis_start + 10000 ) {
        keypad.getKey();

        if( t == true ) {
            TEST_ASSERT_TRUE(true);
            t = false;
            return;
        }
    }
    TEST_FAIL();
}

void runKeypadTest() {
    setupKeypad();

    RUN_TEST(test_press);
    clearSequence();

    RUN_TEST(test_sequence_match);
    clearSequence();

    RUN_TEST(test_sequence_no_match);
    clearSequence();

    RUN_TEST(test_clear);
    clearSequence();

    RUN_TEST(test_overflow);
    clearSequence();
}

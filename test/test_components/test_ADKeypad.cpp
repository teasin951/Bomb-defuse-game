#include "unity.h"
#include "adkeyboard.h"

void setUp(void) {
  // set stuff up here
  pinSetup();
}

void tearDown(void) {
  // clean stuff up here
}

void test_left(void) {
    TEST_MESSAGE("Press the left button on ADKeaboard");

    uint16_t millis_start = millis();
    while( millis() < millis_start + 5000 ) {
        readADKeyboard();

        if( adkeyboard.left == ButtonState::PRESSED ) {
            TEST_ASSERT_TRUE(true);
            break;
        }
        else if ( adkeyboard.left == ButtonState::HELD ) {
            TEST_FAIL();
        }
    }

    TEST_MESSAGE("Release the left button on ADKeaboard");
    millis_start = millis();
    while( millis() < millis_start + 5000 ) {
        readADKeyboard();

        if( adkeyboard.left == ButtonState::RELEASED ) {
            TEST_ASSERT_TRUE(true);
            return;
        }
        else if ( adkeyboard.left == ButtonState::HELD ) {
            TEST_FAIL();
        }
    }
    TEST_FAIL();
}

void test_right(void) {
    TEST_MESSAGE("Press the right button on ADKeaboard");

    uint16_t millis_start = millis();
    while( millis() < millis_start + 5000 ) {
        readADKeyboard();

        if( adkeyboard.right == ButtonState::PRESSED ) {
            TEST_ASSERT_TRUE(true);
            break;
        }
        else if ( adkeyboard.right == ButtonState::HELD ) {
            TEST_FAIL();
        }
    }

    TEST_MESSAGE("Release the left button on ADKeaboard");
    millis_start = millis();
    while( millis() < millis_start + 5000 ) {
        readADKeyboard();

        if( adkeyboard.right == ButtonState::RELEASED ) {
            TEST_ASSERT_TRUE(true);
            return;
        }
        else if ( adkeyboard.right == ButtonState::HELD ) {
            TEST_FAIL();
        }
    }
    TEST_FAIL();
}

void test_up(void) {
    TEST_MESSAGE("Press the up button on ADKeaboard");

    uint16_t millis_start = millis();
    while( millis() < millis_start + 5000 ) {
        readADKeyboard();

        if( adkeyboard.up == ButtonState::PRESSED ) {
            TEST_ASSERT_TRUE(true);
            break;
        }
        else if ( adkeyboard.up == ButtonState::HELD ) {
            TEST_FAIL();
        }
    }

    TEST_MESSAGE("Release the up button on ADKeaboard");
    millis_start = millis();
    while( millis() < millis_start + 5000 ) {
        readADKeyboard();

        if( adkeyboard.up == ButtonState::RELEASED ) {
            TEST_ASSERT_TRUE(true);
            return;
        }
        else if ( adkeyboard.up == ButtonState::HELD ) {
            TEST_FAIL();
        }
    }
    TEST_FAIL();
}

void test_down(void) {
    TEST_MESSAGE("Press the down button on ADKeaboard");

    uint16_t millis_start = millis();
    while( millis() < millis_start + 5000 ) {
        readADKeyboard();

        if( adkeyboard.down == ButtonState::PRESSED ) {
            TEST_ASSERT_TRUE(true);
            break;
        }
        else if ( adkeyboard.down == ButtonState::HELD ) {
            TEST_FAIL();
        }
    }

    TEST_MESSAGE("Release the down button on ADKeaboard");
    millis_start = millis();
    while( millis() < millis_start + 5000 ) {
        readADKeyboard();

        if( adkeyboard.down == ButtonState::RELEASED ) {
            TEST_ASSERT_TRUE(true);
            return;
        }
        else if ( adkeyboard.down == ButtonState::HELD ) {
            TEST_FAIL();
        }
    }
    TEST_FAIL();
}

void test_enter(void) {
    TEST_MESSAGE("Press the enter button on ADKeaboard");

    uint16_t millis_start = millis();
    while( millis() < millis_start + 5000 ) {
        readADKeyboard();

        if( adkeyboard.enter == ButtonState::PRESSED ) {
            TEST_ASSERT_TRUE(true);
            break;
        }
        else if ( adkeyboard.enter == ButtonState::HELD ) {
            TEST_FAIL();
        }
    }

    TEST_MESSAGE("Release the enter button on ADKeaboard");
    millis_start = millis();
    while( millis() < millis_start + 5000 ) {
        readADKeyboard();

        if( adkeyboard.enter == ButtonState::RELEASED ) {
            TEST_ASSERT_TRUE(true);
            return;
        }
        else if ( adkeyboard.enter == ButtonState::HELD ) {
            TEST_FAIL();
        }
    }
    TEST_FAIL();
}

int runUnityTests(void) {
  UNITY_BEGIN();

  RUN_TEST(test_left);
  RUN_TEST(test_right);
  RUN_TEST(test_up);
  RUN_TEST(test_down);
  RUN_TEST(test_enter);

  return UNITY_END();
}

/**
  * For Arduino framework
  */
void setup() {
  // Wait ~2 seconds before the Unity test runner
  // establishes connection with a board Serial interface
  delay(2000);

  runUnityTests();
}

void loop() {}

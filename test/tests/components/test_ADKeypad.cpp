#include "unity.h"
#include "adkeyboard.h"


void test_left_press(void) {
    TEST_MESSAGE("Press the left button on ADKeaboard");

    uint16_t millis_start = millis();
    while( millis() < millis_start + 5000 ) {
        readADKeyboard();

        if( adkeyboard.left == ButtonState::PRESSED ) {
            TEST_ASSERT_TRUE(true);
            return;
        }
        else if ( adkeyboard.left != ButtonState::RELEASED ) {
            TEST_FAIL();
        }
    }
    TEST_FAIL();
}

void test_left_release() {
    TEST_MESSAGE("Release the left button on ADKeaboard");

    uint16_t millis_start = millis();
    while( millis() < millis_start + 5000 ) {
        readADKeyboard();

        if( adkeyboard.left == ButtonState::RELEASED ) {
            TEST_ASSERT_TRUE(true);
            return;
        }
        else if ( adkeyboard.left != ButtonState::PRESSED ) {
            TEST_FAIL();
        }
    }
    TEST_FAIL();
}


void test_right_press(void) {
    TEST_MESSAGE("Press the right button on ADKeaboard");

    uint16_t millis_start = millis();
    while( millis() < millis_start + 5000 ) {
        readADKeyboard();

        if( adkeyboard.right == ButtonState::PRESSED ) {
            TEST_ASSERT_TRUE(true);
            return;
        }
        else if ( adkeyboard.right != ButtonState::RELEASED ) {
            TEST_FAIL();
        }
    }
    TEST_FAIL();
}

void test_right_release() {
    TEST_MESSAGE("Release the left button on ADKeaboard");

    uint16_t millis_start = millis();
    while( millis() < millis_start + 5000 ) {
        readADKeyboard();

        if( adkeyboard.right == ButtonState::RELEASED ) {
            TEST_ASSERT_TRUE(true);
            return;
        }
        else if ( adkeyboard.right != ButtonState::PRESSED ) {
            TEST_FAIL();
        }
    }
    TEST_FAIL();
}


void test_up_press(void) {
    TEST_MESSAGE("Press the up button on ADKeaboard");

    uint16_t millis_start = millis();
    while( millis() < millis_start + 5000 ) {
        readADKeyboard();

        if( adkeyboard.up == ButtonState::PRESSED ) {
            TEST_ASSERT_TRUE(true);
            return;
        }
        else if ( adkeyboard.up != ButtonState::RELEASED ) {
            TEST_FAIL();
        }
    }
    TEST_FAIL();
}

void test_up_release() {
    TEST_MESSAGE("Release the up button on ADKeaboard");

    uint16_t millis_start = millis();
    while( millis() < millis_start + 5000 ) {
        readADKeyboard();

        if( adkeyboard.up == ButtonState::RELEASED ) {
            TEST_ASSERT_TRUE(true);
            return;
        }
        else if ( adkeyboard.up != ButtonState::PRESSED ) {
            TEST_FAIL();
        }
    }
    TEST_FAIL();
}


void test_down_press(void) {
    TEST_MESSAGE("Press the down button on ADKeaboard");

    uint16_t millis_start = millis();
    while( millis() < millis_start + 5000 ) {
        readADKeyboard();

        if( adkeyboard.down == ButtonState::PRESSED ) {
            TEST_ASSERT_TRUE(true);
            return;
        }
        else if ( adkeyboard.down != ButtonState::RELEASED ) {
            TEST_FAIL();
        }
    }
    TEST_FAIL();
}

void test_down_release() {
    TEST_MESSAGE("Release the down button on ADKeaboard");

    uint16_t millis_start = millis();
    while( millis() < millis_start + 5000 ) {
        readADKeyboard();

        if( adkeyboard.down == ButtonState::RELEASED ) {
            TEST_ASSERT_TRUE(true);
            return;
        }
        else if ( adkeyboard.down != ButtonState::PRESSED ) {
            TEST_FAIL();
        }
    }
    TEST_FAIL();
}


void test_enter_press(void) {
    TEST_MESSAGE("Press the enter button on ADKeaboard");

    uint16_t millis_start = millis();
    while( millis() < millis_start + 5000 ) {
        readADKeyboard();

        if( adkeyboard.enter == ButtonState::PRESSED ) {
            TEST_ASSERT_TRUE(true);
            return;
        }
        else if ( adkeyboard.enter != ButtonState::RELEASED ) {
            TEST_FAIL();
        }
    }
    TEST_FAIL();
}

void test_enter_release() {

    TEST_MESSAGE("Release the enter button on ADKeaboard");
    uint16_t millis_start = millis();
    while( millis() < millis_start + 5000 ) {
        readADKeyboard();

        if( adkeyboard.enter == ButtonState::RELEASED ) {
            TEST_ASSERT_TRUE(true);
            return;
        }
        else if ( adkeyboard.enter != ButtonState::PRESSED ) {
            TEST_FAIL();
        }
    }
    TEST_FAIL();
}


void runKeyboardTests(void) {

  RUN_TEST(test_left_press);
  RUN_TEST(test_left_release);

  RUN_TEST(test_right_press);
  RUN_TEST(test_right_release);

  RUN_TEST(test_up_press);
  RUN_TEST(test_up_release);
  
  RUN_TEST(test_down_press);
  RUN_TEST(test_down_release);

  RUN_TEST(test_enter_press);
  RUN_TEST(test_enter_release);

}

#include "unity.h"
#include "joystick.h"
#include "pins.h"


void test_button_press(void) {
    Joystick joy;
    TEST_MESSAGE("Press the joystick button");

    uint16_t millis_start = millis();
    while( millis() < millis_start + 5000 ) {
        readJoystick(joy, JOYSTICK_SW, JOYSTICK_X, JOYSTICK_Y);

        if( joy.button == ButtonState::PRESSED ) {
            TEST_ASSERT_TRUE(true);
            return;
        }
        else if ( joy.button != ButtonState::RELEASED ) {
            TEST_FAIL();
        }
    }
    TEST_FAIL();
}

void test_button_release(void) {
    Joystick joy;
    TEST_MESSAGE("Release the joystick button");

    uint16_t millis_start = millis();
    while( millis() < millis_start + 5000 ) {
        readJoystick(joy, JOYSTICK_SW, JOYSTICK_X, JOYSTICK_Y);

        if( joy.button == ButtonState::RELEASED ) {
            TEST_ASSERT_TRUE(true);
            return;
        }
        else if ( joy.button != ButtonState::PRESSED ) {
            TEST_FAIL();
        }
    }
    TEST_FAIL();
}

void test_x_max() {
    Joystick joy;
    TEST_MESSAGE("Move the joystick to maximum X position");

    uint16_t millis_start = millis();
    while( millis() < millis_start + 5000 ) {
        readJoystick(joy, JOYSTICK_SW, JOYSTICK_X, JOYSTICK_Y);

        if( joy.x > 1018 ) {
            TEST_ASSERT_TRUE(true);
            return;
        }
    }
    TEST_FAIL();
}

void test_x_min() {
    Joystick joy;
    TEST_MESSAGE("Move the joystick to minimum X position");

    uint16_t millis_start = millis();
    while( millis() < millis_start + 5000 ) {
        readJoystick(joy, JOYSTICK_SW, JOYSTICK_X, JOYSTICK_Y);

        if( joy.x < 6 ) {
            TEST_ASSERT_TRUE(true);
            return;
        }
    }
    TEST_FAIL();
}

void test_y_max() {
    Joystick joy;
    TEST_MESSAGE("Move the joystick to maximum Y position");

    uint16_t millis_start = millis();
    while( millis() < millis_start + 5000 ) {
        readJoystick(joy, JOYSTICK_SW, JOYSTICK_X, JOYSTICK_Y);

        if( joy.y > 1018 ) {
            TEST_ASSERT_TRUE(true);
            return;
        }
    }
    TEST_FAIL();
}

void test_y_min() {
    Joystick joy;
    TEST_MESSAGE("Move the joystick to minimum Y position");

    uint16_t millis_start = millis();
    while( millis() < millis_start + 5000 ) {
        readJoystick(joy, JOYSTICK_SW, JOYSTICK_X, JOYSTICK_Y);

        if( joy.y < 6 ) {
            TEST_ASSERT_TRUE(true);
            return;
        }
    }
    TEST_FAIL();
}


void test_center() {
    Joystick joy;
    TEST_MESSAGE("Let the joystick recenter");

    uint16_t millis_start = millis();
    while( millis() < millis_start + 5000 ) {
        readJoystick(joy, JOYSTICK_SW, JOYSTICK_X, JOYSTICK_Y);

        if( 506 < joy.x && joy.x < 520 && 520 < joy.y && joy.y < 530 ) {
            TEST_ASSERT_TRUE(true);
            return;
        }
    }
    TEST_FAIL();
}


void runJoystickTests(void) {

  RUN_TEST(test_button_press);
  RUN_TEST(test_button_release);

  RUN_TEST(test_x_max);
  RUN_TEST(test_x_min);

  RUN_TEST(test_y_max);
  RUN_TEST(test_y_min);

  RUN_TEST(test_center);

}
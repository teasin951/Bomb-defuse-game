#include "unity.h"
#include "components/lcd.h"
#include "components/pins.h"
#include "components/adkeyboard.h"


void test_lcd() {
    lcd.init();
    resetDisplay();

    lcd.print("Test");
    lcd.setCursor(0,1);
    lcd.print("Test");

    for( int i = 0; i < 12; i++ ) {
        lcd.scrollDisplayRight();
        delay(300);
    }
    for( int i = 0; i < 12; i++ ) {
        lcd.scrollDisplayLeft();
        delay(300);
    }

    delay(500);

    resetDisplay();
    lcd.setBacklight(false);


    TEST_MESSAGE("Press the enter button on ADKeypad if the LCD works");

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

void runLCDTest() {
    RUN_TEST(test_lcd);
}
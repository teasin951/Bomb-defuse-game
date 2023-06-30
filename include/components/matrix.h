#pragma once
#include <Arduino.h>
#include <FastLED.h>

#include "pins.h"
#include "matrix/definitions.h"
#include "matrix/animations.h"


// Define the array of leds
CRGB leds[NUM_LEDS];

/**
 * @brief Manage displaying a certain animation
 * 
 * @param animation Animation object to be displayed
*/
void display( Animation & animation ) {
    animation.checkFrame();

    for (uint8_t y = 0; y < NUM_Y; y++) {
        for (uint8_t x = 0; x < NUM_X; x++) {
            leds[(y*NUM_X)+x] = animation.getData( (y*NUM_X)+x );
        }
    }

    FastLED.show();
}

/**
 * Experiment
*/
void joystickDisplay( Joystick & joy ) {
    for (uint8_t y = 0; y < NUM_Y; y++) {
        for (uint8_t x = 0; x < NUM_X; x++) {
            leds[(y*NUM_X)+x] = CRGB(0, 0, 0);
        }
    }

    int x = map(joy.x-10, 1023, 0, 0, 7);
    int y = map(joy.y-10, 1023, 0, 0, 7);
    leds[y*NUM_X + x] = CRGB(0, 127, 255);

    FastLED.show();
}

/**
 * @brief Set up FastLED as needed
*/
void setupFastLED() { 
    FastLED.addLeds<WS2812B, MATRIX, GRB>(leds, NUM_LEDS).setCorrection(TypicalSMD5050);
    FastLED.setBrightness(BRIGHTNESS);
}
#pragma once
#include <Arduino.h>
#include <FastLED.h>

#include "pins.h"
#include "matrix/definitions.h"
#include "matrix/animations.h"


// Define the array of leds
CRGB leds[NUM_LEDS];

BlinkingCross f;


void displayMatrix() {
    f.checkFrame();

    for (uint8_t y = 0; y < NUM_Y; y++) {
        for (uint8_t x = 0; x < NUM_X; x++) {
            leds[(y*NUM_X)+x] = f.getData( (y*NUM_X)+x );
        }
    }

    FastLED.show();
}

void setupFastLED() { 
    FastLED.addLeds<WS2812B, MATRIX, GRB>(leds, NUM_LEDS).setCorrection(TypicalSMD5050);
    FastLED.setBrightness(BRIGHTNESS);
}
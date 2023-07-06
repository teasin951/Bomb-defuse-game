#pragma once
#include <Arduino.h>
#include <FastLED.h>
#include <FastLED_GFX.h>

#include "pins.h"
#include "matrix/definitions.h"
#include "matrix/animations.h"


GFXcanvas canvas(NUM_X, NUM_Y);  /**< My modified version of the library, always creates m_LED[64] */

/**
 * @brief Manage displaying a certain animation
 * 
 * @param animation Animation object to be displayed
*/
void display( Animation & animation ) {
    animation.proceed( canvas.m_LED );
    FastLED.show();
}

/**
 * Experiment
*/
// void joystickDisplay( Joystick & joy ) {
//     for (uint8_t y = 0; y < NUM_Y; y++) {
//         for (uint8_t x = 0; x < NUM_X; x++) {
//             canvas.m_LED[(y*NUM_X)+x] = CRGB(0, 0, 0);
//         }
//     }

//     int x = map(joy.x-10, 1023, 0, 0, 7);
//     int y = map(joy.y-10, 1023, 0, 0, 7);
//     canvas.m_LED[y*NUM_X + x] = CRGB(0, 127, 255);

//     FastLED.show();
// }

/**
 * @brief Set up FastLED as needed
*/
void setupFastLED() { 
    FastLED.addLeds<WS2812B, MATRIX, GRB>(canvas.m_LED, NUM_LEDS).setCorrection(TypicalSMD5050);
    FastLED.setBrightness(BRIGHTNESS);
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 400);
}
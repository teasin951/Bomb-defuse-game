#pragma once
#include <Arduino.h>
#include <FastLED.h>
#include <FastLED_GFX.h>

#include "pins.h"
#include "matrix/definitions.h"


GFXcanvas canvas(NUM_X, NUM_Y);  /**< My modified version of the library, always creates m_LED[64] */

/* defining frames here to avoid dynamic allocation */
#define DEFAULT_FRAMES 1

/**
 * @class Base class for animations
 * 
 * This class holds basic template for animations.
 * Animations are done by filling the base frame and then assigning actions 
 * to frame changes. Animation is done by changing the base frame or by replacing it.
*/
class Animation {
public:
    /**
     * @brief Animation constructor
     * 
     * Each child should define it's frames_count and next_frame_in here
    */
    Animation( GFXcanvas & x ) : leds(x) {}
    virtual ~Animation() = default;

    /**
     * @brief Resets the animation to the beggining
     * 
     * Most importantly, it sets the 'start_millis' variable to the current time and put the starting image to leds.
     * @return false as we shall not move frames after this function call
    */
    virtual bool resetAnimation() {
        leds.fillScreen(CRGB::Black);

        frame = 0;
        start_millis = millis();

        return false;
    }

    /**
     * @brief Prepares the animation to be displayed
     * 
     * Must be called when changing animations!
    */
    virtual void setAnimation() {
        resetAnimation();
        FastLED.show();
    }

    /**
     * @brief Checks if we are supposed to move to the next frame and do it.
     * 
     * Should be called periodically. Every child has to override to access their actions[]
     * 
    */
    virtual void proceed() {

        // time to change frames
        if( millis() > start_millis + (frame+1) * next_frame_in ) {

            // do asociated action and decide if we need frame advancement
            if( (this->*actions[frame])() ) {
                frame++;
            }
            FastLED.show();
        }
    }

    /**
     * @brief Move entire displayed figure right
     * 
     * @return frames shall be proceeded after this
    */
    bool moveRight() {
        for (uint8_t y = 0; y < NUM_Y; y++) {
            for (uint8_t x = NUM_X - 1; x > 0; x--) {
                leds.m_LED[(y*NUM_X)+x] = leds.m_LED[ (y*NUM_X) + x - 1 ];
            }
        }
        for (uint8_t y = 0; y < NUM_Y; y++) {
            leds.m_LED[(y*NUM_X) + 0] = CRGB(0,0,0);
        }
        return true;
    }

    /**
     * @brief Move entire displayed figure left
     * 
     * @return frames shall be proceeded after this
    */
    bool moveLeft() {
        for (uint8_t y = 0; y < NUM_Y; y++) {
            for (uint8_t x = 0; x < NUM_X - 1; x++) {
                leds.m_LED[(y*NUM_X)+x] = leds.m_LED[ (y*NUM_X) + x + 1 ];
            }
        }
        for (uint8_t y = 0; y < NUM_Y; y++) {
            leds.m_LED[(y*NUM_X) + NUM_X - 1] = CRGB(0,0,0);
        }
        return true;
    }

    /**
     * @brief Move entire displayed figure up
     * 
     * @return frames shall be proceeded after this
    */
    bool moveUp() {
        for (uint8_t y = 0; y < NUM_Y - 1; y++) {
            for (uint8_t x = 0; x < NUM_X; x++) {
                leds.m_LED[(y*NUM_X)+x] = leds.m_LED[ (y*NUM_X + NUM_X) + x ];
            }
        }
        for (uint8_t x = 0; x < NUM_X; x++) {
            leds.m_LED[(NUM_Y - 1)*NUM_Y + x] = CRGB(0,0,0);
        }
        return true;
    }

    /**
     * @brief Move entire displayed figure down
     * 
     * @return frames shall be proceeded after this
    */
    bool moveDown() {
        for (uint8_t y = NUM_Y - 1; y > 0; y--) {
            for (uint8_t x = 0; x < NUM_X; x++) {
                leds.m_LED[(y*NUM_X)+x] = leds.m_LED[ (y*NUM_X - NUM_X) + x ];
            }
        }
        for (uint8_t x = 0; x < NUM_X; x++) {
            leds.m_LED[x] = CRGB(0,0,0);
        }
        return true;
    }

protected:
    GFXcanvas & leds;
    bool (Animation::*actions[DEFAULT_FRAMES])() = {&Animation::resetAnimation};  /**< Every child should override! */

    uint32_t start_millis = 0;  /**< Millis when we switched to this animation */
    uint16_t frame = 0;  /**< Animation frame currently displayed */
    uint16_t frame_count = 1;  /**< Number of frames in the animation, change in constructor!!! */
    uint16_t next_frame_in = 40000;  /**< ms between frames, change in constructor!!! */
};


//------------------------- API ---------------------------------

void clearMatrix() {
    canvas.fillScreen(CRGB::Black);
    FastLED.show();
}

/**
 * @brief Set up FastLED as needed
*/
void setupFastLED() { 
    FastLED.addLeds<WS2812B, MATRIX, GRB>(canvas.m_LED, NUM_LEDS).setCorrection(TypicalSMD5050);
    FastLED.setBrightness(BRIGHTNESS);
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 400);

    clearMatrix();
}

//----------------------------------------------------------------




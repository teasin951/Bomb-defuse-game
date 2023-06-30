#include <Arduino.h>
#include <FastLED.h>
#include "definitions.h"

/**
 * @file Defines animations objects
*/

/* defining frames here to avoid dynamic allocation */
#define DANCING_EXCLE_FRAMES 2

/**
 * @class Base class for animations
 * 
 * This class holds basic template for animations.
 * Animations are done by filling 'frames' with arrays of pixel values.
*/
class Animation {
public:
    /**
     * @brief Animation constructor
     * 
     * Each child should define it's frames, frames_count and next_frame_in here
    */
    Animation() = default;
    virtual ~Animation() = default;

    /**
     * @brief Resets the animation to the beggining
     * 
     * Most importantly, it sets the 'start_millis' variable to the current time and put the starting image to leds.
     * 
     * @param leds array of CRGBs used by FastLED to display
    */
    virtual void resetAnimation( CRGB (&leds)[NUM_LEDS] ) {
        for (uint8_t y = 0; y < NUM_Y; y++) {
            for (uint8_t x = 0; x < NUM_X; x++) {
                leds[(y*NUM_X)+x] = base_frame[ (y*NUM_X)+x ];
            }
        }

        frame = 0;
        start_millis = millis();
    }

    /**
     * @brief Prepares the animation to be displayed
     * 
     * Must be called when changing animations!
     * 
     * @param leds array of CRGBs used by FastLED to display
    */
    virtual void setAnimation( CRGB (&leds)[NUM_LEDS] ) {
        resetAnimation(leds);
    }

    /**
     * @brief Checks if we are supposed to move to the next frame and do it.
     * 
     * Should be called periodically.
     * 
     * @param leds array of CRGBs used by FastLED to display
    */
    virtual void proceed( CRGB (&leds)[NUM_LEDS] ) {

        // time to change frames
        if( millis() > start_millis + (frame+1) * next_frame_in ) {

            // frame overflow
            if( frame >= frame_count - 1 ) {
                frame = 0;
                start_millis = millis() + 50000;
            }

            // frame advancement
            else {
                frame++;
            }
        }
    }

protected:
    uint32_t start_millis = 0;  /**< Millis when we switched to this animation */
    uint16_t frame = 0;  /**< Animation frame currently displayed */
    uint16_t frame_count = 1;  /**< Number of frames in the animation, change in constructor!!! */
    uint16_t next_frame_in = 40000;  /**< ms between frames, change in constructor!!! */

    const CRGB base_frame[NUM_LEDS] = {
        CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),
        CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),
        CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),
        CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),
        CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),
        CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),
        CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),
        CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),
    };  /**< The first base frame for the animation */

    void (*actions[1])( CRGB (&)[NUM_LEDS] ) = { nullptr };  /**< Actions to perform when changing to the next frame */
};


class DancingExcle : public Animation {
public:
    DancingExcle() {
        frame_count = DANCING_EXCLE_FRAMES;
        next_frame_in = 500;
    }
    virtual ~DancingExcle() = default;

    void resetAnimation( CRGB (&leds)[NUM_LEDS] ) override {
        for (uint8_t y = 0; y < NUM_Y; y++) {
            for (uint8_t x = 0; x < NUM_X; x++) {
                leds[(y*NUM_X)+x] = base_frame[ (y*NUM_X)+x ];
            }
        }

        frame = 0;
        start_millis = millis();
    }

    void moveRight( CRGB (&leds)[NUM_LEDS] ) {
        for (uint8_t y = 0; y < NUM_Y; y++) {
            for (uint8_t x = NUM_X; x > 0; x--) {
                leds[(y*NUM_X)+x] = leds[ (y*NUM_X) + x - 1 ];
            }
        }
        for (uint8_t y = 0; y < NUM_Y; y++) {
            leds[(y*NUM_X) + 0] = CRGB(0,0,0);
        }
    }

    void proceed( CRGB (&leds)[NUM_LEDS] ) override {

        // time to change frames
        if( millis() > start_millis + (frame+1) * next_frame_in ) {

            // do asociated action
            (this->*actions[frame])(leds);

            // frame overflow
            if( frame >= frame_count - 1 ) {
                resetAnimation(leds);
            }

            // frame advancement
            else {
                frame++;
            }
        }
    }

private:
    const CRGB base_frame[NUM_LEDS] = {
        CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),
        CRGB(0,0,0),CRGB(192,0,0),CRGB(0,0,0),CRGB(192,0,0),CRGB(0,0,0),CRGB(192,0,0),CRGB(0,0,0),CRGB(0,0,0),
        CRGB(0,0,0),CRGB(192,0,0),CRGB(0,0,0),CRGB(192,0,0),CRGB(0,0,0),CRGB(192,0,0),CRGB(0,0,0),CRGB(0,0,0),
        CRGB(0,0,0),CRGB(192,0,0),CRGB(0,0,0),CRGB(192,0,0),CRGB(0,0,0),CRGB(192,0,0),CRGB(0,0,0),CRGB(0,0,0),
        CRGB(0,0,0),CRGB(192,0,0),CRGB(0,0,0),CRGB(192,0,0),CRGB(0,0,0),CRGB(192,0,0),CRGB(0,0,0),CRGB(0,0,0),
        CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),
        CRGB(0,0,0),CRGB(192,0,0),CRGB(0,0,0),CRGB(192,0,0),CRGB(0,0,0),CRGB(192,0,0),CRGB(0,0,0),CRGB(0,0,0),
        CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),
    };  /**< The first base frame for the animation */

    void (DancingExcle::*actions[DANCING_EXCLE_FRAMES])( CRGB (&)[NUM_LEDS] ) = { 
        &DancingExcle::moveRight, nullptr };  /**< Actions to perform when changing to the next frame */
};


class DancingCross : public Animation {
public:
    DancingCross();
    virtual ~DancingCross() = default;

private:
};


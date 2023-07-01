#pragma once
#include <Arduino.h>
#include <FastLED.h>
#include "definitions.h"

/**
 * @file Defines animations objects
*/

/* defining frames here to avoid dynamic allocation */
#define DANCING_EXCLE_FRAMES 2
#define DANCING_CROSS_FRAMES 6

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
     * @return false as we shall not move frames after this function call
    */
    virtual bool resetAnimation( CRGB (&leds)[NUM_LEDS] ) {
        for (uint8_t y = 0; y < NUM_Y; y++) {
            for (uint8_t x = 0; x < NUM_X; x++) {
                leds[(y*NUM_X)+x] = CRGB(0,0,0);
            }
        }

        frame = 0;
        start_millis = millis();

        return false;
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

    /**
     * @brief Move entire displayed figure right
     * 
     * @param leds array of CRGBs used by FastLED to display
    */
    bool moveRight( CRGB (&leds)[NUM_LEDS] ) {
        for (uint8_t y = 0; y < NUM_Y; y++) {
            for (uint8_t x = NUM_X - 1; x > 0; x--) {
                leds[(y*NUM_X)+x] = leds[ (y*NUM_X) + x - 1 ];
            }
        }
        for (uint8_t y = 0; y < NUM_Y; y++) {
            leds[(y*NUM_X) + 0] = CRGB(0,0,0);
        }
        return true;
    }

    /**
     * @brief Move entire displayed figure left
     * 
     * @param leds array of CRGBs used by FastLED to display
    */
    bool moveLeft( CRGB (&leds)[NUM_LEDS] ) {
        for (uint8_t y = 0; y < NUM_Y; y++) {
            for (uint8_t x = 0; x < NUM_X - 1; x++) {
                leds[(y*NUM_X)+x] = leds[ (y*NUM_X) + x + 1 ];
            }
        }
        for (uint8_t y = 0; y < NUM_Y; y++) {
            leds[(y*NUM_X) + NUM_X - 1] = CRGB(0,0,0);
        }
        return true;
    }

    /**
     * @brief Move entire displayed figure up
     * 
     * @param leds array of CRGBs used by FastLED to display
    */
    bool moveUp( CRGB (&leds)[NUM_LEDS] ) {
        for (uint8_t y = 0; y < NUM_Y - 1; y++) {
            for (uint8_t x = 0; x < NUM_X; x++) {
                leds[(y*NUM_X)+x] = leds[ (y*NUM_X + NUM_X) + x ];
            }
        }
        for (uint8_t x = 0; x < NUM_X; x++) {
            leds[(NUM_Y - 1)*NUM_Y + x] = CRGB(0,0,0);
        }
        return true;
    }

    /**
     * @brief Move entire displayed figure down
     * 
     * @param leds array of CRGBs used by FastLED to display
    */
    bool moveDown( CRGB (&leds)[NUM_LEDS] ) {
        for (uint8_t y = NUM_Y - 1; y > 0; y--) {
            for (uint8_t x = 0; x < NUM_X; x++) {
                leds[(y*NUM_X)+x] = leds[ (y*NUM_X - NUM_X) + x ];
            }
        }
        for (uint8_t x = 0; x < NUM_X; x++) {
            leds[x] = CRGB(0,0,0);
        }
        return true;
    }

protected:
    uint32_t start_millis = 0;  /**< Millis when we switched to this animation */
    uint16_t frame = 0;  /**< Animation frame currently displayed */
    uint16_t frame_count = 1;  /**< Number of frames in the animation, change in constructor!!! */
    uint16_t next_frame_in = 40000;  /**< ms between frames, change in constructor!!! */
};


class DancingExcle : public Animation {
public:
    DancingExcle() {
        frame_count = DANCING_EXCLE_FRAMES;
        next_frame_in = 500;
    }
    virtual ~DancingExcle() = default;

    bool resetAnimation( CRGB (&leds)[NUM_LEDS] ) override {
        for (uint8_t y = 0; y < NUM_Y; y++) {
            for (uint8_t x = 0; x < NUM_X; x++) {
                leds[(y*NUM_X)+x] = base_frame[ (y*NUM_X)+x ];
            }
        }

        frame = 0;
        start_millis = millis();

        return false;
    }

    void proceed( CRGB (&leds)[NUM_LEDS] ) override {

        // time to change frames
        if( millis() > start_millis + (frame+1) * next_frame_in ) {

            // do asociated action and decide if we need frame advancement
            if( (this->*actions[frame])(leds) ) {
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

    bool (DancingExcle::*actions[DANCING_EXCLE_FRAMES])( CRGB (&)[NUM_LEDS] ) = { 
        &DancingExcle::moveRight, &DancingExcle::resetAnimation };  /**< Actions to perform when changing to the next frame */
};


class DancingCross : public Animation {
public:
    DancingCross() {
        frame_count = DANCING_CROSS_FRAMES;
        next_frame_in = 200;
    }
    virtual ~DancingCross() = default;

    void proceed( CRGB (&leds)[NUM_LEDS] ) override {

        // time to change frames
        if( millis() > start_millis + (frame+1) * next_frame_in ) {

            // do asociated action and decide if we need frame advancement
            if( (this->*actions[frame])(leds) ) {
                frame++;
            }
        }
    }
    bool resetAnimation( CRGB (&leds)[NUM_LEDS] ) override {
        for (uint8_t y = 0; y < NUM_Y; y++) {
            for (uint8_t x = 0; x < NUM_X; x++) {
                leds[(y*NUM_X)+x] = base_frame[ (y*NUM_X)+x ];
            }
        }

        frame = 0;
        start_millis = millis();

        return false;
    }

    bool leftDown( CRGB (&leds)[NUM_LEDS] ) {
        moveDown( leds );
        moveLeft( leds );
        return true;
    }

    bool leftUp( CRGB (&leds)[NUM_LEDS] ) {
        moveUp( leds );
        moveLeft( leds );
        return true;
    }

    bool rightUp( CRGB (&leds)[NUM_LEDS] ) {
        moveUp( leds );
        moveRight( leds );
        return true;
    }

    bool rightDown ( CRGB (&leds)[NUM_LEDS] ) {
        moveDown( leds );
        moveRight( leds );
        return false;
    }

private:
    const CRGB base_frame[NUM_LEDS] = {
        CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),
        CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(192,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(192,0,0),
        CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(192,0,0),CRGB(0,0,0),CRGB(192,0,0),CRGB(0,0,0),
        CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(192,0,0),CRGB(0,0,0),CRGB(0,0,0),
        CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(192,0,0),CRGB(0,0,0),CRGB(192,0,0),CRGB(0,0,0),
        CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(192,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(192,0,0),
        CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),
        CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),
    };  /**< The first base frame for the animation */

    bool (DancingCross::*actions[DANCING_CROSS_FRAMES])( CRGB (&)[NUM_LEDS] ) = { 
        &DancingCross::leftDown, &DancingCross::leftDown,
        &DancingCross::leftUp, &DancingCross::rightUp, 
        &DancingCross::rightUp, &DancingCross::resetAnimation };  /**< Actions to perform when changing to the next frame */
};


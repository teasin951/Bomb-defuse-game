#include <Arduino.h>
#include <FastLED.h>
#include "definitions.h"

/**
 * @file Defines animations objects
*/

/* defining frames here to avoid dynamic allocation */
#define BLINKING_CROSS_FRAMES 2
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
    Animation();
    virtual ~Animation() = default;

    /**
     * @brief Resets the animation to the beggining
    */
    virtual void resetAnimation() {
        frame = 0;
        start_millis = millis();
    }

    /**
     * @brief Prepares the animation to be displayed
     * 
     * Most importantly, it sets the 'start_millis' variable to the current time.
    */
    virtual void setAnimation() {
        resetAnimation();
    }

    /**
     * @brief Checks if we are supposed to move to the next frame.
     * 
     * Should be called periodically.
    */
    virtual void checkFrame() {
        if( millis() > start_millis + (frame+1) * next_frame_in ) {
            if( frame >= frame_count - 1 ) {
                resetAnimation();
            }
            else {
                frame++;
            }
        }
    }

    /**
     * @brief Returns pixel values at a given index in the current frame
     * 
     * Used to set the 'leds' array for FastLED.h
     * Every child should redefine this to access the correct data
     * 
     * @return CRGB struct for a given pixel
    */
    virtual CRGB & getData( uint16_t index ) {
        return frames[frame][index];
    }

protected:
    uint32_t start_millis = 0;  /**< Millis when we switched to this animation */
    uint16_t frame = 0;  /**< Animation frame currently displayed */
    uint16_t frame_count = 1;  /**< Number of frames in the animation, change in constructor!!! */
    uint16_t next_frame_in = 40;  /**< ms between frames, change in constructor!!! */

    CRGB frames[1][NUM_LEDS];  /**< frames */
};


class BlinkingCross : public Animation {
public:
    BlinkingCross();
    virtual ~BlinkingCross() = default;

    virtual CRGB & getData( uint16_t index ) override {
        return frames[frame][index];
    }

private:

    CRGB frames[BLINKING_CROSS_FRAMES][NUM_LEDS];  /**< frames */
};


class DancingExcle : public Animation {
public:
    DancingExcle();
    virtual ~DancingExcle() = default;

    virtual CRGB & getData( uint16_t index ) override {
        return frames[frame][index];
    }

private:

    CRGB frames[DANCING_EXCLE_FRAMES][NUM_LEDS];  /**< frames */
};
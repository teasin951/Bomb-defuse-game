#pragma once
#include "../animations.h"


#define MOVING_ARROW_UP_FRAMES 2

class MovingArrowUp : public Animation {
public:
    MovingArrowUp() {
        frame_count = MOVING_ARROW_UP_FRAMES;
        next_frame_in = 750;
    }
    virtual ~MovingArrowUp() = default;

    bool resetAnimation( CRGB (&leds)[NUM_LEDS] ) override {
        canvas.

        frame = 0;
        start_millis = millis();

        return false;
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

}
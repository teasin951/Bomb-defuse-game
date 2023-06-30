#include "components/matrix/animations.h"
#include "components/matrix/definitions.h"

/**
 * @file Frame definition for BlinkingCross object
*/

CRGB BlinkingCross_frame0[NUM_X*NUM_Y] = {
    CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),
    CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),
    CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),
    CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),
    CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),
    CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),
    CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),
    CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),
};

CRGB BlinkingCross_frame1[NUM_X*NUM_Y] = {
    CRGB(246,187,0),CRGB(192,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(192,0,0),CRGB(246,187,0),
    CRGB(192,0,0),CRGB(246,187,0),CRGB(192,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(192,0,0),CRGB(246,187,0),CRGB(192,0,0),
    CRGB(0,0,0),CRGB(192,0,0),CRGB(246,187,0),CRGB(192,0,0),CRGB(192,0,0),CRGB(246,187,0),CRGB(192,0,0),CRGB(0,0,0),
    CRGB(0,0,0),CRGB(0,0,0),CRGB(192,0,0),CRGB(246,187,0),CRGB(246,187,0),CRGB(192,0,0),CRGB(0,0,0),CRGB(0,0,0),
    CRGB(0,0,0),CRGB(0,0,0),CRGB(192,0,0),CRGB(246,187,0),CRGB(246,187,0),CRGB(192,0,0),CRGB(0,0,0),CRGB(0,0,0),
    CRGB(0,0,0),CRGB(192,0,0),CRGB(246,187,0),CRGB(192,0,0),CRGB(192,0,0),CRGB(246,187,0),CRGB(192,0,0),CRGB(0,0,0),
    CRGB(192,0,0),CRGB(246,187,0),CRGB(192,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(192,0,0),CRGB(246,187,0),CRGB(192,0,0),
    CRGB(246,187,0),CRGB(192,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(192,0,0),CRGB(246,187,0),
};


BlinkingCross::BlinkingCross() {
    frame_count = BLINKING_CROSS_FRAMES;
    next_frame_in = 1000;

    memcpy(frames[0], BlinkingCross_frame0, sizeof(BlinkingCross_frame0));
    memcpy(frames[1], BlinkingCross_frame1, sizeof(BlinkingCross_frame1));
}
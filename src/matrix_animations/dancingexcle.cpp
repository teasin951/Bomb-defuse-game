#include "components/matrix/animations.h"
#include "components/matrix/definitions.h"

/**
 * @file Frame definition for DancingExcle object
*/

CRGB DancingExcle_frame0[NUM_X*NUM_Y] = {
    CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),
    CRGB(0,0,0),CRGB(192,0,0),CRGB(0,0,0),CRGB(192,0,0),CRGB(0,0,0),CRGB(192,0,0),CRGB(0,0,0),CRGB(0,0,0),
    CRGB(0,0,0),CRGB(192,0,0),CRGB(0,0,0),CRGB(192,0,0),CRGB(0,0,0),CRGB(192,0,0),CRGB(0,0,0),CRGB(0,0,0),
    CRGB(0,0,0),CRGB(192,0,0),CRGB(0,0,0),CRGB(192,0,0),CRGB(0,0,0),CRGB(192,0,0),CRGB(0,0,0),CRGB(0,0,0),
    CRGB(0,0,0),CRGB(192,0,0),CRGB(0,0,0),CRGB(192,0,0),CRGB(0,0,0),CRGB(192,0,0),CRGB(0,0,0),CRGB(0,0,0),
    CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),
    CRGB(0,0,0),CRGB(192,0,0),CRGB(0,0,0),CRGB(192,0,0),CRGB(0,0,0),CRGB(192,0,0),CRGB(0,0,0),CRGB(0,0,0),
    CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),
};

CRGB DancingExcle_frame1[NUM_X*NUM_Y] = {
    CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),
    CRGB(0,0,0),CRGB(0,0,0),CRGB(192,0,0),CRGB(0,0,0),CRGB(192,0,0),CRGB(0,0,0),CRGB(192,0,0),CRGB(0,0,0),
    CRGB(0,0,0),CRGB(0,0,0),CRGB(192,0,0),CRGB(0,0,0),CRGB(192,0,0),CRGB(0,0,0),CRGB(192,0,0),CRGB(0,0,0),
    CRGB(0,0,0),CRGB(0,0,0),CRGB(192,0,0),CRGB(0,0,0),CRGB(192,0,0),CRGB(0,0,0),CRGB(192,0,0),CRGB(0,0,0),
    CRGB(0,0,0),CRGB(0,0,0),CRGB(192,0,0),CRGB(0,0,0),CRGB(192,0,0),CRGB(0,0,0),CRGB(192,0,0),CRGB(0,0,0),
    CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),
    CRGB(0,0,0),CRGB(0,0,0),CRGB(192,0,0),CRGB(0,0,0),CRGB(192,0,0),CRGB(0,0,0),CRGB(192,0,0),CRGB(0,0,0),
    CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),CRGB(0,0,0),
};


DancingExcle::DancingExcle() {
    frame_count = BLINKING_CROSS_FRAMES;
    next_frame_in = 500;

    memcpy(frames[0], DancingExcle_frame0, sizeof(DancingExcle_frame0));
    memcpy(frames[1], DancingExcle_frame1, sizeof(DancingExcle_frame1));
}
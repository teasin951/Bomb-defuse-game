#pragma once
#include "../matrix.h"


#define MOVING_ARROW_UP_FRAMES 2


/**
 * @brief Moving arrow up animation class
*/
class MovingArrowUp : public Animation {
public:
    MovingArrowUp( GFXcanvas & x ) : Animation(x) {
        frame_count = MOVING_ARROW_UP_FRAMES;
        next_frame_in = 400;
    }
    virtual ~MovingArrowUp() = default;

    bool resetAnimation() override {
        canvas.fillScreen(CRGB::Black);
        canvas.drawLine(4, 0, 4, 7, CRGB::Green);
        canvas.drawLine(7, 3, 4, 0, CRGB::Green);
        canvas.drawLine(1, 3, 4, 0, CRGB::Green);

        frame = 0;
        start_millis = millis();

        return false;
    }

    void proceed() override {

        // time to change frames
        if( millis() > start_millis + (frame+1) * next_frame_in ) {

            // do asociated action and decide if we need frame advancement
            if( (this->*actions[frame])() ) {
                frame++;
            }
            FastLED.show();
        }
    }

    void setColour( CRGB & x ) {
        colour = x;
    }

private:
    bool (MovingArrowUp::*actions[MOVING_ARROW_UP_FRAMES])() = {&MovingArrowUp::moveLeft, &MovingArrowUp::resetAnimation}; 
    CRGB colour = CRGB::Green;

};

MovingArrowUp moving_arrow_up( canvas );  // predefine the animation object
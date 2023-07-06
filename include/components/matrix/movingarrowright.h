#pragma once
#include "../matrix.h"


#define MOVING_ARROW_RIGHT_FRAMES 2


class MovingArrowRight : public Animation {
public:
    MovingArrowRight( GFXcanvas & x ) : Animation(x) {
        frame_count = MOVING_ARROW_RIGHT_FRAMES;
        next_frame_in = 400;
    }
    virtual ~MovingArrowRight() = default;

    bool resetAnimation() override {
        canvas.fillScreen(CRGB::Black);
        canvas.drawLine(0, 4, 7, 4, CRGB::Green);
        canvas.drawLine(4, 1, 7, 4, CRGB::Green);
        canvas.drawLine(4, 7, 7, 4, CRGB::Green);

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
    bool (MovingArrowRight::*actions[MOVING_ARROW_RIGHT_FRAMES])() = {&MovingArrowRight::moveUp, &MovingArrowRight::resetAnimation}; 
    CRGB colour = CRGB::Green;

};

MovingArrowRight moving_arrow_right( canvas );  // predefine the animation object
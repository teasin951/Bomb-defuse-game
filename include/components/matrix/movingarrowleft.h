#pragma once
#include "../matrix.h"


#define MOVING_ARROW_LEFT_FRAMES 2


class MovingArrowLeft : public Animation {
public:
    MovingArrowLeft( GFXcanvas & x ) : Animation(x) {
        frame_count = MOVING_ARROW_LEFT_FRAMES;
        next_frame_in = 400;
    }
    virtual ~MovingArrowLeft() = default;

    bool resetAnimation() override {
        canvas.fillScreen(CRGB::Black);
        canvas.drawLine(0, 4, 7, 4, CRGB::Green);
        canvas.drawLine(3, 1, 0, 4, CRGB::Green);
        canvas.drawLine(3, 7, 0, 4, CRGB::Green);

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
    bool (MovingArrowLeft::*actions[MOVING_ARROW_LEFT_FRAMES])() = {&MovingArrowLeft::moveUp, &MovingArrowLeft::resetAnimation}; 
    CRGB colour;

};

MovingArrowLeft moving_arrow_left( canvas );  // predefine the animation object
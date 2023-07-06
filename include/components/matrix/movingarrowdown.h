#pragma once
#include "../matrix.h"


#define MOVING_ARROW_DOWN_FRAMES 2


class MovingArrowDown : public Animation {
public:
    MovingArrowDown( GFXcanvas & x ) : Animation(x) {
        frame_count = MOVING_ARROW_DOWN_FRAMES;
        next_frame_in = 400;
    }
    virtual ~MovingArrowDown() = default;

    bool resetAnimation() override {
        canvas.fillScreen(CRGB::Black);
        canvas.drawLine(4, 0, 4, 7, CRGB::Green);
        canvas.drawLine(7, 4, 4, 7, CRGB::Green);
        canvas.drawLine(1, 4, 4, 7, CRGB::Green);

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
    bool (MovingArrowDown::*actions[MOVING_ARROW_DOWN_FRAMES])() = {&MovingArrowDown::moveLeft, &MovingArrowDown::resetAnimation}; 
    CRGB colour;

};

MovingArrowDown moving_arrow_down( canvas );  // predefine the animation object

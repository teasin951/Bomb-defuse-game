#pragma once
#include "../matrix.h"


#define LOADING_CIRCLE_FRAMES 20


/**
 * @brief Loading circle up animation class
*/
class LoadingCircle : public Animation {
public:
    LoadingCircle( GFXcanvas & x ) : Animation(x) {
        frame_count = LOADING_CIRCLE_FRAMES;
        next_frame_in = 100;
    }
    virtual ~LoadingCircle() = default;

    bool resetAnimation() override {
        canvas.fillScreen(CRGB::Black);

        frame = 0;
        start_millis = millis();
        animation_done = true;

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

    bool setOne() {
        canvas.drawPixel(2, 4, colour);
        return true;
    }
    bool setTwo() {
        canvas.drawPixel(2, 3, colour);
        return true;
    }
    bool setThree() {
        canvas.drawPixel(3, 2, colour);
        return true;
    }
    bool setFour() {
        canvas.drawPixel(4, 2, colour);
        return true;
    }
    bool setFive() {
        canvas.drawPixel(5, 3, colour);
        return true;
    }
    bool setSix() {
        canvas.drawPixel(5, 4, colour);
        return true;
    }
    bool setSeven() {
        canvas.drawPixel(4, 5, colour);
        return true;
    }
    bool setEight() {
        canvas.drawPixel(3, 5, colour);
        return true;
    }

    bool wait() {
        return true;
    }

    void setColour( CRGB & x ) {
        colour = x;
    }

private:
    bool (LoadingCircle::*actions[LOADING_CIRCLE_FRAMES])() = {&LoadingCircle::setOne, &LoadingCircle::wait, 
                                                                &LoadingCircle::setTwo, &LoadingCircle::wait,
                                                                &LoadingCircle::setThree, &LoadingCircle::wait, 
                                                                &LoadingCircle::setFour, &LoadingCircle::wait,
                                                                &LoadingCircle::setFive, &LoadingCircle::wait, &LoadingCircle::wait, &LoadingCircle::wait, 
                                                                &LoadingCircle::setSix, &LoadingCircle::wait, &LoadingCircle::wait, &LoadingCircle::wait,
                                                                &LoadingCircle::setSeven,
                                                                &LoadingCircle::setEight, &LoadingCircle::wait,
                                                                &LoadingCircle::resetAnimation}; 
    CRGB colour = CRGB::Yellow;

};

LoadingCircle loading_circle( canvas );  // predefine the animation object

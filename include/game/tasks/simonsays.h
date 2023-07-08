#pragma once
#include <Arduino.h>
#include <tinyfsm.hpp>
#include "../variables.h"
#include "../events.h"
#include "components/pins.h"


class SimonSays : public tinyfsm::Fsm<SimonSays> {
    virtual void react( KeypadThreePressed const & ) {
        tone(BUZZER_1, 400, 200);
    }

};


class InitSimon : public SimonSays {

};

FSM_INITIAL_STATE(SimonSays, InitSimon);
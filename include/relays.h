#pragma once
#include <Arduino.h>
#include "pins.h"


/**
 * @brief Relay state
*/
struct Relays {
    bool rel1 = false;
    bool rel2 = false;
    bool rel3 = false;
    bool rel4 = false;
};
struct Relays relays;


/**
 * @brief Set relays
 * 
 * @param in1 Relay one
 * @param in2 Relay two
 * @param in3 Relay three
 * @param in4 Relay four
*/
void setRelays( bool in1, bool in2, bool in3, bool in4 ) {
    digitalWrite(RELAY_1, in1);
    digitalWrite(RELAY_2, in1);
    digitalWrite(RELAY_3, in1);
    digitalWrite(RELAY_4, in1);

    relays.rel1 = in1;
    relays.rel2 = in2;
    relays.rel3 = in3;
    relays.rel4 = in4;
}
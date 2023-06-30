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
void setRelays(bool in1, bool in2, bool in3, bool in4 ) {
    if( in1 )
        digitalWrite(RELAY_1, LOW);
    else
        digitalWrite(RELAY_1, HIGH);

    if( in2 )
        digitalWrite(RELAY_2, LOW);
    else
        digitalWrite(RELAY_2, HIGH);

    if( in3 )
        digitalWrite(RELAY_3, LOW);
    else
        digitalWrite(RELAY_3, HIGH);

    if( in4 )
        digitalWrite(RELAY_4, LOW);
    else
        digitalWrite(RELAY_4, HIGH);


    relays.rel1 = in1;
    relays.rel2 = in2;
    relays.rel3 = in3;
    relays.rel4 = in4;
}
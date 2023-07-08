#pragma once
#include <Arduino.h>


/**
 * @file Global variables needed in basically every game for different purposes
*/

uint32_t game_start_millis = 0;  /**< When did the game start */
uint32_t game_countdown_amount = 900000;  /**< How long for a game, default: 15 min*/

/**
 * When a task is finished, this should be set to true,
 * GameXXX checks for it, and advances
*/
bool task_completed = false;

bool game_is_live = true;


typedef struct GameTime {
    uint8_t minutes;
    uint8_t seconds;
} GAMETIME;

// Reset the arduino function
void(* resetArduino) (void) = 0;

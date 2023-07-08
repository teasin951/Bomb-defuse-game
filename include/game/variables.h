#pragma once
#include <Arduino.h>


uint32_t game_start_millis = 0;  /**< When did the game start */
uint32_t game_countdown_amount = 900000;  /**< How long for a game, default: 15 min*/
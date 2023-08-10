#pragma once
#include <Arduino.h>


/**
 * @file Global variables needed in basically every game
*/

uint32_t game_start_millis = 0;  /**< When did the game start */
uint32_t game_countdown_amount = 900000;  /**< How long for a game, default: 15 min*/
uint32_t game_countdown_penalty = 0;  /**< To make the countdown faster, this will be subtracted from time every second */
uint8_t mistakes_count = 0;  /**< For games that count mistakes, should be checked for on Update in GameXXXX */
uint8_t tasks_finished = 0;  /**< Count how many games have been sucessfully finished */

/**
 * When a task is finished, this should be set to true,
 * GameXXX checks for it, and advances
*/
bool task_completed = false;

bool game_is_live = true;  /**< The game is on going */
bool bomb_beep = true;  /**< The bomb should beep*/
bool update_time = true;  /**< Games can set if the time should advance */
bool last_task = false;  /**< Should be set to true if this is the last task of the game */

uint8_t times_played[20];  /**< How many times has each task been played, MAX NUMBER OF DIFFERENT TASKS == 20 !! */


/**
 * @brief Game time structure parsed to minutes and seconds
*/
typedef struct GameTime {
    int8_t minutes;
    int8_t seconds;
} GAMETIME;
GAMETIME game_time;


/**
 * @brief Reset the arduino function
*/
void(* resetArduino) (void) = 0;

#pragma once
#include <Arduino.h>

/**
 * @file definitions of structs holding game data
 */


/**
 * @brief Data structure with all important information about the game state
 */
struct Game {
    uint8_t countdown_sec;  /**< How long should the game last */
    uint32_t start_timestamp;  /**< When has the game started*/
};

/**
 * @brief Scenario for the first time playing 
 */
struct FirstScenario : public Game {
    uint8_t countdown_sec = 360;
   
};

/**
 * @brief Scenario for the second time playing 
 */
struct SecondScenario : public Game {
   
};

/**
 * @brief Scenario for the third time 
 */
struct ThirdScenario : public Game {
   
};

/**
 * @brief Scenario for already experienced
 */
struct Hard : public Game {
   
};

/**
 * @brief Scenario for players hungry for a challange
 */
struct Suicide : public Game {
   
};


/**
 * @brief enum for gamemodes
*/
enum GameMode {
    FIRST_SCENARIO = 0,
    SECOND_SCENARIO = 1,
    THIRD_SCENARIO = 3,
    HARD = 4,
    SUICIDE = 5
};


/**
 * @brief enum for button states
*/
enum ButtonState {
    RELEASED = 0,
    PRESSED = 1,
    HELD = 2
};

/**
 * @brief Relay state
*/
struct Relays {
    bool rel1 = false;
    bool rel2 = false;
    bool rel3 = false;
    bool rel4 = false;
};
#pragma once
#include <Arduino.h>
#include <NonBlockingRtttl.h>
#include "pins.h"


/**
 * @file Melodies for rtttl::play(BUZZER, melody);
*/

// const char * mario = "mario:d=4,o=5,b=100:16e6,16e6,32p,8e6,16c6,8e6,8g6,8p,8g,8p,8c6,16p,8g,16p,8e,16p,8a,8b,16a#,8a,16g.,16e6,16g6,8a6,16f6,8g6,8e6,16c6,16d6,8b,16p,8c6,16p,8g,16p,8e,16p,8a,8b,16a#,8a,16g.,16e6,16g6,8a6,16f6,8g6,8e6,16c6,16d6,8b,8p,16g6,16f#6,16f6,16d#6,16p,16e6,16p,16g#,16a,16c6,16p,16a,16c6,16d6,8p,16g6,16f#6,16f6,16d#6,16p,16e6,16p,16c7,16p,16c7,16c7,p,16g6,16f#6,16f6,16d#6,16p,16e6,16p,16g#,16a,16c6,16p,16a,16c6,16d6,8p,16d#6,8p,16d6,8p,16c6";
const char * test_mario = "mario:d=4,o=5,b=100:16e6,16e6,32p,8e6,16c6,8e6,8g6,8p,8g,8p,8c6";
const char * test_overflow = "t:d=4,o=5,b=120:16a4,32p,16a4,32p,4a4";

const char * game_pick = "g:d=4,o=4,b=140:16g#5,16d#6,16g#6";
const char * bomb_exploded = "g:d=4,o=4,b=20:c6";
const char * task_finished = "f:d=4,o=4,b=130:16c6,16a5,8c7";
const char * fail_waiting = "g:d=4,o=4,b=120:c#4,p";
const char * bomb_defused = "w:d=4,o=4,b=130:32p,8a6,16g6,16p,16e6,16p,16g6,16p,8f6,8a6,16d7,16a7,16g7,16a7";
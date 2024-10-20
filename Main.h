#ifndef MAIN_H
#define MAIN_H
#define _GLIBCXX_DEBUG
using namespace std;

#include "raylib.h"
//#include <iostream>
#include <string>
#include <ctime>
#include <cmath>
#include <vector>
#include <variant>
#include <array>
#include <cstdint>

//Screen dimension constants
const long SCREEN_WIDTH{480};
const long SCREEN_HEIGHT{320};
const long SCREEN_FPS{60};

//Analog joystick dead zone
//const long JOYSTICK_DEAD_ZONE{8000};

const string WINDOW_TEXT = "RPG";

//sound settings
//const long SOUND_FREQUENCY{44100};
//const long NUM_HARDWARE_CHANNELS{2}; // Stereo
//const long SAMPLE_SIZE{2048};
//const long NUM_MIX_CHANNELS{16};

extern long mem;

#include "Consts/Game_Consts.h"
#include "Consts/Media.h"
#include "Functions.h"
#include "Script_Structs.h"
#include "Consts/Storyboard_Consts.h"
#include "Consts/Map_Consts.h"

#endif

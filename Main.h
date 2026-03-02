#ifndef MAIN_H
#define MAIN_H

using namespace std;

#include <raylib.h>
//#include <iostream>
#include <string>
#include <ctime>
#include <cmath>
#include <vector>
#include <variant>
#include <array>
#include <cstdint>
#include <thread>
#include <any>
#include <queue>
#include <tuple>

//Screen dimension constants
const long SCREEN_WIDTH{600};
const long SCREEN_HEIGHT{400};
const long SCREEN_FPS{60};
const double FRAME_LENGTH_IN_SECONDS{1 / static_cast<double>(SCREEN_FPS)};

//Analog joystick dead zone
//const long JOYSTICK_DEAD_ZONE{8000};

const string WINDOW_TEXT = "My Little Pony RPG: The Elements of Harmony Remastered";

extern long mem;

#include "Consts/Game_Consts.h"
#include "Consts/Media.h"
#include "Functions.h"
#include "Script.h"
#include "Consts/Storyboard_Consts.h"
#include "Consts/Map_Consts.h"

extern const Sound_Player* g_sound_player;

#endif

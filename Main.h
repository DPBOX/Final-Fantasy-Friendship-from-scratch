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
#include <thread>
#include <any>

//Screen dimension constants
const long SCREEN_WIDTH{480};
const long SCREEN_HEIGHT{320};
const long SCREEN_FPS{60};
const double FRAME_LENGTH_IN_SECONDS{1 / static_cast<double>(SCREEN_FPS)};

//Analog joystick dead zone
//const long JOYSTICK_DEAD_ZONE{8000};

const string WINDOW_TEXT = "RPG";

extern long mem;

#include "Consts/Game_Consts.h"
#include "Consts/Media.h"
#include "Functions.h"
#include "Script_Structs.h"
#include "Consts/Storyboard_Consts.h"
#include "Consts/Map_Consts.h"

extern const Sound_Player* g_sound_player;

#endif

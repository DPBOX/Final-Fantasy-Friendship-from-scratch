#ifndef WORLD_CONSTS_H
#define WORLD_CONSTS_H

const long MAX_PARTY_SIZE{6};

const long HERO_WIDTH{48};
const double HERO_VELOCITY{3};
const long TILE_ANIMATION_SPEED{12};
const long MAP_TILE_WIDTH{32};

const long PLAYER_Y_COLLISION_POINT_DOWN{2};
const long PLAYER_Y_COLLISION_POINT_UP{16};
const long PLAYER_X_COLLISION_POINT{12};

// Number of frames that pass until the animation frame switches. 1 means that the animation frame will switch every frame.
const long HERO_ANIMATION_SPEED{8};
const long CHANGELING_ANIMATION_SPEED{1};
const long BLINKING_ANIMATION_SPEED{8};

// You must press and release a movement key within this number of frames to turn
const long HERO_TURNING_SPEED{0};

// Which frame index in the starting animation to start on
const long HERO_START_FRAME{3};

const vector<long> HERO_ANIM_UP{13, 14, 15, 12};
const vector<long> HERO_ANIM_RIGHT{9, 10, 11, 8};
const vector<long> HERO_ANIM_DOWN{1, 2, 3, 0};
const vector<long> HERO_ANIM_LEFT{5, 6, 7, 4};
const vector<long> HERO_ANIM_BATTLE_IDLE{16};
const vector<long> HERO_ANIM_BATTLE_GUARD{17};

const long MAX_LEVEL{99};
const long MAX_SPEED{510};

#endif

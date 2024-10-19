#ifndef GAME_CONSTS_H
#define GAME_CONSTS_H

const long PLAYER_SUMMARY_SECTION_PADDING{6};
const long PLAYER_SUMMARY_PROGRESS_BAR_TEXT_OFFSET{-4};
const long PLAYER_SUMMARY_PROGRESS_BAR_BAR_OFFSET{-6};
const long PLAYER_SUMMARY_ROW_OFFSET{16};
const long PLAYER_SUMMARY_SECTION_WIDTH{80};
const long PLAYER_SUMMARY_PROGRESS_BAR_LENGTH{72};
const long STATUS_PROGRESS_BAR_PADDING{8};
const long TEXT_FONT_HEIGHT{16};
const double PLAYER_SUMMARY_ROW_PORTRAIT_TWEEN_TIME{.05};

const long CONSUMABLE_ITEM_ICON{17};
const long KEY_ITEM_ICON{18};

const vector<string> FORMATION_MENU_TEXT{"Up/Down: Select char.", "Left/Right: Char. row", "A: Switch characters", "", "The character at the", "top is the leader and", "the one you will", "control. Characters in", "the front row will", "give and take normal", "damage. Characters", "in the back row will", "give and take half", "damage. Some", "weapons and abilities", "can do normal damage", "from the back row.", ""};
const vector<string> STAT_STRINGS{"Strength", "Attack", "Weapon", "Speed", "Defense", "Shield", "Intellect", "Resistance", "Helm", "Stamina", "Accuracy", "Armor", "Spirit", "Critical", "Accessory 1", "Evasion", "Magic Evasion", "Accessory 2"};
const vector<string> STAT_DESCRIPTIONS_LINE_1{"Increasing Strength will make your physical attacks such as the Attack command deal more", "Increasing Attack will make your physical attacks such as the Attack command deal more", "", "Increasing Speed will make the ATB bar fill up faster.", "Increasing Defense will make you take less damage from physical attacks.", "", "Increasing Intellect will make your magical attacks do more damage to enemies.", "Increasing Resistance will make you take less damage from magical attacks.", "", "Increasing Stamina will increase your maximum HP.", "Increasing Accuracy will make your attacks miss less." , "", "Increasing Spirit will increase your maximum MP.", "Increasing Critical will make the Attack command more likely to be a critical hit and do a lot", "", "Increasing Evasion will make enemies' physical attacks miss more often.", "Increasing Magic Evasion will make enemies' magical attacks miss more often.", ""};
const vector<string> STAT_DESCRIPTIONS_LINE_2{"damage to enemies. It can be increased by levelling up.", "damage to enemies. Only equipment can change it.", "", "It can be increased by levelling up.", "Only equipment can change it.", "", "It can be increased by levelling up.", "Only equipment can change it.", "", "It can be increased by levelling up.", "Only equipment can change it.", "", "It can be increased by levelling up.", "more damage. Only equipment can change it.", "", "Only equipment can change it.", "Only equipment can change it.", ""};

const long ALPHA_MAX{255};
const double VOLUME_MAX{1};

const double MAX_PROGRESS_BAR_VALUE{100};

const long AVATAR_WIDTH{81};
const long INTRO_CAPTION_HEIGHT{80};

// Padding for the text boxes.
const long TEXTBOX_PADDING_SCREEN{16};
const long TEXTBOX_PADDING_SCREEN_Y{12};
const long TEXTBOX_PADDING_LONG{8};
const long TEXTBOX_PADDING_SHORT{4};

const long PANEL_TILE_WIDTH{3};
const long PANEL_ALPHA{192};

// Number of frames it takes for the window growing and shrinking animation to complete.
const long PANEL_SPEED{8};

// How many frames the continue arrow blinking animation lasts when there's more than 1 page of text left in a text box.
const long CONTINUE_ARROW_INTERVAL{15};

const vector<long> CONTINUE_ARROW_ANIMATION_FRAMES{1, 0};
const long CONTINUE_ARROW_ANIMATION_START_FRAME{1};

const vector<long> CURSOR_ANIM{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 0};

// Number of frames that pass until the animation frame switches. 1 means that the animation frame will switch every frame.
const long CURSOR_ANIMATION_SPEED{3};
const long CURSOR_WIDTH{35};

// Where the cursor is in relation to where it's pointing to.
const long CURSOR_PADDING_X{-36};
const long CURSOR_PADDING_Y{-18};

// The cursor is always displayed. This is where it goes when it's not in use, which is offscreen where it can't be seen.
const long CURSOR_START_X{-64};
const long CURSOR_START_Y{-64};

// How many seconds it takes for the cursor to move to a new position
const double CURSOR_MOVE_TIME{.1};

const long NUM_FONT_CELLS{123};

const long FONT_TEXT_CELL_WIDTH{16};
const array<long, NUM_FONT_CELLS> FONT_TEXT_CHAR_WIDTHS{0, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 4, 4, 4, 16, 16, 16, 16, 2, 4, 4, 16, 6, 3, 5, 2, 5, 6, 3, 6, 6, 6, 6, 6, 6, 6, 6, 2, 16, 16, 16, 16, 6, 16, 6, 6, 6, 6, 5, 5, 6, 6, 4, 6, 6, 5, 8, 6, 6, 6, 6, 6, 6, 6, 6, 6, 10, 6, 6, 6, 16, 16, 16, 16, 16, 16, 5, 5, 5, 5, 5, 5, 5, 5, 3, 3, 5, 3, 8, 5, 5, 5, 5, 5, 5, 4, 5, 6, 8, 6, 5, 5};
const long FONT_TEXT_HEIGHT{16};

const long FONT_HEADING_CELL_WIDTH{25};
const array<long, NUM_FONT_CELLS> FONT_HEADING_CHAR_WIDTHS{0, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 25, 25, 25, 25, 25, 16, 5, 8, 25, 25, 25, 14, 5, 25, 25, 25, 12, 6, 8, 4, 9, 14, 7, 12, 13, 14, 13, 14, 12, 14, 14, 4, 6, 25, 25, 25, 11, 25, 14, 13, 12, 12, 12, 11, 15, 12, 5, 11, 12, 10, 15, 12, 13, 12, 14, 13, 13, 12, 11, 12, 16, 11, 14, 13, 25, 25, 25, 25, 25, 25, 11, 10, 10, 11, 10, 10, 10, 10, 4, 7, 9, 4, 15, 10, 11, 10, 13, 9, 11, 11, 10, 10, 13, 10, 11, 11};
const long FONT_HEADING_HEIGHT{25};

const long NUM_FRONT_MENU_COLUMNS{1};
const long FRONT_MENU_SPLIT{4};
const long NUM_FRONT_MENU_CHOICES{5};
const vector<string> FRONT_MENU_CHOICES{"Items", "Magic", "Status and Equipment", "Formation", "Save"};

const long NUM_ITEM_MENU_CHOICES{3};
const long ITEM_MENU_SPLIT{3};
const vector<string> ITEM_MENU_CHOICES{"Items", "Key Items"};
const double ITEM_QUANTITY_LOCATION_FRACTION{.75};
const double STAT_LOCATION_FRACTION{.5};
const long ICON_WIDTH{18};
const long ITEM_MENU_ROWS{15};
const long MAX_ITEM_MENU_ROWS{500};
const long NUM_ITEM_MENU_COLUMNS{2};
const long STATUS_MENU_ROWS{6};
const long NUM_STATUS_MENU_COLUMNS{3};

const long MAX_PARTY_SIZE{3};

const long NUM_EQUIPMENT_MENU_COLUMNS{1};
const long MAX_NUM_EQUIPMENT_MENU_ROWS{500};
const long NUM_EQUIPMENT_MENU_ROWS{9};

const long HERO_WIDTH{48};
const double HERO_VELOCITY{3};

// Number of frames that pass until the animation frame switches. 1 means that the animation frame will switch every frame.
const long HERO_ANIMATION_SPEED{8};

// You must press and release a movement key within this number of frames to turn
const long HERO_TURNING_SPEED{0};

// Which frame index in the starting animation to start on
const long HERO_START_FRAME{3};

const vector<long> HERO_ANIM_UP{13, 14, 15, 12};
const vector<long> HERO_ANIM_RIGHT{9, 10, 11, 8};
const vector<long> HERO_ANIM_DOWN{1, 2, 3, 0};
const vector<long> HERO_ANIM_LEFT{5, 6, 7, 4};

const long MAX_LEVEL{99};
const long DEFAULT_ATTACK{1};
const long DEFAULT_ACCURACY{100};
const long EXP_BASE{40};
const long EXP_INFLATION{40};

const long BATTLE_TRANSITION_FRAMES{600};

const array<long, MAX_LEVEL> TEMPEST_SPIRIT_GROWTH{11, 12, 12, 13, 14, 14, 15, 15, 16, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 23, 23, 24, 24, 24, 25, 25, 26, 27, 28, 28, 29, 29, 29, 30, 30, 31, 32, 32, 33, 34, 34, 35, 35, 36, 37, 37, 38, 38, 39, 40, 40, 40, 41, 41, 41, 42, 42, 43, 43, 44, 44, 45, 45, 45, 46, 46, 47, 48, 48, 48, 48, 49, 49, 50, 50, 51, 51, 51, 51, 52, 52, 52, 52, 53, 53, 54, 55, 56, 56, 56, 56, 57, 58, 58, 59, 59, 59, 60, 60};
const array<long, MAX_LEVEL> TEMPEST_STAMINA_GROWTH{13, 14, 15, 15, 16, 17, 17, 18, 18, 19, 20, 20, 21, 22, 22, 23, 23, 24, 24, 25, 25, 26, 27, 27, 28, 28, 29, 30, 30, 31, 32, 32, 33, 34, 35, 36, 36, 37, 38, 39, 40, 41, 41, 42, 42, 43, 44, 44, 44, 45, 46, 47, 48, 48, 49, 50, 51, 52, 52, 53, 53, 54, 55, 56, 56, 57, 57, 58, 58, 59, 59, 59, 60, 60, 60, 61, 61, 61, 62, 62, 63, 64, 64, 64, 65, 66, 67, 68, 68, 69, 69, 70, 70, 71, 71, 72, 72, 72, 73};
const array<long, MAX_LEVEL> TEMPEST_STRENGTH_GROWTH{28, 29, 30, 30, 31, 32, 32, 33, 33, 34, 35, 35, 35, 36, 36, 36, 37, 37, 37, 38, 38, 39, 39, 39, 40, 40, 41, 42, 42, 43, 43, 44, 44, 44, 45, 45, 46, 46, 47, 47, 48, 49, 49, 50, 50, 50, 51, 51, 52, 53, 54, 55, 56, 56, 57, 58, 58, 59, 59, 60, 60, 61, 62, 62, 63, 63, 64, 65, 65, 66, 66, 67, 67, 68, 68, 69, 69, 70, 71, 71, 72, 73, 74, 74, 75, 75, 75, 76, 76, 77, 78, 78, 79, 79, 80, 81, 82, 83, 84};
const array<long, MAX_LEVEL> TEMPEST_INTELLECT_GROWTH{18, 19, 20, 21, 22, 22, 23, 23, 24, 25, 26, 26, 27, 28, 29, 29, 30, 30, 31, 32, 33, 34, 35, 36, 37, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 71, 72, 73, 73, 74, 75, 76, 76, 77, 78, 79, 80, 80, 81, 82, 83, 84, 84, 85, 86, 87, 88, 89, 90, 90, 91, 91, 92, 93, 94, 95, 95, 96, 96, 97, 97, 98, 98, 98};

const array<long, MAX_LEVEL> NIGHTWISH_SPIRIT_GROWTH{15, 16, 16, 17, 17, 18, 18, 19, 19, 20, 21, 22, 22, 23, 24, 24, 25, 26, 26, 26, 27, 27, 27, 28, 28, 29, 30, 30, 31, 32, 32, 33, 33, 33, 34, 34, 35, 36, 36, 37, 38, 39, 39, 40, 41, 41, 41, 42, 42, 43, 44, 44, 45, 45, 46, 46, 47, 48, 49, 49, 49, 50, 50, 51, 52, 52, 52, 53, 53, 53, 53, 54, 54, 55, 56, 56, 57, 57, 58, 59, 59, 60, 61, 61, 61, 62, 62, 63, 63, 63, 64, 64, 65, 65, 66, 67, 67, 68, 68};
const array<long, MAX_LEVEL> NIGHTWISH_STAMINA_GROWTH{17, 18, 19, 19, 21, 22, 22, 23, 24, 26, 26, 28, 29, 30, 31, 31, 33, 33, 35, 36, 37, 37, 38, 39, 40, 40, 41, 41, 42, 42, 43, 44, 45, 45, 46, 47, 47, 48, 49, 49, 50, 50, 51, 52, 52, 53, 53, 53, 54, 55, 55, 56, 57, 57, 58, 59, 60, 60, 61, 62, 63, 63, 64, 65, 66, 68, 68, 69, 70, 70, 71, 71, 72, 73, 73, 75, 75, 76, 77, 78, 78, 79, 79, 80, 80, 81, 81, 82, 82, 82, 83, 84, 84, 85, 85, 86, 86, 86, 86};
const array<long, MAX_LEVEL> NIGHTWISH_STRENGTH_GROWTH{22, 23, 24, 24, 25, 25, 25, 26, 26, 27, 27, 28, 28, 28, 29, 30, 30, 31, 32, 32, 32, 33, 33, 33, 34, 34, 35, 36, 36, 37, 37, 38, 38, 38, 39, 39, 39, 40, 40, 41, 41, 42, 42, 42, 43, 43, 44, 45, 45, 45, 45, 46, 46, 47, 48, 48, 49, 49, 49, 50, 50, 51, 52, 52, 53, 53, 53, 54, 54, 55, 55, 56, 56, 57, 58, 58, 59, 59, 59, 60, 60, 61, 61, 62, 62, 63, 63, 64, 64, 65, 66, 66, 66, 67, 67, 67, 68, 69, 70};
const array<long, MAX_LEVEL> NIGHTWISH_INTELLECT_GROWTH{24, 25, 26, 27, 28, 29, 30, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 41, 42, 42, 43, 44, 45, 46, 47, 48, 50, 50, 51, 52, 53, 54, 54, 55, 56, 57, 58, 59, 60, 62, 62, 63, 64, 65, 66, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 78, 80, 81, 81, 82, 83, 84, 85, 86, 87, 88, 89, 89, 90, 91, 92, 93, 94, 95, 95, 96, 97, 98, 99, 99, 100, 101, 102, 103, 105, 105, 106, 107, 108, 108, 109, 109, 110, 111, 111, 112, 113, 113};

const array<long, MAX_LEVEL> GALLUS_SPIRIT_GROWTH{8, 9, 10, 10, 10, 10, 11, 11, 12, 12, 12, 12, 12, 13, 13, 13, 14, 14, 15, 16, 17, 17, 17, 18, 18, 18, 19, 19, 20, 20, 21, 21, 21, 22, 22, 23, 24, 25, 25, 26, 26, 26, 26, 26, 27, 27, 28, 28, 29, 29, 30, 30, 30, 31, 31, 32, 33, 33, 34, 35, 35, 36, 36, 36, 37, 38, 39, 39, 39, 39, 40, 40, 40, 41, 42, 42, 43, 43, 44, 44, 45, 45, 45, 46, 46, 47, 47, 48, 48, 48, 49, 49, 49, 50, 50, 50, 50, 50, 51};
const array<long, MAX_LEVEL> GALLUS_STAMINA_GROWTH{12, 13, 13, 14, 14, 15, 15, 15, 16, 16, 17, 17, 18, 19, 19, 20, 20, 20, 21, 21, 22, 22, 23, 23, 24, 24, 25, 25, 26, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36, 36, 37, 38, 38, 39, 39, 40, 41, 42, 42, 43, 44, 44, 45, 45, 46, 46, 47, 47, 48, 49, 49, 50, 50, 51, 51, 52, 52, 53, 53, 54, 54, 55, 56, 56, 57, 58, 58, 59, 59, 60, 60, 60, 61, 61, 61, 61, 62, 62, 63, 63, 64, 64, 65, 65};
const array<long, MAX_LEVEL> GALLUS_STRENGTH_GROWTH{34, 34, 35, 36, 36, 37, 38, 38, 39, 39, 39, 40, 41, 42, 43, 43, 44, 45, 45, 45, 46, 46, 47, 48, 48, 48, 49, 49, 49, 50, 51, 51, 52, 53, 53, 53, 54, 54, 55, 56, 57, 57, 57, 58, 58, 59, 60, 60, 61, 62, 62, 63, 63, 64, 65, 66, 67, 68, 68, 69, 70, 70, 71, 72, 72, 73, 73, 73, 74, 75, 75, 76, 76, 77, 77, 77, 78, 78, 79, 80, 80, 81, 81, 82, 83, 83, 83, 84, 84, 85, 86, 86, 87, 87, 87, 88, 88, 89, 90};
const array<long, MAX_LEVEL> GALLUS_INTELLECT_GROWTH{5, 5, 6, 6, 7, 7, 7, 8, 8, 9, 9, 10, 11, 12, 12, 13, 13, 14, 14, 15, 16, 17, 17, 18, 18, 19, 19, 20, 20, 21, 22, 23, 24, 25, 25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 33, 34, 34, 35, 36, 37, 37, 38, 39, 40, 41, 42, 43, 44, 44, 45, 46, 47, 48, 49, 49, 49, 50, 50, 51, 52, 53, 54, 55, 56, 56, 57, 57, 57, 57, 58, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76};

#endif

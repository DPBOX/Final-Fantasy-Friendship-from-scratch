#ifndef UI_CONSTS_H
#define UI_CONSTS_H

const long PLAYER_SUMMARY_SECTION_PADDING_X{16};
const long PLAYER_SUMMARY_SECTION_PADDING_Y{16};
const long PLAYER_SUMMARY_PROGRESS_BAR_TEXT_OFFSET{-4};
const long PLAYER_SUMMARY_PROGRESS_BAR_BAR_OFFSET{-6};
const long PLAYER_SUMMARY_SECTION_WIDTH{112};
const long PLAYER_SUMMARY_PROGRESS_BAR_LENGTH{96};
const long PLAYER_SUMMARY_SECTIONS{4};
const long PLAYER_SUMMARY_HEIGHT_IN_TILES{3};
const long PLAYER_SUMMARY_PORTRAIT_OFFSET{-48};
const long STATUS_PROGRESS_BAR_PADDING{8};
const long TEXT_FONT_HEIGHT{16};
const double PLAYER_SUMMARY_ROW_PORTRAIT_TWEEN_TIME{.05};

const long CONSUMABLE_ITEM_ICON{17};
const long KEY_ITEM_ICON{18};

const vector<string> STAT_STRINGS{"Attack", "Hooves", "Defense", "Armor", "Magic", "Accessory", "Speed"};
const vector<string> STAT_DESCRIPTIONS_LINE_1{"Increasing Attack will make your physical attacks such as the Attack command deal more damage to enemies.", "", "Increasing Defense will make you take less damage from physical attacks.", "", "Increasing Magic will make your magic attacks do more damage and make you take less damage from magic attacks.", "", "Increasing Speed will make you able to attack earlier."};

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

const long FONT_HEADING_CELL_WIDTH{25};
const array<long, NUM_FONT_CELLS> FONT_HEADING_CHAR_WIDTHS{0, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 25, 25, 25, 25, 25, 16, 5, 8, 25, 25, 25, 14, 5, 25, 25, 25, 12, 6, 8, 4, 9, 14, 7, 12, 13, 14, 13, 14, 12, 14, 14, 4, 6, 25, 25, 25, 11, 25, 14, 13, 12, 12, 12, 11, 15, 12, 5, 11, 12, 10, 15, 12, 13, 12, 14, 13, 13, 12, 11, 12, 16, 11, 14, 13, 25, 25, 25, 25, 25, 25, 11, 10, 10, 11, 10, 10, 10, 10, 4, 7, 9, 4, 15, 10, 11, 10, 13, 9, 11, 11, 10, 10, 13, 10, 11, 11};
const long FONT_HEADING_HEIGHT{25};

const long NUM_FRONT_MENU_COLUMNS{1};
const long FRONT_MENU_SPLIT{4};
const long NUM_FRONT_MENU_CHOICES{5};
const vector<string> FRONT_MENU_CHOICES{"Items", "Skills", "Status and Equipment", "Formation", "Save"};

const long NUM_ITEM_MENU_CHOICES{2};
const long ITEM_MENU_SPLIT{3};
const vector<string> ITEM_MENU_CHOICES{"Items", "Key Items"};
const double ITEM_QUANTITY_LOCATION_FRACTION{.75};
const double EQUIPMENT_QUANTITY_LOCATION_FRACTION{.75};
const double STAT_LOCATION_FRACTION{.5};
const long ICON_WIDTH{16};
const long ICON_PADDING{2};
const long ITEM_MENU_ROWS{15};
const long MAX_ITEM_MENU_ROWS{500};
const long NUM_ITEM_MENU_COLUMNS{4};
const long STATUS_MENU_ROWS{4};
const long NUM_STATUS_MENU_COLUMNS{2};
const long STATUS_MENU_SPLIT{7};

const long NUM_EQUIPMENT_MENU_COLUMNS{1};
const long MAX_NUM_EQUIPMENT_MENU_ROWS{500};
const long NUM_EQUIPMENT_MENU_ROWS{9};

// Padding for the text boxes.
const long PANEL_SCREEN_OFFSET_X{16};
const long PANEL_SCREEN_OFFSET_Y{12};
const long TEXTBOX_PANEL_OFFSET_X{8};
const long TEXTBOX_PANEL_OFFSET_Y{4};

const long PANEL_MENU_UL_X{PANEL_SCREEN_OFFSET_X};
const long PANEL_MENU_UL_Y{PANEL_SCREEN_OFFSET_Y};
const long TEXTBOX_MENU_UL_X{PANEL_MENU_UL_X + TEXTBOX_PANEL_OFFSET_X};
const long TEXTBOX_MENU_UL_Y{PANEL_MENU_UL_Y + TEXTBOX_PANEL_OFFSET_Y};

const long PANEL_MENU_LL_X{PANEL_MENU_UL_X};
const long PANEL_MENU_LL_Y{SCREEN_HEIGHT - PANEL_SCREEN_OFFSET_Y};

const long PANEL_WIDTH_SCREEN{SCREEN_WIDTH - PANEL_SCREEN_OFFSET_X * 2};
const long PANEL_HEIGHT_SCREEN{SCREEN_HEIGHT - PANEL_SCREEN_OFFSET_Y * 2};
const long PANEL_HEIGHT_ONE_LINE{TEXT_FONT_HEIGHT + TEXTBOX_PANEL_OFFSET_Y * 2};
const long PANEL_HEIGHT_TWO_LINES{TEXT_FONT_HEIGHT * 2 + TEXTBOX_PANEL_OFFSET_Y * 2};
const long PANEL_HEIGHT_THREE_LINES{TEXT_FONT_HEIGHT * 3 + TEXTBOX_PANEL_OFFSET_Y * 2};
const long PANEL_HEIGHT_FOUR_LINES{TEXT_FONT_HEIGHT * 4 + TEXTBOX_PANEL_OFFSET_Y * 2};
const long PANEL_HEIGHT_THIRTEEN_LINES{TEXT_FONT_HEIGHT * 13 + TEXTBOX_PANEL_OFFSET_Y * 2};

const long PANEL_GOLD_Y{PANEL_MENU_LL_Y - PANEL_HEIGHT_TWO_LINES};
const long PANEL_FRONT_MENU_WIDTH_LEFT{PANEL_WIDTH_SCREEN / FRONT_MENU_SPLIT};
const long PANEL_MAP_NAME_Y{PANEL_MENU_LL_Y - PANEL_HEIGHT_TWO_LINES * 2};
const long PANEL_FRONT_MENU_X_RIGHT{PANEL_SCREEN_OFFSET_X + PANEL_FRONT_MENU_WIDTH_LEFT};
const long PANEL_FRONT_MENU_WIDTH_RIGHT{PANEL_WIDTH_SCREEN / FRONT_MENU_SPLIT * (FRONT_MENU_SPLIT - 1)};

const long PANEL_ITEM_MENU_WIDTH_LEFT{PANEL_WIDTH_SCREEN / ITEM_MENU_SPLIT};
const long PANEL_ITEM_MENU_X_RIGHT{PANEL_SCREEN_OFFSET_X + PANEL_ITEM_MENU_WIDTH_LEFT};
const long PANEL_ITEM_MENU_WIDTH_RIGHT{PANEL_WIDTH_SCREEN / ITEM_MENU_SPLIT * (ITEM_MENU_SPLIT - 1) + 1};

const long PANEL_STATUS_MENU_WIDTH_LEFT{PANEL_WIDTH_SCREEN / STATUS_MENU_SPLIT * (STATUS_MENU_SPLIT - 4)};
const long PANEL_STATUS_MENU_X_RIGHT{PANEL_SCREEN_OFFSET_X + PANEL_STATUS_MENU_WIDTH_LEFT + PANEL_WIDTH_SCREEN * (STATUS_MENU_SPLIT - 7) / STATUS_MENU_SPLIT};
const long PANEL_STATUS_MENU_WIDTH_RIGHT{PANEL_WIDTH_SCREEN / STATUS_MENU_SPLIT * (STATUS_MENU_SPLIT - 3) + 1};

#endif

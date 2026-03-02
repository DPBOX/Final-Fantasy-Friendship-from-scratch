#ifndef MEDIA_H
#define MEDIA_H

class Sound_Player
{
  public:
    explicit Sound_Player();
    Sound_Player(const Sound_Player & obj) = delete;
    Sound_Player & operator =(const Sound_Player & obj) = delete;
    virtual ~Sound_Player();

    void play_global_sound(const string & name) const;
  private:
    vector<Sound> m_global_sounds{};
    vector<string> m_global_sound_names{};
};

class Music_Player
{
  public:
    explicit Music_Player();
    Music_Player(const Music_Player & obj) = delete;
    Music_Player & operator =(const Music_Player & obj) = delete;
    virtual ~Music_Player();

    void play_global_music(const string & name);
    void pause_play_global_music() const;
    void stop_global_music();
    void update_music();
    void terminate_music();
  private:
    vector<Music> m_global_music{};
    vector<string> m_global_music_names{};
    string m_music_playing{"NULL"};
    bool m_terminate_music{false};
};

struct Music_Params
{
  explicit Music_Params(){}
  explicit Music_Params(const string & name, const unsigned char data[], const long & size, const double volume = VOLUME_MAX) : m_name(name), m_data(data), m_size(size), m_volume(volume){}
  explicit Music_Params(const Music_Params & obj) = delete;
  Music_Params & operator =(const Music_Params & obj) = delete;
  string m_name{"NULL"};
  const unsigned char* m_data{nullptr};
  long m_size{1};
  double m_volume{1};
};

struct Sound_Params
{
  explicit Sound_Params(){}
  explicit Sound_Params(const string & name, const unsigned char data[], const long & size, const double volume = VOLUME_MAX) : m_name(name), m_data(data), m_size(size), m_volume(volume){}
  explicit Sound_Params(const Sound_Params & obj) = delete;
  Sound_Params & operator =(const Sound_Params & obj) = delete;
  string m_name{"NULL"};
  const unsigned char* m_data{nullptr};
  long m_size{1};
  double m_volume{1};
};

struct Image_Params
{
  explicit Image_Params(){}
  explicit Image_Params(const string & name, const unsigned char data[], const long & size) : m_name(name), m_data(data), m_size(size){}
  explicit Image_Params(const Image_Params & obj) = delete;
  Image_Params & operator =(const Image_Params & obj) = delete;
  string m_name{"NULL"};
  const unsigned char* m_data{nullptr};
  long m_size{1};
};

#ifdef OS_LINUX
extern const unsigned char _binary_Image_applejack_png_start[];
extern const unsigned char _binary_Image_applejack_png_end[];

extern const unsigned char _binary_Image_applejack_portrait_png_start[];
extern const unsigned char _binary_Image_applejack_portrait_png_end[];

extern const unsigned char _binary_Image_applejack_small_portrait_png_start[];
extern const unsigned char _binary_Image_applejack_small_portrait_png_end[];

extern const unsigned char _binary_Image_battle_arrow_icon_png_start[];
extern const unsigned char _binary_Image_battle_arrow_icon_png_end[];

extern const unsigned char _binary_Image_battle_background_celestial_plane_png_start[];
extern const unsigned char _binary_Image_battle_background_celestial_plane_png_end[];

extern const unsigned char _binary_Image_colgate_png_start[];
extern const unsigned char _binary_Image_colgate_png_end[];

extern const unsigned char _binary_Image_colgate_small_portrait_png_start[];
extern const unsigned char _binary_Image_colgate_small_portrait_png_end[];

extern const unsigned char _binary_Image_continue_arrow_png_start[];
extern const unsigned char _binary_Image_continue_arrow_png_end[];

extern const unsigned char _binary_Image_cursor_png_start[];
extern const unsigned char _binary_Image_cursor_png_end[];

extern const unsigned char _binary_Image_enemy_changeling_png_start[];
extern const unsigned char _binary_Image_enemy_changeling_png_end[];

extern const unsigned char _binary_Image_fluttershy_portrait_png_start[];
extern const unsigned char _binary_Image_fluttershy_portrait_png_end[];

extern const unsigned char _binary_Image_fluttershy_small_portrait_png_start[];
extern const unsigned char _binary_Image_fluttershy_small_portrait_png_end[];

extern const unsigned char _binary_Image_heading_font_png_start[];
extern const unsigned char _binary_Image_heading_font_png_end[];

extern const unsigned char _binary_Image_intro_1_png_start[];
extern const unsigned char _binary_Image_intro_1_png_end[];

extern const unsigned char _binary_Image_intro_2_png_start[];
extern const unsigned char _binary_Image_intro_2_png_end[];

extern const unsigned char _binary_Image_intro_3_png_start[];
extern const unsigned char _binary_Image_intro_3_png_end[];

extern const unsigned char _binary_Image_intro_4_png_start[];
extern const unsigned char _binary_Image_intro_4_png_end[];

extern const unsigned char _binary_Image_intro_5_png_start[];
extern const unsigned char _binary_Image_intro_5_png_end[];

extern const unsigned char _binary_Image_intro_6_png_start[];
extern const unsigned char _binary_Image_intro_6_png_end[];

extern const unsigned char _binary_Image_intro_7_png_start[];
extern const unsigned char _binary_Image_intro_7_png_end[];

extern const unsigned char _binary_Image_intro_8_png_start[];
extern const unsigned char _binary_Image_intro_8_png_end[];

extern const unsigned char _binary_Image_intro_9_png_start[];
extern const unsigned char _binary_Image_intro_9_png_end[];

extern const unsigned char _binary_Image_intro_10_png_start[];
extern const unsigned char _binary_Image_intro_10_png_end[];

extern const unsigned char _binary_Image_intro_11_png_start[];
extern const unsigned char _binary_Image_intro_11_png_end[];

extern const unsigned char _binary_Image_intro_12_png_start[];
extern const unsigned char _binary_Image_intro_12_png_end[];

extern const unsigned char _binary_Image_inventory_icons_png_start[];
extern const unsigned char _binary_Image_inventory_icons_png_end[];

extern const unsigned char _binary_Image_map_ponyville_png_start[];
extern const unsigned char _binary_Image_map_ponyville_png_end[];

extern const unsigned char _binary_Image_map_ponyville_twilight_house_interior_png_start[];
extern const unsigned char _binary_Image_map_ponyville_twilight_house_interior_png_end[];

extern const unsigned char _binary_Image_npc_big_treasure_chest_png_start[];
extern const unsigned char _binary_Image_npc_big_treasure_chest_png_end[];

extern const unsigned char _binary_Image_pegasus_guard_png_start[];
extern const unsigned char _binary_Image_pegasus_guard_png_end[];

extern const unsigned char _binary_Image_pegasus_guard_small_portrait_png_start[];
extern const unsigned char _binary_Image_pegasus_guard_small_portrait_png_end[];

extern const unsigned char _binary_Image_pinkie_pie_png_start[];
extern const unsigned char _binary_Image_pinkie_pie_png_end[];

extern const unsigned char _binary_Image_pinkie_pie_portrait_png_start[];
extern const unsigned char _binary_Image_pinkie_pie_portrait_png_end[];

extern const unsigned char _binary_Image_pinkie_pie_small_portrait_png_start[];
extern const unsigned char _binary_Image_pinkie_pie_small_portrait_png_end[];

extern const unsigned char _binary_Image_progress_bar_background_png_start[];
extern const unsigned char _binary_Image_progress_bar_background_png_end[];

extern const unsigned char _binary_Image_progress_bar_blue_png_start[];
extern const unsigned char _binary_Image_progress_bar_blue_png_end[];

extern const unsigned char _binary_Image_progress_bar_green_png_start[];
extern const unsigned char _binary_Image_progress_bar_green_png_end[];

extern const unsigned char _binary_Image_progress_bar_orange_png_start[];
extern const unsigned char _binary_Image_progress_bar_orange_png_end[];

extern const unsigned char _binary_Image_progress_bar_pink_png_start[];
extern const unsigned char _binary_Image_progress_bar_pink_png_end[];

extern const unsigned char _binary_Image_progress_bar_red_png_start[];
extern const unsigned char _binary_Image_progress_bar_red_png_end[];

extern const unsigned char _binary_Image_rainbow_dash_portrait_png_start[];
extern const unsigned char _binary_Image_rainbow_dash_portrait_png_end[];

extern const unsigned char _binary_Image_rainbow_dash_small_portrait_png_start[];
extern const unsigned char _binary_Image_rainbow_dash_small_portrait_png_end[];

extern const unsigned char _binary_Image_rarity_portrait_png_start[];
extern const unsigned char _binary_Image_rarity_portrait_png_end[];

extern const unsigned char _binary_Image_rarity_small_portrait_png_start[];
extern const unsigned char _binary_Image_rarity_small_portrait_png_end[];

extern const unsigned char _binary_Image_simple_panel_png_start[];
extern const unsigned char _binary_Image_simple_panel_png_end[];

extern const unsigned char _binary_Image_spike_png_start[];
extern const unsigned char _binary_Image_spike_png_end[];

extern const unsigned char _binary_Image_spike_small_portrait_png_start[];
extern const unsigned char _binary_Image_spike_small_portrait_png_end[];

extern const unsigned char _binary_Image_text_font_png_start[];
extern const unsigned char _binary_Image_text_font_png_end[];

extern const unsigned char _binary_Image_text_font_yellow_png_start[];
extern const unsigned char _binary_Image_text_font_yellow_png_end[];

extern const unsigned char _binary_Image_text_font_red_png_start[];
extern const unsigned char _binary_Image_text_font_red_png_end[];

extern const unsigned char _binary_Image_text_font_green_png_start[];
extern const unsigned char _binary_Image_text_font_green_png_end[];

extern const unsigned char _binary_Image_text_font_gray_png_start[];
extern const unsigned char _binary_Image_text_font_gray_png_end[];

extern const unsigned char _binary_Image_twilight_sparkle_png_start[];
extern const unsigned char _binary_Image_twilight_sparkle_png_end[];

extern const unsigned char _binary_Image_twilight_sparkle_portrait_png_start[];
extern const unsigned char _binary_Image_twilight_sparkle_portrait_png_end[];

extern const unsigned char _binary_Image_twilight_sparkle_small_portrait_png_start[];
extern const unsigned char _binary_Image_twilight_sparkle_small_portrait_png_end[];



extern const unsigned char _binary_Sound_cursor_wav_start[];
extern const unsigned char _binary_Sound_cursor_wav_end[];

extern const unsigned char _binary_Sound_door_open_wav_start[];
extern const unsigned char _binary_Sound_door_open_wav_end[];

extern const unsigned char _binary_Sound_confirm_wav_start[];
extern const unsigned char _binary_Sound_confirm_wav_end[];

extern const unsigned char _binary_Sound_back_wav_start[];
extern const unsigned char _binary_Sound_back_wav_end[];

extern const unsigned char _binary_Sound_buzzer_wav_start[];
extern const unsigned char _binary_Sound_buzzer_wav_end[];

extern const unsigned char _binary_Sound_encounter_wav_start[];
extern const unsigned char _binary_Sound_encounter_wav_end[];

extern const unsigned char _binary_Sound_equip_wav_start[];
extern const unsigned char _binary_Sound_equip_wav_end[];

extern const unsigned char _binary_Sound_atb_wav_start[];
extern const unsigned char _binary_Sound_atb_wav_end[];

extern const unsigned char _binary_Sound_exit_area_wav_start[];
extern const unsigned char _binary_Sound_exit_area_wav_end[];



extern const unsigned char _binary_Music_ponyville_mp3_start[];
extern const unsigned char _binary_Music_ponyville_mp3_end[];

extern const unsigned char _binary_Music_battle_mp3_start[];
extern const unsigned char _binary_Music_battle_mp3_end[];

extern const unsigned char _binary_Music_title_mp3_start[];
extern const unsigned char _binary_Music_title_mp3_end[];

extern const unsigned char _binary_Music_intro_1_mp3_start[];
extern const unsigned char _binary_Music_intro_1_mp3_end[];

extern const unsigned char _binary_Music_intro_2_mp3_start[];
extern const unsigned char _binary_Music_intro_2_mp3_end[];

#endif

#ifdef OS_WINDOWS
extern const unsigned char binary_Image_hero_png_start[];
extern const unsigned char binary_Image_hero_png_end[];

extern const unsigned char binary_Image_avatar_png_start[];
extern const unsigned char binary_Image_avatar_png_end[];

extern const unsigned char binary_Image_smolder_fly_right_png_start[];
extern const unsigned char binary_Image_smolder_fly_right_png_end[];

extern const unsigned char binary_Image_simple_panel_png_start[];
extern const unsigned char binary_Image_simple_panel_png_end[];

extern const unsigned char binary_Image_continue_arrow_png_start[];
extern const unsigned char binary_Image_continue_arrow_png_end[];

extern const unsigned char binary_Image_text_font_png_start[];
extern const unsigned char binary_Image_text_font_png_end[];

extern const unsigned char binary_Image_text_font_yellow_png_start[];
extern const unsigned char binary_Image_text_font_yellow_png_end[];

extern const unsigned char binary_Image_text_font_red_png_start[];
extern const unsigned char binary_Image_text_font_red_png_end[];

extern const unsigned char binary_Image_text_font_green_png_start[];
extern const unsigned char binary_Image_text_font_green_png_end[];

extern const unsigned char binary_Image_heading_font_png_start[];
extern const unsigned char binary_Image_heading_font_png_end[];

extern const unsigned char binary_Image_inventory_icons_png_start[];
extern const unsigned char binary_Image_inventory_icons_png_end[];

extern const unsigned char binary_Image_tempest_small_portrait_png_start[];
extern const unsigned char binary_Image_tempest_small_portrait_png_end[];

extern const unsigned char binary_Image_nightwish_png_start[];
extern const unsigned char binary_Image_nightwish_png_end[];

extern const unsigned char binary_Image_gallus_png_start[];
extern const unsigned char binary_Image_gallus_png_end[];

extern const unsigned char binary_Image_nightwish_portrait_png_start[];
extern const unsigned char binary_Image_nightwish_portrait_png_end[];

extern const unsigned char binary_Image_nightwish_small_portrait_png_start[];
extern const unsigned char binary_Image_nightwish_small_portrait_png_end[];

extern const unsigned char binary_Image_gallus_portrait_png_start[];
extern const unsigned char binary_Image_gallus_portrait_png_end[];

extern const unsigned char binary_Image_gallus_small_portrait_png_start[];
extern const unsigned char binary_Image_gallus_small_portrait_png_end[];

extern const unsigned char binary_Image_progress_bar_background_png_start[];
extern const unsigned char binary_Image_progress_bar_background_png_end[];

extern const unsigned char binary_Image_progress_bar_blue_png_start[];
extern const unsigned char binary_Image_progress_bar_blue_png_end[];

extern const unsigned char binary_Image_progress_bar_green_png_start[];
extern const unsigned char binary_Image_progress_bar_green_png_end[];

extern const unsigned char binary_Image_progress_bar_orange_png_start[];
extern const unsigned char binary_Image_progress_bar_orange_png_end[];

extern const unsigned char binary_Image_progress_bar_pink_png_start[];
extern const unsigned char binary_Image_progress_bar_pink_png_end[];

extern const unsigned char binary_Image_progress_bar_red_png_start[];
extern const unsigned char binary_Image_progress_bar_red_png_end[];

extern const unsigned char binary_Image_entrance_png_start[];
extern const unsigned char binary_Image_entrance_png_end[];

extern const unsigned char binary_Image_battle_testing_png_start[];
extern const unsigned char binary_Image_battle_testing_png_end[];

extern const unsigned char binary_Sound_cursor_wav_start[];
extern const unsigned char binary_Sound_cursor_wav_end[];

extern const unsigned char binary_Sound_confirm_wav_start[];
extern const unsigned char binary_Sound_confirm_wav_end[];

extern const unsigned char binary_Sound_back_wav_start[];
extern const unsigned char binary_Sound_back_wav_end[];

extern const unsigned char binary_Sound_buzzer_wav_start[];
extern const unsigned char binary_Sound_buzzer_wav_end[];

extern const unsigned char binary_Sound_encounter_wav_start[];
extern const unsigned char binary_Sound_encounter_wav_end[];

extern const unsigned char binary_Sound_equip_wav_start[];
extern const unsigned char binary_Sound_equip_wav_end[];

extern const unsigned char binary_Sound_atb_wav_start[];
extern const unsigned char binary_Sound_atb_wav_end[];

extern const unsigned char binary_Image_big_treasure_chest_png_start[];
extern const unsigned char binary_Image_big_treasure_chest_png_end[];
#endif

#ifdef OS_LINUX
const Music_Params PONYVILLE_MUSIC{"Ponyville", _binary_Music_ponyville_mp3_start, static_cast<long>(_binary_Music_ponyville_mp3_end - _binary_Music_ponyville_mp3_start)};
const Music_Params BATTLE_MUSIC{"Battle", _binary_Music_battle_mp3_start, static_cast<long>(_binary_Music_battle_mp3_end - _binary_Music_battle_mp3_start)};
const Music_Params TITLE_SCREEN_MUSIC{"Title Screen", _binary_Music_title_mp3_start, static_cast<long>(_binary_Music_title_mp3_end - _binary_Music_title_mp3_start), .5};
const Music_Params INTRO_1_MUSIC{"Intro 1", _binary_Music_intro_1_mp3_start, static_cast<long>(_binary_Music_intro_1_mp3_end - _binary_Music_intro_1_mp3_start)};
const Music_Params INTRO_2_MUSIC{"Intro 2", _binary_Music_intro_2_mp3_start, static_cast<long>(_binary_Music_intro_2_mp3_end - _binary_Music_intro_2_mp3_start)};

const Sound_Params CURSOR_SOUND{"Cursor", _binary_Sound_cursor_wav_start, static_cast<long>(_binary_Sound_cursor_wav_end - _binary_Sound_cursor_wav_start), .75};
const Sound_Params DOOR_OPEN_SOUND{"Door Open", _binary_Sound_door_open_wav_start, static_cast<long>(_binary_Sound_door_open_wav_end - _binary_Sound_door_open_wav_start)};
const Sound_Params CONFIRM_SOUND{"Confirm", _binary_Sound_confirm_wav_start, static_cast<long>(_binary_Sound_confirm_wav_end - _binary_Sound_confirm_wav_start)};
const Sound_Params BACK_SOUND{"Back", _binary_Sound_back_wav_start, static_cast<long>(_binary_Sound_back_wav_end - _binary_Sound_back_wav_start)};
const Sound_Params BUZZER_SOUND{"Buzzer", _binary_Sound_buzzer_wav_start, static_cast<long>(_binary_Sound_buzzer_wav_end - _binary_Sound_buzzer_wav_start)};
const Sound_Params BATTLE_TRANSITION_SOUND{"Battle Transition", _binary_Sound_encounter_wav_start, static_cast<long>(_binary_Sound_encounter_wav_end - _binary_Sound_encounter_wav_start)};
const Sound_Params EQUIP_SOUND{"Equip", _binary_Sound_equip_wav_start, static_cast<long>(_binary_Sound_equip_wav_end - _binary_Sound_equip_wav_start)};
const Sound_Params ATB_SOUND{"ATB", _binary_Sound_atb_wav_start, static_cast<long>(_binary_Sound_atb_wav_end - _binary_Sound_atb_wav_start)};
const Sound_Params EXIT_AREA_SOUND{"Exit Area", _binary_Sound_exit_area_wav_start, static_cast<long>(_binary_Sound_exit_area_wav_end - _binary_Sound_exit_area_wav_start)};

const Image_Params NULL_IMAGE{"NULL", _binary_Image_applejack_png_start, static_cast<long>(_binary_Image_applejack_png_end - _binary_Image_applejack_png_start)};
const Image_Params APPLEJACK_IMAGE{"Applejack", _binary_Image_applejack_png_start, static_cast<long>(_binary_Image_applejack_png_end - _binary_Image_applejack_png_start)};
const Image_Params APPLEJACK_PORTRAIT_IMAGE{"Applejack Portrait", _binary_Image_applejack_portrait_png_start, static_cast<long>(_binary_Image_applejack_portrait_png_end - _binary_Image_applejack_portrait_png_start)};
const Image_Params APPLEJACK_SMALL_PORTRAIT_IMAGE{"Applejack Small Portrait", _binary_Image_applejack_small_portrait_png_start, static_cast<long>(_binary_Image_applejack_small_portrait_png_end - _binary_Image_applejack_small_portrait_png_start)};
const Image_Params BATTLE_ARROW_ICON_IMAGE{"Battle Arrow", _binary_Image_battle_arrow_icon_png_start, static_cast<long>(_binary_Image_battle_arrow_icon_png_end - _binary_Image_battle_arrow_icon_png_start)};
const Image_Params CELESTIAL_PLANE_BATTLE_BACKGROUND_IMAGE{"Celestial Plane Battle Background", _binary_Image_battle_background_celestial_plane_png_start, static_cast<long>(_binary_Image_battle_background_celestial_plane_png_end - _binary_Image_battle_background_celestial_plane_png_start)};
const Image_Params COLGATE_IMAGE{"Colgate", _binary_Image_colgate_png_start, static_cast<long>(_binary_Image_colgate_png_end - _binary_Image_colgate_png_start)};
const Image_Params COLGATE_SMALL_PORTRAIT_IMAGE{"Colgate Small Portrait", _binary_Image_colgate_small_portrait_png_start, static_cast<long>(_binary_Image_colgate_small_portrait_png_end - _binary_Image_colgate_small_portrait_png_start)};
const Image_Params CONTINUE_ARROW_IMAGE{"Continue Arrow", _binary_Image_continue_arrow_png_start, static_cast<long>(_binary_Image_continue_arrow_png_end - _binary_Image_continue_arrow_png_start)};
const Image_Params CURSOR_IMAGE{"Cursor", _binary_Image_cursor_png_start, static_cast<long>(_binary_Image_cursor_png_end - _binary_Image_cursor_png_start)};
const Image_Params CHANGELING_ENEMY_IMAGE{"Changeling Enemy", _binary_Image_enemy_changeling_png_start, static_cast<long>(_binary_Image_enemy_changeling_png_end - _binary_Image_enemy_changeling_png_start)};
const Image_Params FLUTTERSHY_PORTRAIT_IMAGE{"Fluttershy Portrait", _binary_Image_fluttershy_portrait_png_start, static_cast<long>(_binary_Image_fluttershy_portrait_png_end - _binary_Image_fluttershy_portrait_png_start)};
const Image_Params FLUTTERSHY_SMALL_PORTRAIT_IMAGE{"Fluttershy Small Portrait", _binary_Image_fluttershy_small_portrait_png_start, static_cast<long>(_binary_Image_fluttershy_small_portrait_png_end - _binary_Image_fluttershy_small_portrait_png_start)};
const Image_Params HEADING_FONT_IMAGE{"Heading Font", _binary_Image_heading_font_png_start, static_cast<long>(_binary_Image_heading_font_png_end - _binary_Image_heading_font_png_start)};
const Image_Params INTRO_1_IMAGE{"Intro 1", _binary_Image_intro_1_png_start, static_cast<long>(_binary_Image_intro_1_png_end - _binary_Image_intro_1_png_start)};
const Image_Params INTRO_2_IMAGE{"Intro 2", _binary_Image_intro_2_png_start, static_cast<long>(_binary_Image_intro_2_png_end - _binary_Image_intro_2_png_start)};
const Image_Params INTRO_3_IMAGE{"Intro 3", _binary_Image_intro_3_png_start, static_cast<long>(_binary_Image_intro_3_png_end - _binary_Image_intro_3_png_start)};
const Image_Params INTRO_4_IMAGE{"Intro 4", _binary_Image_intro_4_png_start, static_cast<long>(_binary_Image_intro_4_png_end - _binary_Image_intro_4_png_start)};
const Image_Params INTRO_5_IMAGE{"Intro 5", _binary_Image_intro_5_png_start, static_cast<long>(_binary_Image_intro_5_png_end - _binary_Image_intro_5_png_start)};
const Image_Params INTRO_6_IMAGE{"Intro 6", _binary_Image_intro_6_png_start, static_cast<long>(_binary_Image_intro_6_png_end - _binary_Image_intro_6_png_start)};
const Image_Params INTRO_7_IMAGE{"Intro 7", _binary_Image_intro_7_png_start, static_cast<long>(_binary_Image_intro_7_png_end - _binary_Image_intro_7_png_start)};
const Image_Params INTRO_8_IMAGE{"Intro 8", _binary_Image_intro_8_png_start, static_cast<long>(_binary_Image_intro_8_png_end - _binary_Image_intro_8_png_start)};
const Image_Params INTRO_9_IMAGE{"Intro 9", _binary_Image_intro_9_png_start, static_cast<long>(_binary_Image_intro_9_png_end - _binary_Image_intro_9_png_start)};
const Image_Params INTRO_10_IMAGE{"Intro 10", _binary_Image_intro_10_png_start, static_cast<long>(_binary_Image_intro_10_png_end - _binary_Image_intro_10_png_start)};
const Image_Params INTRO_11_IMAGE{"Intro 11", _binary_Image_intro_11_png_start, static_cast<long>(_binary_Image_intro_11_png_end - _binary_Image_intro_11_png_start)};
const Image_Params INTRO_12_IMAGE{"Intro 12", _binary_Image_intro_12_png_start, static_cast<long>(_binary_Image_intro_12_png_end - _binary_Image_intro_12_png_start)};
const Image_Params INVENTORY_ICONS_IMAGE{"Inventory Icons", _binary_Image_inventory_icons_png_start, static_cast<long>(_binary_Image_inventory_icons_png_end - _binary_Image_inventory_icons_png_start)};
const Image_Params PONYVILLE_MAP_IMAGE{"Map Ponyville", _binary_Image_map_ponyville_png_start, static_cast<long>(_binary_Image_map_ponyville_png_end - _binary_Image_map_ponyville_png_start)};
const Image_Params PONYVILLE_TWILIGHT_HOUSE_INTERIOR_MAP_IMAGE{"Map Ponyville Twilight House Interior", _binary_Image_map_ponyville_twilight_house_interior_png_start, static_cast<long>(_binary_Image_map_ponyville_twilight_house_interior_png_end - _binary_Image_map_ponyville_twilight_house_interior_png_start)};
const Image_Params BIG_TREASURE_CHEST_IMAGE{"Big Treasure Chest", _binary_Image_npc_big_treasure_chest_png_start, static_cast<long>(_binary_Image_npc_big_treasure_chest_png_end - _binary_Image_npc_big_treasure_chest_png_start)};
const Image_Params PEGASUS_GUARD_IMAGE{"Pegasus Guard", _binary_Image_pegasus_guard_png_start, static_cast<long>(_binary_Image_pegasus_guard_png_end - _binary_Image_pegasus_guard_png_start)};
const Image_Params PEGASUS_GUARD_SMALL_PORTRAIT_IMAGE{"Pegasus Guard Small Portrait", _binary_Image_pegasus_guard_small_portrait_png_start, static_cast<long>(_binary_Image_pegasus_guard_small_portrait_png_end - _binary_Image_pegasus_guard_small_portrait_png_start)};
const Image_Params PINKIE_PIE_IMAGE{"Pinkie Pie", _binary_Image_pinkie_pie_png_start, static_cast<long>(_binary_Image_pinkie_pie_png_end - _binary_Image_pinkie_pie_png_start)};
const Image_Params PINKIE_PIE_PORTRAIT_IMAGE{"Pinkie Pie Portrait", _binary_Image_pinkie_pie_portrait_png_start, static_cast<long>(_binary_Image_pinkie_pie_portrait_png_end - _binary_Image_pinkie_pie_portrait_png_start)};
const Image_Params PINKIE_PIE_SMALL_PORTRAIT_IMAGE{"Pinkie Pie Small Portrait", _binary_Image_pinkie_pie_small_portrait_png_start, static_cast<long>(_binary_Image_pinkie_pie_small_portrait_png_end - _binary_Image_pinkie_pie_small_portrait_png_start)};
const Image_Params PROGRESS_BAR_BACKGROUND_IMAGE{"Progress Bar Background", _binary_Image_progress_bar_background_png_start, static_cast<long>(_binary_Image_progress_bar_background_png_end - _binary_Image_progress_bar_background_png_start)};
const Image_Params PROGRESS_BAR_BLUE_IMAGE{"Progress Bar Blue", _binary_Image_progress_bar_blue_png_start, static_cast<long>(_binary_Image_progress_bar_blue_png_end - _binary_Image_progress_bar_blue_png_start)};
const Image_Params PROGRESS_BAR_GREEN_IMAGE{"Progress Bar Green", _binary_Image_progress_bar_green_png_start, static_cast<long>(_binary_Image_progress_bar_green_png_end - _binary_Image_progress_bar_green_png_start)};
const Image_Params PROGRESS_BAR_ORANGE_IMAGE{"Progress Bar Orange", _binary_Image_progress_bar_orange_png_start, static_cast<long>(_binary_Image_progress_bar_orange_png_end - _binary_Image_progress_bar_orange_png_start)};
const Image_Params PROGRESS_BAR_PINK_IMAGE{"Progress Bar Pink", _binary_Image_progress_bar_pink_png_start, static_cast<long>(_binary_Image_progress_bar_pink_png_end - _binary_Image_progress_bar_pink_png_start)};
const Image_Params PROGRESS_BAR_RED_IMAGE{"Progress Bar Red", _binary_Image_progress_bar_red_png_start, static_cast<long>(_binary_Image_progress_bar_red_png_end - _binary_Image_progress_bar_red_png_start)};
const Image_Params RAINBOW_DASH_PORTRAIT_IMAGE{"Rainbow Dash Portrait", _binary_Image_rainbow_dash_portrait_png_start, static_cast<long>(_binary_Image_rainbow_dash_portrait_png_end - _binary_Image_rainbow_dash_portrait_png_start)};
const Image_Params RAINBOW_DASH_SMALL_PORTRAIT_IMAGE{"Rainbow Dash Small Portrait", _binary_Image_rainbow_dash_small_portrait_png_start, static_cast<long>(_binary_Image_rainbow_dash_small_portrait_png_end - _binary_Image_rainbow_dash_small_portrait_png_start)};
const Image_Params RARITY_PORTRAIT_IMAGE{"Rarity Portrait", _binary_Image_rarity_portrait_png_start, static_cast<long>(_binary_Image_rarity_portrait_png_end - _binary_Image_rarity_portrait_png_start)};
const Image_Params RARITY_SMALL_PORTRAIT_IMAGE{"Rarity Small Portrait", _binary_Image_rarity_small_portrait_png_start, static_cast<long>(_binary_Image_rarity_small_portrait_png_end - _binary_Image_rarity_small_portrait_png_start)};
const Image_Params PANEL_IMAGE{"Panel", _binary_Image_simple_panel_png_start, static_cast<long>(_binary_Image_simple_panel_png_end - _binary_Image_simple_panel_png_start)};
const Image_Params SPIKE_IMAGE{"Spike", _binary_Image_spike_png_start, static_cast<long>(_binary_Image_spike_png_end - _binary_Image_spike_png_start)};
const Image_Params SPIKE_SMALL_PORTRAIT_IMAGE{"Spike Small Portrait", _binary_Image_spike_small_portrait_png_start, static_cast<long>(_binary_Image_spike_small_portrait_png_end - _binary_Image_spike_small_portrait_png_start)};
const Image_Params TEXT_FONT_IMAGE{"Text Font", _binary_Image_text_font_png_start, static_cast<long>(_binary_Image_text_font_png_end - _binary_Image_text_font_png_start)};
const Image_Params TEXT_FONT_YELLOW_IMAGE{"Text Font Yellow", _binary_Image_text_font_yellow_png_start, static_cast<long>(_binary_Image_text_font_yellow_png_end - _binary_Image_text_font_yellow_png_start)};
const Image_Params TEXT_FONT_RED_IMAGE{"Text Font Red", _binary_Image_text_font_red_png_start, static_cast<long>(_binary_Image_text_font_red_png_end - _binary_Image_text_font_red_png_start)};
const Image_Params TEXT_FONT_GREEN_IMAGE{"Text Font Green", _binary_Image_text_font_green_png_start, static_cast<long>(_binary_Image_text_font_green_png_end - _binary_Image_text_font_green_png_start)};
const Image_Params TEXT_FONT_GRAY_IMAGE{"Text Font Gray", _binary_Image_text_font_gray_png_start, static_cast<long>(_binary_Image_text_font_gray_png_end - _binary_Image_text_font_gray_png_start)};
const Image_Params TWILIGHT_SPARKLE_IMAGE{"Twilight Sparkle", _binary_Image_twilight_sparkle_png_start, static_cast<long>(_binary_Image_twilight_sparkle_png_end - _binary_Image_twilight_sparkle_png_start)};
const Image_Params TWILIGHT_SPARKLE_PORTRAIT_IMAGE{"Twilight Sparkle Portrait", _binary_Image_twilight_sparkle_portrait_png_start, static_cast<long>(_binary_Image_twilight_sparkle_portrait_png_end - _binary_Image_twilight_sparkle_portrait_png_start)};
const Image_Params TWILIGHT_SPARKLE_SMALL_PORTRAIT_IMAGE{"Twilight Sparkle Small Portrait", _binary_Image_twilight_sparkle_small_portrait_png_start, static_cast<long>(_binary_Image_twilight_sparkle_small_portrait_png_end - _binary_Image_twilight_sparkle_small_portrait_png_start)};

#endif

#ifdef OS_WINDOWS
const Sound_Params CURSOR_SOUND{"Cursor", binary_Sound_cursor_wav_start, static_cast<long>(binary_Sound_cursor_wav_end - binary_Sound_cursor_wav_start), .75};
const Sound_Params CONFIRM_SOUND{"Confirm", binary_Sound_confirm_wav_start, static_cast<long>(binary_Sound_confirm_wav_end - binary_Sound_confirm_wav_start)};
const Sound_Params BACK_SOUND{"Back", binary_Sound_back_wav_start, static_cast<long>(binary_Sound_back_wav_end - binary_Sound_back_wav_start)};
const Sound_Params BUZZER_SOUND{"Buzzer", binary_Sound_buzzer_wav_start, static_cast<long>(binary_Sound_buzzer_wav_end - binary_Sound_buzzer_wav_start)};
const Sound_Params BATTLE_TRANSITION_SOUND{"Battle Transition", binary_Sound_encounter_wav_start, static_cast<long>(binary_Sound_encounter_wav_end - binary_Sound_encounter_wav_start)};

const Image_Params TEMPEST_PORTRAIT_IMAGE{"Tempest Portrait", binary_Image_avatar_png_start, static_cast<long>(binary_Image_avatar_png_end - binary_Image_avatar_png_start)};
const Image_Params TEMPEST_IMAGE{"Tempest", binary_Image_hero_png_start, static_cast<long>(binary_Image_hero_png_end - binary_Image_hero_png_start)};
const Image_Params CURSOR_IMAGE{"Cursor", binary_Image_smolder_fly_right_png_start, static_cast<long>(binary_Image_smolder_fly_right_png_end - binary_Image_smolder_fly_right_png_start)};
const Image_Params PANEL_IMAGE{"Panel", binary_Image_simple_panel_png_start, static_cast<long>(binary_Image_simple_panel_png_end - binary_Image_simple_panel_png_start)};
const Image_Params CONTINUE_ARROW_IMAGE{"Continue Arrow", binary_Image_continue_arrow_png_start, static_cast<long>(binary_Image_continue_arrow_png_end - binary_Image_continue_arrow_png_start)};
const Image_Params TEXT_FONT_IMAGE{"Text Font", binary_Image_text_font_png_start, static_cast<long>(binary_Image_text_font_png_end - binary_Image_text_font_png_start)};
const Image_Params TEXT_FONT_YELLOW_IMAGE{"Text Font Yellow", binary_Image_text_font_yellow_png_start, static_cast<long>(binary_Image_text_font_yellow_png_end - binary_Image_text_font_yellow_png_start)};
const Image_Params TEXT_FONT_RED_IMAGE{"Text Font Red", binary_Image_text_font_red_png_start, static_cast<long>(binary_Image_text_font_red_png_end - binary_Image_text_font_red_png_start)};
const Image_Params TEXT_FONT_GREEN_IMAGE{"Text Font Green", binary_Image_text_font_green_png_start, static_cast<long>(binary_Image_text_font_green_png_end - binary_Image_text_font_green_png_start)};
const Image_Params TEXT_FONT_TEMPEST_IMAGE{"Text Font Tempest", binary_Image_text_font_tempest_png_start, static_cast<long>(binary_Image_text_font_tempest_png_end - binary_Image_text_font_tempest_png_start)};
const Image_Params TEXT_FONT_NIGHTWISH_IMAGE{"Text Font Nightwish", binary_Image_text_font_nightwish_png_start, static_cast<long>(binary_Image_text_font_nightwish_png_end - binary_Image_text_font_nightwish_png_start)};
const Image_Params TEXT_FONT_GALLUS_IMAGE{"Text Font Gallus", binary_Image_text_font_gallus_png_start, static_cast<long>(binary_Image_text_font_gallus_png_end - binary_Image_text_font_gallus_png_start)};
const Image_Params HEADING_FONT_IMAGE{"Heading Font", binary_Image_heading_font_png_start, static_cast<long>(binary_Image_heading_font_png_end - binary_Image_heading_font_png_start)};
const Image_Params INVENTORY_ICONS_IMAGE{"Inventory Icons", binary_Image_inventory_icons_png_start, static_cast<long>(binary_Image_inventory_icons_png_end - binary_Image_inventory_icons_png_start)};
const Image_Params TEMPEST_SMALL_PORTRAIT_IMAGE{"Tempest Small Portrait", binary_Image_tempest_small_portrait_png_start, static_cast<long>(binary_Image_tempest_small_portrait_png_end - binary_Image_tempest_small_portrait_png_start)};
const Image_Params NIGHTWISH_IMAGE{"Nightwish", binary_Image_nightwish_png_start, static_cast<long>(binary_Image_nightwish_png_end - binary_Image_nightwish_png_start)};
const Image_Params NIGHTWISH_PORTRAIT_IMAGE{"Nightwish Portrait", binary_Image_nightwish_portrait_png_start, static_cast<long>(binary_Image_nightwish_portrait_png_end - binary_Image_nightwish_portrait_png_start)};
const Image_Params NIGHTWISH_SMALL_PORTRAIT_IMAGE{"Nightwish Small Portrait", binary_Image_nightwish_small_portrait_png_start, static_cast<long>(binary_Image_nightwish_small_portrait_png_end - binary_Image_nightwish_small_portrait_png_start)};
const Image_Params GALLUS_IMAGE{"Gallus", binary_Image_gallus_png_start, static_cast<long>(binary_Image_gallus_png_end - binary_Image_gallus_png_start)};
const Image_Params GALLUS_PORTRAIT_IMAGE{"Gallus Portrait", binary_Image_gallus_portrait_png_start, static_cast<long>(binary_Image_gallus_portrait_png_end - binary_Image_gallus_portrait_png_start)};
const Image_Params GALLUS_SMALL_PORTRAIT_IMAGE{"Gallus Small Portrait", binary_Image_gallus_small_portrait_png_start, static_cast<long>(binary_Image_gallus_small_portrait_png_end - binary_Image_gallus_small_portrait_png_start)};
const Image_Params PROGRESS_BAR_BACKGROUND_IMAGE{"Progres Bar Background", binary_Image_progress_bar_background_png_start, static_cast<long>(binary_Image_progress_bar_background_png_end - binary_Image_progress_bar_background_png_start)};
const Image_Params PROGRESS_BAR_BLUE_IMAGE{"Progres Bar Blue", binary_Image_progress_bar_blue_png_start, static_cast<long>(binary_Image_progress_bar_blue_png_end - binary_Image_progress_bar_blue_png_start)};
const Image_Params PROGRESS_BAR_GREEN_IMAGE{"Progres Bar Green", binary_Image_progress_bar_green_png_start, static_cast<long>(binary_Image_progress_bar_green_png_end - binary_Image_progress_bar_green_png_start)};
const Image_Params PROGRESS_BAR_ORANGE_IMAGE{"Progres Bar Orange", binary_Image_progress_bar_orange_png_start, static_cast<long>(binary_Image_progress_bar_orange_png_end - binary_Image_progress_bar_orange_png_start)};
const Image_Params PROGRESS_BAR_PINK_IMAGE{"Progres Bar Pink", binary_Image_progress_bar_pink_png_start, static_cast<long>(binary_Image_progress_bar_pink_png_end - binary_Image_progress_bar_pink_png_start)};
const Image_Params PROGRESS_BAR_RED_IMAGE{"Progres Bar Red", binary_Image_progress_bar_red_png_start, static_cast<long>(binary_Image_progress_bar_red_png_end - binary_Image_progress_bar_red_png_start)};
const Image_Params ENTRANCE_MAP_IMAGE{"Entrance Map", binary_Image_entrance_png_start, static_cast<long>(binary_Image_entrance_png_end - binary_Image_entrance_png_start)};
const Image_Params BATTLE_TESTING_MAP_IMAGE{"Battle Testing Map", binary_Image_battle_testing_png_start, static_cast<long>(binary_Image_battle_testing_png_end - binary_Image_battle_testing_png_start)};
const Image_Params TREASURE_CHEST_IMAGE{"Treasure Chest", binary_Image_treasure_chest_png_start, static_cast<long>(binary_Image_treasure_chest_png_end - binary_Image_treasure_chest_png_start)};
const Image_Params BIG_TREASURE_CHEST_IMAGE{"Big Treasure Chest", binary_Image_big_treasure_chest_png_start, static_cast<long>(binary_Image_big_treasure_chest_png_end - binary_Image_big_treasure_chest_png_start)};
#endif
#endif

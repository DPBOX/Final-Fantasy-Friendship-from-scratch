#ifndef SCRIPT_H
#define SCRIPT_H
#include "World.h"

class Tilemap;
class Input_Wrapper;
class Textbox;

struct No_Script_Params{};

struct Name_Params
{
  explicit Name_Params(const string & name) : m_name(name){}
  string m_name{"NULL"};
};

struct Name_Pair_Params
{
  explicit Name_Pair_Params(const string & name, const string & name2) : m_name(name), m_name2(name2){}
  string m_name{"NULL"};
  string m_name2{"NULL"};
};

struct Add_Caption_Params
{
  explicit Add_Caption_Params(const string & id, const string & text, const string & font, const long & y_pos) : m_id(id), m_text(text), m_font(font), m_y_pos(y_pos){}
  string m_id{"NULL"};
  string m_text{"NULL"};
  string m_font{};
  long m_y_pos{0};
};

struct Add_Image_Params
{
  explicit Add_Image_Params(const Image_Params* image, const long & y_pos) : m_image(image), m_y_pos(y_pos){}
  const Image_Params* m_image{nullptr};
  long m_y_pos{0};
};

struct Has_Key_Item_Params
{
  explicit Has_Key_Item_Params(const string & item_name, const long & have, const long & dont_have) : m_item_name(item_name), m_have(have), m_dont_have(dont_have){}
  string m_item_name{"NULL"};
  long m_have{0};
  long m_dont_have{0};
};

struct Check_Entity_Position_Params
{
  explicit Check_Entity_Position_Params(const string & npc_name, const long & tile_offset_x, const long & tile_offset_y, const long & there, const long & not_there) : m_npc_name(npc_name), m_tile_offset_x(tile_offset_x), m_tile_offset_y(tile_offset_y), m_there(there), m_not_there(not_there){}
  string m_npc_name{"NULL"};
  long m_tile_offset_x{0};
  long m_tile_offset_y{0};
  long m_there{0};
  long m_not_there{0};
};

struct Write_Map_Tile_Params
{
  explicit Write_Map_Tile_Params(const long & layer, const bool & sublayer, const bool & new_collision, const long & tile_to_change_x, const long & tile_to_change_y, const long & tile_to_change_to) : m_layer(layer), m_sublayer(sublayer), m_new_collision(new_collision), m_tile_to_change_x(tile_to_change_x), m_tile_to_change_y(tile_to_change_y), m_tile_to_change_to(tile_to_change_to){}
  long m_layer{0};
  bool m_sublayer{0};
  bool m_new_collision{0};
  long m_tile_to_change_x{0};
  long m_tile_to_change_y{0};
  long m_tile_to_change_to{0};
};

struct Party_Params
{
  explicit Party_Params(const Player_Info & member) : m_member(&member){}
  const Player_Info* m_member{&TWILIGHT_SPARKLE_INFO};
};

struct Wait_Params
{
  explicit Wait_Params(const long & frames) : m_frames(frames){}
  long m_frames{60};
};

struct Fade_Params
{
  explicit Fade_Params(const string & name, const double & seconds) : m_name(name), m_seconds(seconds){}
  string m_name{"NULL"};
  double m_seconds{1};
};

struct Scroll_Params
{
  explicit Scroll_Params(const string & name, const double & seconds, const long & destination) : m_name(name), m_seconds(seconds), m_destination(destination){}
  string m_name{"NULL"};
  double m_seconds{1};
  long m_destination{1};
};

struct Fade_Screen_Params
{
  explicit Fade_Screen_Params(const double & seconds) : m_seconds(seconds){}
  double m_seconds{1};
};

struct Set_NPC_Path_Params
{
  explicit Set_NPC_Path_Params(const string & npc_name, const long & path) : m_npc_name(npc_name), m_path(path){}
  string m_npc_name{"NULL"};
  long m_path{0};
};

struct Say_Params
{
  explicit Say_Params(const string & npc_name, const string & text, const long & x_offset = 0, const long & y_offset = 0) : m_npc_name(npc_name), m_text(text), m_x_offset(x_offset), m_y_offset(y_offset){}
  string m_npc_name{"NULL"};
  string m_text{"NULL"};
  long m_x_offset{0};
  long m_y_offset{0};
};

struct Talk_Params
{
  explicit Talk_Params(const string & text, const string & npc_name = "NULL", const Image_Params & image = NULL_IMAGE) : m_text(text), m_npc_name(npc_name), m_portrait_image(&image){}
  Talk_Params(const Talk_Params & obj) = default;
  Talk_Params & operator =(const Talk_Params & obj) = default;
  virtual ~Talk_Params(){}
  string m_text{"NULL"};
  string m_npc_name{"NULL"};
  const Image_Params* m_portrait_image{&NULL_IMAGE};
};

struct Say_Choices_Params
{
  explicit Say_Choices_Params(const string & npc_name, const string & text, const long & x_offset, const long & y_offset, const vector<string> & choices, const vector<long> & script_decisions) : m_npc_name(npc_name), m_text(text), m_x_offset(x_offset), m_y_offset(y_offset), m_choices(choices), m_script_decisions(script_decisions){}
  string m_npc_name{"NULL"};
  string m_text{"NULL"};
  long m_x_offset{0};
  long m_y_offset{0};
  vector<string> m_choices{};
  vector<long> m_script_decisions{};
};

struct Move_Camera_To_Tile_Params
{
  explicit Move_Camera_To_Tile_Params(const long & destination_tile_x, const long & destination_tile_y, const double & seconds) : m_destination_tile_x(destination_tile_x), m_destination_tile_y(destination_tile_y), m_seconds(seconds){}
  long m_destination_tile_x{0};
  long m_destination_tile_y{0};
  double m_seconds{1};
};

struct Change_Map_Params
{
  explicit Change_Map_Params(const string & name, const long & start_layer, const long & start_tile_x, const long & start_tile_y, const Direction & hero_start_facing_dir) : m_name(name), m_start_layer(start_layer), m_start_tile_x(start_tile_x), m_start_tile_y(start_tile_y), m_hero_start_facing_dir(hero_start_facing_dir){}
  string m_name{"NULL"};
  long m_start_layer{0};
  long m_start_tile_x{0};
  long m_start_tile_y{0};
  Direction m_hero_start_facing_dir{Direction::Down};
};

enum class Script_Op
{
  Switch_Game_State,
  Add_Game_State,
  Black_Screen,
  Add_Caption,
  Add_Image,
  Show_NPC,
  Hide_NPC,
  Lock_Controls,
  Unlock_Controls,
  Play_Music,
  Play_Sound,
  Change_Map,
  Add_Key_Item,
  Remove_Key_Item,
  Has_Key_Item,
  Add_Equipment,
  Add_Item,
  Check_Entity_Position,
  Write_Map_Tile,
  Join_Party,
  Wait,
  Fade_In_Screen,
  Fade_Out_Screen,
  Fade_In_Caption,
  Fade_Out_Caption,
  Fade_In_Image,
  Fade_Out_Image,
  Fade_In_NPC,
  Fade_Out_NPC,
  Scroll_Image_Y,
  Set_NPC_Path,
  Say,
  Narrate,
  Interact,
  Talk,
  Say_Choices,
  Move_Camera_To_Tile,
  Battle_Transition,
  Add_Game_State_Pair
};

typedef variant
<
  No_Script_Params,
  Name_Params,
  Name_Pair_Params,
  Add_Caption_Params,
  Add_Image_Params,
  Has_Key_Item_Params,
  Check_Entity_Position_Params,
  Write_Map_Tile_Params,
  Party_Params,
  Wait_Params,
  Fade_Params,
  Scroll_Params,
  Fade_Screen_Params,
  Set_NPC_Path_Params,
  Say_Params,
  Talk_Params,
  Say_Choices_Params,
  Move_Camera_To_Tile_Params,
  Change_Map_Params
> Script_Ops;

struct Script_Op_Params
{
  Script_Op_Params(const Script_Op & op, const Script_Ops & params = No_Script_Params{}) : m_operation(op), m_params(params){}
  Script_Op m_operation{Script_Op::Black_Screen};
  Script_Ops m_params{};
};

struct Script_Step
{
  Script_Step(const vector<Script_Op_Params> & operations) : m_operations(operations){}
  long size() const{return m_operations.size();}
  Script_Op get_opcode(const long & index) const{return m_operations[index].m_operation;}
  Script_Ops & operator[](const long & index){return m_operations[index].m_params;}
  vector<Script_Op_Params> m_operations{};
};

struct Scr
{
  Scr(const vector<Script_Step> & steps = vector<Script_Step>{}) : m_steps(steps){}
  long size() const{return m_steps.size();}
  Script_Step & operator[](const long & index){return m_steps[index];}
  vector<Script_Step> m_steps{};
};

class Map_Data;

class Script
{
  public:
    explicit Script(const Scr & events) : m_events(events){}
    Script(const Script & obj) = delete;
    Script & operator =(const Script & obj) = delete;
    ~Script();

    void update(){}
    // 0: pop the current state
    // 1: next state to load
    // 2: an additional state to load on top the 1, such as transitions
    // 3: all scripts are finished and control can return to the player
    // 4: If a script makes another script run, this is the new script to run.
    // 5: new map to load when changing maps
    // 6: the player's starting parameters on the new map (direction, x tile, y tile, and layer)
    tuple<bool, string, string, bool, long, const Map_Data*, tuple<Direction, long, long, long>> update_input(Tilemap* map, Music_Player* music_player, World* world, Input_Wrapper* input);
    void render(const World* const world) const;
  private:
    struct Tween_Data
    {
      explicit Tween_Data(const string & function, const string & target, const double & velocity, const double & start, const double & end) : m_function(function), m_target(target), m_velocity(velocity), m_position(start), m_start(start), m_end(end){}
      string m_function{"NULL"};
      string m_target{"NULL"};
      double m_velocity{0};
      double m_position{0};
      double m_start{0};
      double m_end{0};
      bool m_done{false};
      ~Tween_Data(){}
    };
    struct Screen_Data
    {
      explicit Screen_Data(const string & id, const long & alpha = 255, const long & red = 0, const long & green = 0, const long & blue = 0) : m_id(id), m_alpha(alpha), m_red(red), m_green(green), m_blue(blue){}
      string m_id{"NULL"};
      long m_alpha{255};
      long m_red{0};
      long m_green{0};
      long m_blue{0};
      ~Screen_Data(){}
    };
    struct Caption_Data
    {
      explicit Caption_Data(const string & font_name, const string & id, const string & text, const long & y_pos, const long & alpha = 0);
      Caption_Data(const Caption_Data & obj) = delete;
      Caption_Data & operator =(const Caption_Data & obj) = delete;
      ~Caption_Data(){}
      string m_font{"Text"};
      string m_id{"NULL"};
      string m_text{"NULL"};
      long m_y_pos{0};
      long m_alpha{0};
    };
    struct Image_Data
    {
      explicit Image_Data(const Image_Params* const image, const long & y_pos){m_y_pos = y_pos; Image the_image{LoadImageFromMemory(".png", image->m_data, image->m_size)}; m_id = image->m_name; m_image = LoadTextureFromImage(the_image); UnloadImage(the_image);}
      Image_Data(const Image_Data & obj) = delete;
      Image_Data & operator =(const Image_Data & obj) = delete;
      ~Image_Data(){UnloadTexture(m_image);}
      Texture2D m_image{};
      string m_id{"NULL"};
      long m_y_pos{0};
      long m_alpha{0};
    };

    Scr m_events{};
    long m_outer_index{0};
    long m_inner_index{0};
    long m_inner_index2{0};
    long m_choice_index{-1};
    vector<Tween_Data> m_tween_list{};
    vector<Screen_Data*> m_screen_list{};
    vector<Caption_Data*> m_caption_list{};
    vector<Image_Data*> m_image_list{};
    Textbox* m_textbox{nullptr};
    long m_new_script{-1};
    vector<string> m_choices{};
    vector<long> m_choice_scripts{};
};

class Script_Handler
{
  public:
    explicit Script_Handler(const vector<Scr> & script_list) : m_script_list(script_list){}
    Script_Handler(const Script_Handler & obj) = delete;
    Script_Handler & operator =(const Script_Handler & obj) = delete;
    ~Script_Handler();
    // 0: pop the current state
    // 1: next state to load
    // 2: an additional state to load on top the 1, such as transitions
    // 3: all scripts are finished and control can return to the player
    // 4: new map to load when changing maps
    // 5: the player's starting parameters on the new map (direction, x tile, y tile, and layer)
    tuple<bool, string, string, bool, const Map_Data*, tuple<Direction, long, long, long>> update_input(Tilemap* map, Music_Player* music_player, World* world, Input_Wrapper* input);
    void render(const World* const world) const;
    void run_script(const long & index);
  private:
    Script* m_script{nullptr};
    vector<Scr> m_script_list{};
};

#endif

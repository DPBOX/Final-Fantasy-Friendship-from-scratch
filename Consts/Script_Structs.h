#ifndef SCRIPT_STRUCTS_H
#define SCRIPT_STRUCTS_H

enum class Direction{Up, Down, Left, Right};

struct No_Script_Params{};

struct Teleport_Entity_Params
{
  explicit Teleport_Entity_Params(const string & entity_name, const long & destination_tile_x, const long & destination_tile_y) : m_entity_name(entity_name), m_destination_tile_x(destination_tile_x), m_destination_tile_y(destination_tile_y){}
  string m_entity_name{"NULL"};
  long m_destination_tile_x{0};
  long m_destination_tile_y{0};
};

struct Name_Params
{
  explicit Name_Params(const string & name) : m_name(name){}
  string m_name{"NULL"};
};

struct Add_Music_Script_Params
{
  explicit Add_Music_Script_Params(const Music_Params & params) : m_music(params){}
  Music_Params m_music{};
};

struct Add_Caption_Params
{
  explicit Add_Caption_Params(const string & id, const string & text, const long & font, const long & y_pos) : m_id(id), m_text(text), m_font(font), m_y_pos(y_pos){}
  string m_id{"NULL"};
  string m_text{"NULL"};
  long m_font{};
  long m_y_pos{0};
};

struct Add_Sound_Params
{
  explicit Add_Sound_Params(const Sound_Params & params) : m_params(params){}
  Sound_Params m_params{};
};

struct Change_Music_Volume_Params
{
  explicit Change_Music_Volume_Params(const string & music_name, const double & volume) : m_music_name(music_name), m_volume(volume){}
  string m_music_name{"NULL"};
  double m_volume{0};
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
  explicit Say_Params(const string & npc_name, const string & text, const long & x_offset, const long & y_offset) : m_npc_name(npc_name), m_text(text), m_x_offset(x_offset), m_y_offset(y_offset){}
  string m_npc_name{"NULL"};
  string m_text{"NULL"};
  long m_x_offset{0};
  long m_y_offset{0};
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

enum class Script_Op
{
  Teleport_Entity,
  Switch_Game_State,
  Add_Game_State,
  Black_Screen,
  Add_Music,
  Remove_Music,
  Remove_All_Music,
  Play_Music,
  Set_Music_Volume,
  Add_Caption,
  Add_Sound,
  Show_NPC,
  Hide_NPC,
  Lock_Controls,
  Unlock_Controls,
  Play_Sound,
  Change_Map,
  Deactivate_Trigger,
  Deactivate_Use_Trigger,
  Deactivate_Enter_Trigger,
  Deactivate_Exit_Trigger,
  Add_Key_Item,
  Remove_Key_Item,
  Has_Key_Item,
  Check_Entity_Position,
  Write_Map_Tile,
  Wait,
  Fade_In_Music,
  Fade_Out_Music,
  Fade_In_Sound,
  Fade_Out_Sound,
  Fade_In_Screen,
  Fade_Out_Screen,
  Fade_In_Caption,
  Fade_Out_Caption,
  Fade_In_NPC,
  Fade_Out_NPC,
  Set_NPC_Path,
  Say,
  Talk,
  Say_Choices,
  Move_Camera_To_Tile
};

typedef variant
<
  No_Script_Params,
  Teleport_Entity_Params,
  Name_Params,
  Add_Music_Script_Params,
  Add_Caption_Params,
  Add_Sound_Params,
  Change_Music_Volume_Params,
  Has_Key_Item_Params,
  Check_Entity_Position_Params,
  Write_Map_Tile_Params,
  Wait_Params,
  Fade_Params,
  Fade_Screen_Params,
  Set_NPC_Path_Params,
  Say_Params,
  Say_Choices_Params,
  Move_Camera_To_Tile_Params
> Script_Ops;

struct Script_Op_Params
{
  Script_Op_Params(const Script_Op & op, const Script_Ops & params = No_Script_Params{}) : m_operation(op), m_params(params){}
  Script_Op m_operation{Script_Op::Add_Sound};
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

struct NPC_Effect
{
  explicit NPC_Effect(){}
  explicit NPC_Effect(const long & width, const long & offset_x, const long & offset_y, const unsigned char* data, const long & size, const long & animation_speed, const vector<long> & animation_list)
  {
    m_width = width;
    m_offset_x = offset_x;
    m_offset_y = offset_y;
    m_img_size = size;
    m_animation_speed = animation_speed;
    m_animation_list = animation_list;
    m_img_data = new unsigned char[m_img_size];
    ++mem;
    for(long k{0}; k < m_img_size; ++k)
    {
      m_img_data[k] = data[k];
    }
  }
  NPC_Effect & operator =(const NPC_Effect & obj)
  {
    if(this != &obj)
    {
      if(m_img_data != nullptr)
      {
        delete [] m_img_data;
        m_img_data = nullptr;
        --mem;
      }
      m_width = obj.m_width;
      m_offset_x = obj.m_offset_x;
      m_offset_y = obj.m_offset_y;
      m_img_size = obj.m_img_size;
      m_animation_speed = obj.m_animation_speed;
      m_animation_list = obj.m_animation_list;
      m_img_data = new unsigned char[m_img_size];
      ++mem;
      for(long k{0}; k < m_img_size; ++k)
      {
        m_img_data[k] = obj.m_img_data[k];
      }
    }
    return *this;
  }
  explicit NPC_Effect(const NPC_Effect & obj)
  {
    *this = obj;
  }
  long m_width{0};
  long m_offset_x{0};
  long m_offset_y{0};
  unsigned char* m_img_data{nullptr};
  long m_img_size{0}; 
  long m_animation_speed{0};
  vector<long> m_animation_list{};
  ~NPC_Effect()
  {
    if(m_img_data != nullptr)
    {
      delete [] m_img_data;
      m_img_data = nullptr;
      --mem;
    }
  }
};

struct Hero_Data
{
  explicit Hero_Data(const long & layer = 0, const long & tile_x = 0, const long & tile_y = 0, const Direction & facing_dir = Direction::Down, const string & start_state = "NULL") : m_layer(layer), m_tile_x(tile_x), m_tile_y(tile_y), m_facing_dir(facing_dir), m_start_state(start_state){}
  long m_layer;
  long m_tile_x;
  long m_tile_y;
  Direction m_facing_dir;
  string m_start_state;
  ~Hero_Data(){}
};

struct NPC_Data
{
  explicit NPC_Data(){}
  explicit NPC_Data(const long & layer, const long & width, const long & tile_x, const long & tile_y, const Direction & facing_dir, const string & start_state, const double & move_speed, const bool & show_effect, const bool & loop, const bool & hidden, const long & animation_speed, const string & tex_id, const unsigned char* data, const long & size, const NPC_Effect & effect, const vector<vector<Direction>> & paths, const vector<vector<long>> & animation_list, const vector<string> & speech)
  {
    m_layer = layer;
    m_width = width;
    m_tile_x = tile_x;
    m_tile_y = tile_y;
    m_facing_dir = facing_dir;
    m_start_state = start_state;
    m_move_speed = move_speed;
    m_show_effect = show_effect;
    m_loop = loop;
    m_hidden = hidden;
    m_animation_speed = animation_speed;
    m_id = tex_id;
    m_img_size = size;
    m_effect = effect;
    m_paths = paths;
    m_animation_list = animation_list;
    m_speech = speech;
    m_img_data = new unsigned char[m_img_size];
    ++mem;
    for(long k{0}; k < m_img_size; ++k)
    {
      m_img_data[k] = data[k];
    }
  }
  NPC_Data & operator =(const NPC_Data & obj)
  {
    if(this != &obj)
    {
      if(m_img_data != nullptr)
      {
        delete [] m_img_data;
        m_img_data = nullptr;
        --mem;
      }
      m_layer = obj.m_layer;
      m_width = obj.m_width;
      m_tile_x = obj.m_tile_x;
      m_tile_y = obj.m_tile_y;
      m_facing_dir = obj.m_facing_dir;
      m_start_state = obj.m_start_state;
      m_move_speed = obj.m_move_speed;
      m_show_effect = obj.m_show_effect;
      m_loop = obj.m_loop;
      m_hidden = obj.m_hidden;
      m_animation_speed = obj.m_animation_speed;
      m_id = obj.m_id;
      m_img_size = obj.m_img_size;
      m_effect = obj.m_effect;
      m_paths = obj.m_paths;
      m_animation_list = obj.m_animation_list;
      m_speech = obj.m_speech;
      m_img_data = new unsigned char[m_img_size];
      ++mem;
      for(long k{0}; k < m_img_size; ++k)
      {
        m_img_data[k] = obj.m_img_data[k];
      }
    }
    return *this;
  }
  explicit NPC_Data(const NPC_Data & obj)
  {
    *this = obj;
  }
  long m_layer{0};
  long m_width{0};
  long m_tile_x{0};
  long m_tile_y{0};
  Direction m_facing_dir{Direction::Up};
  string m_start_state{"NULL"};
  double m_move_speed{0};
  bool m_show_effect{false};
  bool m_loop{false};
  bool m_hidden{true};
  long m_animation_speed{0};
  string m_id{"NULL"};
  unsigned char* m_img_data{nullptr};
  long m_img_size{0};
  NPC_Effect m_effect{};
  vector<vector<Direction>> m_paths{};
  vector<vector<long>> m_animation_list{};
  vector<string> m_speech{};
  ~NPC_Data()
  {
    if(m_img_data != nullptr)
    {
      delete [] m_img_data;
      m_img_data = nullptr;
      --mem;
    }
  }
};

struct Trigger_Data
{
  explicit Trigger_Data(const long & id, const long & l, const long & x, const long & y, const long & enter_script, const long & use_script, const bool & orientation = 0, const long & length = 1, const bool & next_tile = false, const bool & sublayer_to_write = 0, const long & tile_to_write = -1, const bool & new_collision = 0) : m_id(id), m_l(l), m_x(x), m_y(y), m_enter_script(enter_script), m_use_script(use_script), m_orientation(orientation), m_length(length), m_next_tile(next_tile), m_sublayer_to_write(sublayer_to_write), m_tile_to_write(tile_to_write), m_new_collision(new_collision){}
  long m_id;
  long m_l;
  long m_x;
  long m_y;
  long m_enter_script;
  long m_use_script;
  bool m_orientation;
  long m_length;
  bool m_next_tile;
  bool m_sublayer_to_write;
  long m_tile_to_write;
  bool m_new_collision;
  ~Trigger_Data(){}
};

struct Map_Data
{
  explicit Map_Data(){}
  explicit Map_Data(const long & map_width, const long & map_height, const long & tile_width, const string & id, const unsigned char* data, const long & size, const Music_Params & music, const bool & show_hero, const Hero_Data & hero_data, const vector<NPC_Data> & npc_data, const vector<Trigger_Data> & trigger_list, const vector<vector<vector<long>>> & tile_map, const vector<Scr> & scripts)
  {
    m_map_width = map_width;
    m_map_height = map_height;
    m_tile_width = tile_width;
    m_id = id;
    m_img_size = size;
    m_music = music;
    m_show_hero = show_hero;
    m_hero_data = hero_data;
    m_npc_list = npc_data;
    m_trigger_list = trigger_list;
    m_tile_map = tile_map;
    m_scripts = scripts;
    m_img_data = new unsigned char[m_img_size];
    ++mem;
    for(long k{0}; k < m_img_size; ++k)
    {
      m_img_data[k] = data[k];
    }
  }
  Map_Data & operator =(const Map_Data & obj)
  {
    if(this != &obj)
    {
      if(m_img_data != nullptr)
      {
        delete [] m_img_data;
        m_img_data = nullptr;
        --mem;
      }
      m_map_width = obj.m_map_width;
      m_map_height = obj.m_map_height;
      m_tile_width = obj.m_tile_width;
      m_id = obj.m_id;
      m_img_size = obj.m_img_size;
      m_music = obj.m_music;
      m_show_hero = obj.m_show_hero;
      m_hero_data = obj.m_hero_data;
      m_npc_list = obj.m_npc_list;
      m_trigger_list = obj.m_trigger_list;
      m_tile_map = obj.m_tile_map;
      m_scripts = obj.m_scripts;
      m_img_data = new unsigned char[m_img_size];
      ++mem;
      for(long k{0}; k < m_img_size; ++k)
      {
        m_img_data[k] = obj.m_img_data[k];
      }
    }
    return *this;
  }
  explicit Map_Data(const Map_Data & obj)
  {
    *this = obj;
  }
  long m_map_width{0};
  long m_map_height{0};
  long m_tile_width{0};
  string m_id{"NULL"};
  unsigned char* m_img_data{nullptr};
  long m_img_size{0};
  Music_Params m_music{};
  bool m_show_hero{false};
  Hero_Data m_hero_data{};
  vector<NPC_Data> m_npc_list{};
  vector<Trigger_Data> m_trigger_list{};
  vector<vector<vector<long>>> m_tile_map{};
  vector<Scr> m_scripts{};
  ~Map_Data()
  {
    if(m_img_data != nullptr)
    {
      delete [] m_img_data;
      m_img_data = nullptr;
      --mem;
    }
  }
};

#endif
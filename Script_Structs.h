#ifndef SCRIPT_STRUCTS_H
#define SCRIPT_STRUCTS_H
#include "World.h"

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

struct Add_Caption_Params
{
  explicit Add_Caption_Params(const string & id, const string & text, const string & font, const long & y_pos) : m_id(id), m_text(text), m_font(font), m_y_pos(y_pos){}
  string m_id{"NULL"};
  string m_text{"NULL"};
  string m_font{};
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
  const Player_Info* m_member{&TEMPEST_SHADOW_INFO};
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
  explicit Say_Params(const string & npc_name, const string & text, const long & x_offset = 0, const long & y_offset = 0) : m_npc_name(npc_name), m_text(text), m_x_offset(x_offset), m_y_offset(y_offset){}
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
  Add_Caption,
  Show_NPC,
  Hide_NPC,
  Lock_Controls,
  Unlock_Controls,
  Play_Sound,
  Change_Map,
  Deactivate_Trigger,
  Add_Key_Item,
  Remove_Key_Item,
  Has_Key_Item,
  Add_Equipment,
  Check_Entity_Position,
  Write_Map_Tile,
  Join_Party,
  Wait,
  Fade_In_Screen,
  Fade_Out_Screen,
  Fade_In_Caption,
  Fade_Out_Caption,
  Fade_In_NPC,
  Fade_Out_NPC,
  Set_NPC_Path,
  Say,
  Interact,
  Talk,
  Say_Choices,
  Move_Camera_To_Tile,
  Battle_Transition
};

typedef variant
<
  No_Script_Params,
  Teleport_Entity_Params,
  Name_Params,
  Add_Caption_Params,
  Has_Key_Item_Params,
  Check_Entity_Position_Params,
  Write_Map_Tile_Params,
  Party_Params,
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

#endif

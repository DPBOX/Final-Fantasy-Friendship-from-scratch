#include "Main.h"
#include "Script.h"
#include "UI.h"
#include "Tilemap.h"

Script_Handler::~Script_Handler()
{
  if(m_script != nullptr)
  {
    delete m_script;
    m_script = nullptr;
    --mem;
  }
}

tuple<bool, string, string, bool, const Map_Data*, tuple<Direction, long, long, long>> Script_Handler::update_input(Tilemap* map, Music_Player* music_player, World* world, Input_Wrapper* input)
{
  tuple<bool, string, string, bool, long, const Map_Data*, tuple<Direction, long, long, long>> s{make_tuple(false, "NULL", "NULL", false, -1, nullptr, make_tuple(Direction::Down, 0, 0, 0))};
  if(m_script != nullptr)
  {
    s = m_script->update_input(map, music_player, world, input);
    if(get<5>(s) != nullptr)
    {
      m_script_list = get<5>(s)->m_scripts;
    }
    if(get<3>(s) == true)
    {
      delete m_script;
      m_script = nullptr;
      --mem;
      if(get<4>(s) != -1)
      {
        if(get<4>(s) >= 0 && get<4>(s) < static_cast<long>(m_script_list.size()))
        {
          run_script(get<4>(s));
        }
        else
        {
          crash("Error: Script ID " + to_string(get<4>(s)) + " doesn't exist in the current map.");
        }
      }
      else
      {
        return make_tuple(get<0>(s), get<1>(s), get<2>(s), true, get<5>(s), get<6>(s));
      }
    }
  }
  return make_tuple(get<0>(s), get<1>(s), get<2>(s), false, get<5>(s), get<6>(s));
}

void Script_Handler::render(const World* const world) const
{
  if(m_script != nullptr)
  {
    m_script->render(world);
  }
}

void Script_Handler::run_script(const long & index)
{
  if(m_script == nullptr)
  {
    m_script = new Script(m_script_list[index]);
    ++mem;
  }
}

Script::~Script()
{
  for(long i{0}; i < static_cast<long>(m_screen_list.size()); ++i)
  {
    delete m_screen_list[i];
    m_screen_list[i] = nullptr;
    --mem;
  }
  
  for(long i{0}; i < static_cast<long>(m_caption_list.size()); ++i)
  {
    delete m_caption_list[i];
    m_caption_list[i] = nullptr;
    --mem;
  }
  for(long i{0}; i < static_cast<long>(m_image_list.size()); ++i)
  {
    delete m_image_list[i];
    m_image_list[i] = nullptr;
    --mem;
  }
  if(m_textbox != nullptr)
  {
    delete m_textbox;
    m_textbox = nullptr;
    --mem;
  }
  m_tween_list.clear();
  m_choices.clear();
  m_choice_scripts.clear();
  m_screen_list.clear();
  m_caption_list.clear();
}

tuple<bool, string, string, bool, long, const Map_Data*, tuple<Direction, long, long, long>> Script::update_input(Tilemap* map, Music_Player* music_player, World* world, Input_Wrapper* input)
{
  tuple<bool, string, string, bool, long, const Map_Data*, tuple<Direction, long, long, long>> s{make_tuple(false, "NULL", "NULL", m_outer_index == static_cast<long>(m_events.m_steps.size()), m_new_script, nullptr, make_tuple(Direction::Down, 0, 0, 0))};
  if(m_textbox != nullptr)
  {
    m_textbox->update_input(world, input);
  }

  if(m_inner_index == m_inner_index2)
  {
    m_inner_index = 0;
    m_inner_index2 = 0;
    bool instant{true};
    while(instant == true && m_outer_index != m_events.size())
    {
      while(m_inner_index != static_cast<long>(m_events[m_outer_index].size()))
      {
        Script_Op opcode{m_events[m_outer_index].get_opcode(m_inner_index)};
        long target_index{-1};
        switch(opcode)
        {
          case Script_Op::Switch_Game_State:
            s = make_tuple(true, get<Name_Params>(m_events[m_outer_index][m_inner_index]).m_name, "NULL", m_outer_index == static_cast<long>(m_events.m_steps.size()), m_new_script, nullptr, make_tuple(Direction::Down, 0, 0, 0));
            ++m_inner_index;
            ++m_inner_index2;
            break;

          case Script_Op::Add_Game_State:
            s = make_tuple(false, get<Name_Params>(m_events[m_outer_index][m_inner_index]).m_name, "NULL", m_outer_index == static_cast<long>(m_events.m_steps.size()), m_new_script, nullptr, make_tuple(Direction::Down, 0, 0, 0));
            ++m_inner_index;
            ++m_inner_index2;
            break;

          case Script_Op::Add_Game_State_Pair:
            s = make_tuple(false, get<Name_Pair_Params>(m_events[m_outer_index][m_inner_index]).m_name, get<Name_Pair_Params>(m_events[m_outer_index][m_inner_index]).m_name2, m_outer_index == static_cast<long>(m_events.m_steps.size()), m_new_script, nullptr, make_tuple(Direction::Down, 0, 0, 0));
            ++m_inner_index;
            ++m_inner_index2;
            break;

          case Script_Op::Black_Screen:
            m_screen_list.push_back(new Screen_Data{"Black Screen"});
            ++mem;
            ++m_inner_index;
            ++m_inner_index2;
            break;

          case Script_Op::Add_Caption:
            m_caption_list.push_back(new Caption_Data{get<Add_Caption_Params>(m_events[m_outer_index][m_inner_index]).m_font, get<Add_Caption_Params>(m_events[m_outer_index][m_inner_index]).m_id, get<Add_Caption_Params>(m_events[m_outer_index][m_inner_index]).m_text, get<Add_Caption_Params>(m_events[m_outer_index][m_inner_index]).m_y_pos});
            ++mem;
            ++m_inner_index;
            ++m_inner_index2;
            break;

          case Script_Op::Add_Image:
            m_image_list.push_back(new Image_Data{get<Add_Image_Params>(m_events[m_outer_index][m_inner_index]).m_image, get<Add_Image_Params>(m_events[m_outer_index][m_inner_index]).m_y_pos});
            ++mem;
            ++m_inner_index;
            ++m_inner_index2;
            break;

          case Script_Op::Show_NPC:
            map->show_npc(get<Name_Params>(m_events[m_outer_index][m_inner_index]).m_name);
            ++m_inner_index;
            ++m_inner_index2;
            break;
        
          case Script_Op::Hide_NPC:
            map->hide_npc(get<Name_Params>(m_events[m_outer_index][m_inner_index]).m_name);
            ++m_inner_index;
            ++m_inner_index2;
            break;
        
          case Script_Op::Lock_Controls:
            map->lock_controls();
            ++m_inner_index;
            ++m_inner_index2;
            break;
        
          case Script_Op::Unlock_Controls:
            map->unlock_controls();
            ++m_inner_index;
            ++m_inner_index2;
            break;

          case Script_Op::Play_Music:
            music_player->play_global_music(get<Name_Params>(m_events[m_outer_index][m_inner_index]).m_name);
            ++m_inner_index;
            ++m_inner_index2;
            break;

          case Script_Op::Play_Sound:
            g_sound_player->play_global_sound(get<Name_Params>(m_events[m_outer_index][m_inner_index]).m_name);
            ++m_inner_index;
            ++m_inner_index2;
            break;
        
          case Script_Op::Change_Map:
            for(long j{0}; j < static_cast<long>(MAPS.size()); ++j)
            {
              if(MAPS[j].m_id == get<Change_Map_Params>(m_events[m_outer_index][m_inner_index]).m_name)
              {
                s = make_tuple(false, "NULL", "NULL", m_outer_index == static_cast<long>(m_events.m_steps.size()), m_new_script, &MAPS[j], make_tuple(get<Change_Map_Params>(m_events[m_outer_index][m_inner_index]).m_hero_start_facing_dir, get<Change_Map_Params>(m_events[m_outer_index][m_inner_index]).m_start_tile_x, get<Change_Map_Params>(m_events[m_outer_index][m_inner_index]).m_start_tile_y, get<Change_Map_Params>(m_events[m_outer_index][m_inner_index]).m_start_layer));
              }
            }
            ++m_inner_index;
            ++m_inner_index2;
            break;

          case Script_Op::Add_Key_Item:
            world->add_key_item(get<Name_Params>(m_events[m_outer_index][m_inner_index]).m_name);
            ++m_inner_index;
            ++m_inner_index2;
            break;

          case Script_Op::Remove_Key_Item:
            world->remove_key_item(get<Name_Params>(m_events[m_outer_index][m_inner_index]).m_name);
            ++m_inner_index;
            ++m_inner_index2;
            break;

          case Script_Op::Has_Key_Item:
            if(world->has_key_item(get<Has_Key_Item_Params>(m_events[m_outer_index][m_inner_index]).m_item_name) == true)
            {
              m_new_script = get<Has_Key_Item_Params>(m_events[m_outer_index][m_inner_index]).m_have;
            }
            else
            {
              m_new_script = get<Has_Key_Item_Params>(m_events[m_outer_index][m_inner_index]).m_dont_have;
            }
            ++m_inner_index;
            ++m_inner_index2;
            break;

          case Script_Op::Add_Equipment:
            world->add_equipment(get<Name_Params>(m_events[m_outer_index][m_inner_index]).m_name);
            ++m_inner_index;
            ++m_inner_index2;
            break;

          case Script_Op::Add_Item:
            world->add_item(get<Name_Params>(m_events[m_outer_index][m_inner_index]).m_name);
            ++m_inner_index;
            ++m_inner_index2;
            break;
        
          case Script_Op::Check_Entity_Position:
            if(map->check_entity_position(get<Check_Entity_Position_Params>(m_events[m_outer_index][m_inner_index]).m_npc_name, get<Check_Entity_Position_Params>(m_events[m_outer_index][m_inner_index]).m_tile_offset_x, get<Check_Entity_Position_Params>(m_events[m_outer_index][m_inner_index]).m_tile_offset_y) == true)
            {
              m_new_script = get<Check_Entity_Position_Params>(m_events[m_outer_index][m_inner_index]).m_there;
            }
            else
            {
              m_new_script = get<Check_Entity_Position_Params>(m_events[m_outer_index][m_inner_index]).m_not_there;
            }
            ++m_inner_index;
            ++m_inner_index2;
            break;
        
          case Script_Op::Write_Map_Tile:
            map->write_tile(get<Write_Map_Tile_Params>(m_events[m_outer_index][m_inner_index]).m_layer,
                                    get<Write_Map_Tile_Params>(m_events[m_outer_index][m_inner_index]).m_sublayer,
                                    get<Write_Map_Tile_Params>(m_events[m_outer_index][m_inner_index]).m_new_collision,
                                    get<Write_Map_Tile_Params>(m_events[m_outer_index][m_inner_index]).m_tile_to_change_x,
                                    get<Write_Map_Tile_Params>(m_events[m_outer_index][m_inner_index]).m_tile_to_change_y,
                                    get<Write_Map_Tile_Params>(m_events[m_outer_index][m_inner_index]).m_tile_to_change_to);
            ++m_inner_index;
            ++m_inner_index2;
            break;
            
          case Script_Op::Join_Party:
            world->add_party_member(get<Party_Params>(m_events[m_outer_index][m_inner_index]).m_member);
            ++m_inner_index;
            ++m_inner_index2;
            break;

          case Script_Op::Wait:
            instant = false;
            m_tween_list.push_back(Tween_Data{"Wait", "NULL", 1, 0, static_cast<double>(get<Wait_Params>(m_events[m_outer_index][m_inner_index]).m_frames)});
            ++m_inner_index;
            break;

          case Script_Op::Fade_In_Caption:
            instant = false;
            m_tween_list.push_back(Tween_Data{"Fade In Caption", get<Fade_Params>(m_events[m_outer_index][m_inner_index]).m_name, 255 / (SCREEN_FPS * get<Fade_Params>(m_events[m_outer_index][m_inner_index]).m_seconds), 0, 255});
            ++m_inner_index;
            break;

          case Script_Op::Fade_Out_Caption:
            instant = false;
            m_tween_list.push_back(Tween_Data{"Fade Out Caption", get<Fade_Params>(m_events[m_outer_index][m_inner_index]).m_name, -(255 / (SCREEN_FPS * get<Fade_Params>(m_events[m_outer_index][m_inner_index]).m_seconds)), 255, 0});
            ++m_inner_index;
            break;

          case Script_Op::Fade_In_Image:
            instant = false;
            m_tween_list.push_back(Tween_Data{"Fade In Image", get<Fade_Params>(m_events[m_outer_index][m_inner_index]).m_name, 255 / (SCREEN_FPS * get<Fade_Params>(m_events[m_outer_index][m_inner_index]).m_seconds), 0, 255});
            ++m_inner_index;
            break;

          case Script_Op::Fade_Out_Image:
            instant = false;
            m_tween_list.push_back(Tween_Data{"Fade Out Image", get<Fade_Params>(m_events[m_outer_index][m_inner_index]).m_name, -(255 / (SCREEN_FPS * get<Fade_Params>(m_events[m_outer_index][m_inner_index]).m_seconds)), 255, 0});
            ++m_inner_index;
            break;

          case Script_Op::Fade_Out_Screen:
            if(m_screen_list.empty() == true)
            {
              m_screen_list.push_back(new Screen_Data{"Black Screen", 0});
              ++mem;
            }
            instant = false;
            m_tween_list.push_back(Tween_Data{"Fade Out Screen", "NULL", 255 / (SCREEN_FPS * get<Fade_Screen_Params>(m_events[m_outer_index][m_inner_index]).m_seconds), 0, 255});
            ++m_inner_index;
            break;

          case Script_Op::Fade_In_Screen:
            instant = false;
            m_tween_list.push_back(Tween_Data{"Fade In Screen", "NULL", -(255 / (SCREEN_FPS * get<Fade_Screen_Params>(m_events[m_outer_index][m_inner_index]).m_seconds)), 255, 0});
            ++m_inner_index;
            break;
        
          case Script_Op::Fade_In_NPC:
            instant = false;
            m_tween_list.push_back(Tween_Data{"Fade In NPC", get<Fade_Params>(m_events[m_outer_index][m_inner_index]).m_name, 255 / (SCREEN_FPS * get<Fade_Params>(m_events[m_outer_index][m_inner_index]).m_seconds), 0, 255});
            ++m_inner_index;
            break;

          case Script_Op::Fade_Out_NPC:
            instant = false;
            m_tween_list.push_back(Tween_Data{"Fade Out NPC", get<Fade_Params>(m_events[m_outer_index][m_inner_index]).m_name, -(255 / (SCREEN_FPS * get<Fade_Params>(m_events[m_outer_index][m_inner_index]).m_seconds)), 255, 0});
            ++m_inner_index;
            break;

          case Script_Op::Scroll_Image_Y:
            instant = false;
            for(long j{0}; j < static_cast<long>(m_image_list.size()); ++j)
            {
              if(m_image_list[j]->m_id == get<Scroll_Params>(m_events[m_outer_index][m_inner_index]).m_name)
              {
                target_index = j;
              }
            }
            if(target_index == -1)
            {
              crash("Error: \"" + get<Scroll_Params>(m_events[m_outer_index][m_inner_index]).m_name + "\" doesn't exist in the current script.");
            }
            m_tween_list.push_back(Tween_Data{"Scroll Image Y", get<Scroll_Params>(m_events[m_outer_index][m_inner_index]).m_name, (static_cast<double>(get<Scroll_Params>(m_events[m_outer_index][m_inner_index]).m_destination) - static_cast<double>(m_image_list[target_index]->m_y_pos)) / (SCREEN_FPS * get<Scroll_Params>(m_events[m_outer_index][m_inner_index]).m_seconds), static_cast<double>(m_image_list[target_index]->m_y_pos), static_cast<double>(get<Scroll_Params>(m_events[m_outer_index][m_inner_index]).m_destination)});
            ++m_inner_index;
            break;

          case Script_Op::Set_NPC_Path:
            instant = false;
            m_tween_list.push_back(Tween_Data{"Set NPC Path", get<Set_NPC_Path_Params>(m_events[m_outer_index][m_inner_index]).m_npc_name, 0, 0, 0});
            map->set_npc_path(get<Set_NPC_Path_Params>(m_events[m_outer_index][m_inner_index]).m_npc_name, get<Set_NPC_Path_Params>(m_events[m_outer_index][m_inner_index]).m_path);
            ++m_inner_index;
            break;

          case Script_Op::Say:
            instant = false;
            m_tween_list.push_back(Tween_Data{"Say", "NULL", 0, 0, 0});
            m_textbox = new Textbox;
            ++mem;
            m_textbox->add_text(get<Say_Params>(m_events[m_outer_index][m_inner_index]).m_text);
            m_textbox->create_fitted(map->get_entity_screen_pos_x(get<Say_Params>(m_events[m_outer_index][m_inner_index]).m_npc_name) + get<Say_Params>(m_events[m_outer_index][m_inner_index]).m_x_offset, map->get_entity_screen_pos_y(get<Say_Params>(m_events[m_outer_index][m_inner_index]).m_npc_name) + get<Say_Params>(m_events[m_outer_index][m_inner_index]).m_y_offset);
            ++m_inner_index;
            break;

          case Script_Op::Narrate:
            instant = false;
            m_tween_list.push_back(Tween_Data{"Narrate", "NULL", 0, 0, 0});
            m_textbox = new Textbox;
            ++mem;
            m_textbox->add_text(get<Name_Params>(m_events[m_outer_index][m_inner_index]).m_name);
            m_textbox->create_fixed(PANEL_MENU_UL_X, 0, PANEL_WIDTH_SCREEN, PANEL_HEIGHT_FOUR_LINES, false);
            ++m_inner_index;
            break;

          case Script_Op::Interact:
            m_new_script = map->get_npc_interact_script(get<Name_Params>(m_events[m_outer_index][m_inner_index]).m_name);
            ++m_inner_index;
            ++m_inner_index2;
            break;

          case Script_Op::Talk:
            instant = false;
            m_tween_list.push_back(Tween_Data{"Talk", "NULL", 0, 0, 0});
            m_textbox = new Textbox;
            ++mem;
            m_textbox->add_text(get<Talk_Params>(m_events[m_outer_index][m_inner_index]).m_text);
            if(get<Talk_Params>(m_events[m_outer_index][m_inner_index]).m_npc_name != "NULL")
            {
              m_textbox->add_title(get<Talk_Params>(m_events[m_outer_index][m_inner_index]).m_npc_name);
            }
            if(get<Talk_Params>(m_events[m_outer_index][m_inner_index]).m_portrait_image->m_name != "NULL")
            {
              m_textbox->add_portrait(get<Talk_Params>(m_events[m_outer_index][m_inner_index]).m_portrait_image);
            }
            m_textbox->create_fixed(PANEL_MENU_UL_X, SCREEN_HEIGHT - PANEL_HEIGHT_THREE_LINES - PANEL_SCREEN_OFFSET_Y, PANEL_WIDTH_SCREEN, PANEL_HEIGHT_THREE_LINES);
            ++m_inner_index;
            break;
        
          case Script_Op::Say_Choices:
            m_choices = get<Say_Choices_Params>(m_events[m_outer_index][m_inner_index]).m_choices;
            m_choice_scripts = get<Say_Choices_Params>(m_events[m_outer_index][m_inner_index]).m_script_decisions;
            instant = false;
            m_tween_list.push_back(Tween_Data{"Say Choices", "NULL", 0, 0, 0});
            m_textbox = new Textbox;
            ++mem;
            m_textbox->add_text(get<Say_Choices_Params>(m_events[m_outer_index][m_inner_index]).m_text);
            m_textbox->create_fitted_choices(map->get_entity_screen_pos_x(get<Say_Choices_Params>(m_events[m_outer_index][m_inner_index]).m_npc_name) + get<Say_Choices_Params>(m_events[m_outer_index][m_inner_index]).m_x_offset, map->get_entity_screen_pos_y(get<Say_Choices_Params>(m_events[m_outer_index][m_inner_index]).m_npc_name) + get<Say_Choices_Params>(m_events[m_outer_index][m_inner_index]).m_y_offset, m_choices);
            ++m_inner_index;
            break;

          case Script_Op::Move_Camera_To_Tile:
            instant = false;
            map->set_follow_cam("NULL");
            m_tween_list.push_back(Tween_Data{"Move Camera To Tile X", "NULL", static_cast<double>(((get<Move_Camera_To_Tile_Params>(m_events[m_outer_index][m_inner_index]).m_destination_tile_x * MAP_TILE_WIDTH + MAP_TILE_WIDTH / 2) - SCREEN_WIDTH / 2) - map->get_manual_cam_x() / (SCREEN_FPS * get<Move_Camera_To_Tile_Params>(m_events[m_outer_index][m_inner_index]).m_seconds)), static_cast<double>(map->get_manual_cam_x()), static_cast<double>((get<Move_Camera_To_Tile_Params>(m_events[m_outer_index][m_inner_index]).m_destination_tile_x * MAP_TILE_WIDTH + MAP_TILE_WIDTH / 2) - SCREEN_WIDTH / 2)});
            m_tween_list.push_back(Tween_Data{"Move Camera To Tile Y", "NULL", static_cast<double>(((get<Move_Camera_To_Tile_Params>(m_events[m_outer_index][m_inner_index]).m_destination_tile_y * map->get_tile_height() + map->get_tile_height() / 2) - SCREEN_HEIGHT / 2) - map->get_manual_cam_y() / (SCREEN_FPS * get<Move_Camera_To_Tile_Params>(m_events[m_outer_index][m_inner_index]).m_seconds)), static_cast<double>(map->get_manual_cam_y()), static_cast<double>((get<Move_Camera_To_Tile_Params>(m_events[m_outer_index][m_inner_index]).m_destination_tile_y * map->get_tile_height() + map->get_tile_height() / 2) - SCREEN_HEIGHT / 2)});
            ++m_inner_index;
            break;

          case Script_Op::Battle_Transition:
            instant = false;
            music_player->stop_global_music();
            g_sound_player->play_global_sound("Battle Transition");
            m_tween_list.push_back(Tween_Data{"Battle Transition", "NULL", 1, 0, BATTLE_TRANSITION_FRAMES});
            ++m_inner_index;
            break;

          default:
            crash("Error: Invalid script command.");
            break;
        }
      }
      if(instant == true)
      {
        ++m_outer_index;
        m_inner_index = 0;
        m_inner_index2 = 0;
      }
    }
  }
  else
  {
    for(long i{0}; i < static_cast<long>(m_tween_list.size()); ++i)
    {
      if(m_tween_list[i].m_done == false)
      {
        if(m_tween_list[i].m_function == "Fade In Caption" || m_tween_list[i].m_function == "Fade Out Caption")
        {
          m_tween_list[i].m_position += m_tween_list[i].m_velocity;
          long target_index{-1};
          for(long j{0}; j < static_cast<long>(m_caption_list.size()); ++j)
          {
            if(m_caption_list[j]->m_id == m_tween_list[i].m_target)
            {
              target_index = j;
            }
          }
          m_caption_list[target_index]->m_alpha = m_tween_list[i].m_position;
          if((m_tween_list[i].m_function == "Fade In Caption" && m_tween_list[i].m_position >= m_tween_list[i].m_end) || (m_tween_list[i].m_function == "Fade Out Caption" && m_tween_list[i].m_position <= m_tween_list[i].m_end))
          {
            m_tween_list[i].m_position = m_tween_list[i].m_end;
            m_caption_list[target_index]->m_alpha = m_tween_list[i].m_position;
            m_tween_list[i].m_done = true;
            ++m_inner_index2;
          }
        }

        else if(m_tween_list[i].m_function == "Fade In Image" || m_tween_list[i].m_function == "Fade Out Image")
        {
          m_tween_list[i].m_position += m_tween_list[i].m_velocity;
          long target_index{-1};
          for(long j{0}; j < static_cast<long>(m_image_list.size()); ++j)
          {
            if(m_image_list[j]->m_id == m_tween_list[i].m_target)
            {
              target_index = j;
            }
          }
          m_image_list[target_index]->m_alpha = m_tween_list[i].m_position;
          if((m_tween_list[i].m_function == "Fade In Image" && m_tween_list[i].m_position >= m_tween_list[i].m_end) || (m_tween_list[i].m_function == "Fade Out Image" && m_tween_list[i].m_position <= m_tween_list[i].m_end))
          {
            m_tween_list[i].m_position = m_tween_list[i].m_end;
            m_image_list[target_index]->m_alpha = m_tween_list[i].m_position;
            m_tween_list[i].m_done = true;
            ++m_inner_index2;
          }
        }

        else if(m_tween_list[i].m_function == "Fade In Screen" || m_tween_list[i].m_function == "Fade Out Screen")
        {
          m_tween_list[i].m_position += m_tween_list[i].m_velocity;
          m_screen_list[0]->m_alpha = m_tween_list[i].m_position;
          if((m_tween_list[i].m_function == "Fade Out Screen" && m_tween_list[i].m_position >= m_tween_list[i].m_end) || (m_tween_list[i].m_function == "Fade In Screen" && m_tween_list[i].m_position <= m_tween_list[i].m_end))
          {
            m_tween_list[i].m_position = m_tween_list[i].m_end;
            m_screen_list[0]->m_alpha = m_tween_list[i].m_position;
            m_tween_list[i].m_done = true;
            ++m_inner_index2;
          }
        }
        
        else if(m_tween_list[i].m_function == "Fade In NPC" || m_tween_list[i].m_function == "Fade Out NPC")
        {
          m_tween_list[i].m_position += m_tween_list[i].m_velocity;
          map->change_entity_alpha(m_tween_list[i].m_target, m_tween_list[i].m_position);
          if((m_tween_list[i].m_function == "Fade In NPC" && m_tween_list[i].m_position >= m_tween_list[i].m_end) || (m_tween_list[i].m_function == "Fade Out NPC" && m_tween_list[i].m_position <= m_tween_list[i].m_end))
          {
            m_tween_list[i].m_position = m_tween_list[i].m_end;
            map->change_entity_alpha(m_tween_list[i].m_target, m_tween_list[i].m_position);
            m_tween_list[i].m_done = true;
            ++m_inner_index2;
          }
        }

        else if(m_tween_list[i].m_function == "Scroll Image Y")
        {
          m_tween_list[i].m_position += m_tween_list[i].m_velocity;
          long target_index{-1};
          for(long j{0}; j < static_cast<long>(m_image_list.size()); ++j)
          {
            if(m_image_list[j]->m_id == m_tween_list[i].m_target)
            {
              target_index = j;
            }
          }
          m_image_list[target_index]->m_y_pos = m_tween_list[i].m_position;
          if((m_tween_list[i].m_start >= m_tween_list[i].m_end && m_tween_list[i].m_position <= m_tween_list[i].m_end) || (m_tween_list[i].m_start <= m_tween_list[i].m_end && m_tween_list[i].m_position >= m_tween_list[i].m_end))
          {
            m_tween_list[i].m_position = m_tween_list[i].m_end;
            m_image_list[target_index]->m_y_pos = m_tween_list[i].m_position;
            m_tween_list[i].m_done = true;
            ++m_inner_index2;
          }
        }

        else if(m_tween_list[i].m_function == "Wait")
        {
          m_tween_list[i].m_position += m_tween_list[i].m_velocity;
          if(m_tween_list[i].m_position >= m_tween_list[i].m_end)
          {
            m_tween_list[i].m_done = true;
            ++m_inner_index2;
          }
        }

        else if(m_tween_list[i].m_function == "Set NPC Path")
        {
          if(map->npc_path_finished(m_tween_list[i].m_target) == true)
          {
            m_tween_list[i].m_done = true;
            ++m_inner_index2;
          }
        }

        else if(m_tween_list[i].m_function == "Say" || m_tween_list[i].m_function == "Talk" || m_tween_list[i].m_function == "Narrate")
        {
          if(m_textbox->dead() == true)
          {
            m_tween_list[i].m_done = true;
            ++m_inner_index2;
            delete m_textbox;
            m_textbox = nullptr;
            --mem;
          }
        }

        else if(m_tween_list[i].m_function == "Say Choices")
        {
          if(m_textbox->dead() == true)
          {
            m_tween_list[i].m_done = true;
            ++m_inner_index2;
            m_new_script = m_choice_scripts[m_textbox->get_selected_item()];
            delete m_textbox;
            m_textbox = nullptr;
            --mem;
          }
        }

        else if(m_tween_list[i].m_function == "Move Camera To Tile X")
        {
          m_tween_list[i].m_position += m_tween_list[i].m_velocity;
          map->set_manual_cam_x(m_tween_list[i].m_position);
          if((m_tween_list[i].m_velocity < 0 && m_tween_list[i].m_position <= m_tween_list[i].m_end) || (m_tween_list[i].m_velocity >= 0 && m_tween_list[i].m_position >= m_tween_list[i].m_end))
          {
            m_tween_list[i].m_position = m_tween_list[i].m_end;
            map->set_manual_cam_x(m_tween_list[i].m_position);
            m_tween_list[i].m_done = true;
          }
        }
        
        else if(m_tween_list[i].m_function == "Move Camera To Tile Y")
        {
          m_tween_list[i].m_position += m_tween_list[i].m_velocity;
          map->set_manual_cam_y(m_tween_list[i].m_position);
          if((m_tween_list[i].m_velocity < 0 && m_tween_list[i].m_position <= m_tween_list[i].m_end) || (m_tween_list[i].m_velocity >= 0 && m_tween_list[i].m_position >= m_tween_list[i].m_end))
          {
            m_tween_list[i].m_position = m_tween_list[i].m_end;
            map->set_manual_cam_y(m_tween_list[i].m_position);
            m_tween_list[i].m_done = true;
            ++m_inner_index2;
          }
        }

        else if(m_tween_list[i].m_function == "Battle Transition")
        {
          m_tween_list[i].m_position += m_tween_list[i].m_velocity;
          if(m_tween_list[i].m_position >= m_tween_list[i].m_end - 10)
          {
            music_player->play_global_music("Battle");
            s = make_tuple(false, "Battle", "Battle Transition", m_outer_index == static_cast<long>(m_events.m_steps.size()), m_new_script, nullptr, make_tuple(Direction::Down, 0, 0, 0));
          }
          if(m_tween_list[i].m_position >= m_tween_list[i].m_end)
          {
            m_tween_list[i].m_done = true;
            ++m_inner_index2;
          }
        }
        
        else
        {
          crash("Error: Invalid tween function \"" + m_tween_list[i].m_function + "\".");
        }
      }
    }
    if(m_inner_index == m_inner_index2)
    {
      ++m_outer_index;
    }
  }
  return s;
}

void Script::render(const World* const world) const
{
  long index{-1};
  for(long i{0}; i < static_cast<long>(m_tween_list.size()); ++i)
  {
    if(m_tween_list[i].m_function == "Battle Transition")
    {
      index = i;
    }
  }

  if(index != -1)
  {
    DrawRing(Vector2{SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2}, SCREEN_HEIGHT / 2 - m_tween_list[index].m_position * 4, SCREEN_HEIGHT / 2 + m_tween_list[index].m_position * 4, 0, 360, 4, Color{255, 255, 255, 255});
  }

  for(long i{0}; i < static_cast<long>(m_screen_list.size()); ++i)
  {
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Color{static_cast<unsigned char>(m_screen_list[i]->m_red), static_cast<unsigned char>(m_screen_list[i]->m_green), static_cast<unsigned char>(m_screen_list[i]->m_blue), static_cast<unsigned char>(m_screen_list[i]->m_alpha)});
  }

  for(long i{0}; i < static_cast<long>(m_image_list.size()); ++i)
  {
    DrawTexturePro(m_image_list[i]->m_image, Rectangle{0, 0, static_cast<float>(m_image_list[i]->m_image.width), static_cast<float>(m_image_list[i]->m_image.height)}, Rectangle{static_cast<float>(SCREEN_WIDTH / 2 - m_image_list[i]->m_image.width / 2), static_cast<float>(m_image_list[i]->m_y_pos), static_cast<float>(m_image_list[i]->m_image.width), static_cast<float>(m_image_list[i]->m_image.height)}, Vector2{0, 0}, 0, Color{0xFF, 0xFF, 0xFF, static_cast<unsigned char>(m_image_list[i]->m_alpha)});
  }

  for(long i{0}; i < static_cast<long>(m_caption_list.size()); ++i)
  {
    world->render_text_center(m_caption_list[i]->m_font, m_caption_list[i]->m_text, m_caption_list[i]->m_y_pos, m_caption_list[i]->m_alpha);
  }

  if(m_textbox != nullptr)
  {
    m_textbox->render(world);
  }
}

Script::Caption_Data::Caption_Data(const string & font_name, const string & id, const string & text, const long & y_pos, const long & alpha)
{
  m_font = font_name;
  m_id = id;
  m_text = text;
  m_y_pos = y_pos;
  m_alpha = alpha;
}

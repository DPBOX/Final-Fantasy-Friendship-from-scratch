#include "Main.h"
#include "Tilemap.h"

Map_Handler::Script::~Script()
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

void Map_Handler::Script::update_input(Map_Handler* map_handler, World* world)
{
  if(m_textbox != nullptr)
  {
    m_textbox->update_input(world);
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

        switch(opcode)
        {
          case Script_Op::Teleport_Entity:
            map_handler->teleport_entity(get<Teleport_Entity_Params>(m_events[m_outer_index][m_inner_index]).m_entity_name, get<Teleport_Entity_Params>(m_events[m_outer_index][m_inner_index]).m_destination_tile_x, get<Teleport_Entity_Params>(m_events[m_outer_index][m_inner_index]).m_destination_tile_y);
            ++m_inner_index;
            ++m_inner_index2;
            break;
        
          case Script_Op::Switch_Game_State:
            map_handler->add_game_state(get<Name_Params>(m_events[m_outer_index][m_inner_index]).m_name);
            map_handler->pop_state();
            ++m_inner_index;
            ++m_inner_index2;
            break;

          case Script_Op::Add_Game_State:
            map_handler->add_game_state(get<Name_Params>(m_events[m_outer_index][m_inner_index]).m_name);
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

          case Script_Op::Show_NPC:
            map_handler->show_npc(get<Name_Params>(m_events[m_outer_index][m_inner_index]).m_name);
            ++m_inner_index;
            ++m_inner_index2;
            break;
        
          case Script_Op::Hide_NPC:
            map_handler->hide_npc(get<Name_Params>(m_events[m_outer_index][m_inner_index]).m_name);
            ++m_inner_index;
            ++m_inner_index2;
            break;
        
          case Script_Op::Lock_Controls:
            map_handler->lock_controls();
            ++m_inner_index;
            ++m_inner_index2;
            break;
        
          case Script_Op::Unlock_Controls:
            map_handler->unlock_controls();
            ++m_inner_index;
            ++m_inner_index2;
            break;

          case Script_Op::Play_Sound:

            break;
        
          case Script_Op::Change_Map:
            for(long j{0}; j < static_cast<long>(MAPS.size()); ++j)
            {
              if(MAPS[j].m_id == get<Name_Params>(m_events[m_outer_index][m_inner_index]).m_name)
              {
                map_handler->add_map(MAPS[j], map_handler);
              }
            }
            ++m_inner_index;
            ++m_inner_index2;
            break;
        
          case Script_Op::Deactivate_Trigger:
            map_handler->deactivate_trigger();
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
        
          case Script_Op::Check_Entity_Position:
            if(map_handler->check_entity_position(get<Check_Entity_Position_Params>(m_events[m_outer_index][m_inner_index]).m_npc_name, get<Check_Entity_Position_Params>(m_events[m_outer_index][m_inner_index]).m_tile_offset_x, get<Check_Entity_Position_Params>(m_events[m_outer_index][m_inner_index]).m_tile_offset_y) == true)
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
            map_handler->write_tile(get<Write_Map_Tile_Params>(m_events[m_outer_index][m_inner_index]).m_layer,
                                    get<Write_Map_Tile_Params>(m_events[m_outer_index][m_inner_index]).m_sublayer,
                                    get<Write_Map_Tile_Params>(m_events[m_outer_index][m_inner_index]).m_new_collision,
                                    get<Write_Map_Tile_Params>(m_events[m_outer_index][m_inner_index]).m_tile_to_change_x,
                                    get<Write_Map_Tile_Params>(m_events[m_outer_index][m_inner_index]).m_tile_to_change_y,
                                    get<Write_Map_Tile_Params>(m_events[m_outer_index][m_inner_index]).m_tile_to_change_to);
            ++m_inner_index;
            ++m_inner_index2;
            break;
            
          case Script_Op::Join_Party:
            world->add_party_member(*(get<Party_Params>(m_events[m_outer_index][m_inner_index]).m_member));
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

          case Script_Op::Set_NPC_Path:
            instant = false;
            m_tween_list.push_back(Tween_Data{"Set NPC Path", get<Set_NPC_Path_Params>(m_events[m_outer_index][m_inner_index]).m_npc_name, 0, 0, 0});
            map_handler->set_npc_path(get<Set_NPC_Path_Params>(m_events[m_outer_index][m_inner_index]).m_npc_name, get<Set_NPC_Path_Params>(m_events[m_outer_index][m_inner_index]).m_path);
            ++m_inner_index;
            break;

          case Script_Op::Say:
            instant = false;
            m_tween_list.push_back(Tween_Data{"Say", "NULL", 0, 0, 0});
            m_textbox = new Textbox;
            ++mem;
            m_textbox->add_text(get<Say_Params>(m_events[m_outer_index][m_inner_index]).m_text);
            m_textbox->create_fitted(map_handler->get_entity_screen_pos_x(get<Say_Params>(m_events[m_outer_index][m_inner_index]).m_npc_name) + get<Say_Params>(m_events[m_outer_index][m_inner_index]).m_x_offset, map_handler->get_entity_screen_pos_y(get<Say_Params>(m_events[m_outer_index][m_inner_index]).m_npc_name) + get<Say_Params>(m_events[m_outer_index][m_inner_index]).m_y_offset, world);
            ++m_inner_index;
            break;

          case Script_Op::Interact:
            m_new_script = map_handler->get_npc_script(get<Name_Params>(m_events[m_outer_index][m_inner_index]).m_name);
            ++m_inner_index;
            ++m_inner_index2;
            break;

          case Script_Op::Talk:
            instant = false;
            m_tween_list.push_back(Tween_Data{"Talk", "NULL", 0, 0, 0});
            m_textbox = new Textbox;
            ++mem;
            m_textbox->add_text(get<Say_Params>(m_events[m_outer_index][m_inner_index]).m_text);
            m_textbox->add_title(get<Say_Params>(m_events[m_outer_index][m_inner_index]).m_npc_name);
            m_textbox->add_portrait(TEMPEST_SMALL_PORTRAIT_IMAGE);
            m_textbox->create_fixed(TEXTBOX_PADDING_SCREEN, SCREEN_HEIGHT - (TEXTBOX_PADDING_SHORT * 2 + FONT_TEXT_HEIGHT * 4) - TEXTBOX_PADDING_SCREEN_Y, SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2, TEXTBOX_PADDING_SHORT * 2 + FONT_TEXT_HEIGHT * 4, world);
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
            m_textbox->create_fitted_choices(map_handler->get_entity_screen_pos_x(get<Say_Choices_Params>(m_events[m_outer_index][m_inner_index]).m_npc_name) + get<Say_Choices_Params>(m_events[m_outer_index][m_inner_index]).m_x_offset, map_handler->get_entity_screen_pos_y(get<Say_Choices_Params>(m_events[m_outer_index][m_inner_index]).m_npc_name) + get<Say_Choices_Params>(m_events[m_outer_index][m_inner_index]).m_y_offset, m_choices, world);
            ++m_inner_index;
            break;

          case Script_Op::Move_Camera_To_Tile:
            instant = false;
            map_handler->set_follow_cam("NULL");
            m_tween_list.push_back(Tween_Data{"Move Camera To Tile X", "NULL", static_cast<double>(((get<Move_Camera_To_Tile_Params>(m_events[m_outer_index][m_inner_index]).m_destination_tile_x * map_handler->get_map_tile_width() + map_handler->get_map_tile_width() / 2) - SCREEN_WIDTH / 2) - map_handler->get_manual_cam_x() / (SCREEN_FPS * get<Move_Camera_To_Tile_Params>(m_events[m_outer_index][m_inner_index]).m_seconds)), static_cast<double>(map_handler->get_manual_cam_x()), static_cast<double>((get<Move_Camera_To_Tile_Params>(m_events[m_outer_index][m_inner_index]).m_destination_tile_x * map_handler->get_map_tile_width() + map_handler->get_map_tile_width() / 2) - SCREEN_WIDTH / 2)});
            m_tween_list.push_back(Tween_Data{"Move Camera To Tile Y", "NULL", static_cast<double>(((get<Move_Camera_To_Tile_Params>(m_events[m_outer_index][m_inner_index]).m_destination_tile_y * map_handler->get_map_tile_height() + map_handler->get_map_tile_height() / 2) - SCREEN_HEIGHT / 2) - map_handler->get_manual_cam_y() / (SCREEN_FPS * get<Move_Camera_To_Tile_Params>(m_events[m_outer_index][m_inner_index]).m_seconds)), static_cast<double>(map_handler->get_manual_cam_y()), static_cast<double>((get<Move_Camera_To_Tile_Params>(m_events[m_outer_index][m_inner_index]).m_destination_tile_y * map_handler->get_map_tile_height() + map_handler->get_map_tile_height() / 2) - SCREEN_HEIGHT / 2)});
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
          map_handler->change_entity_alpha(m_tween_list[i].m_target, m_tween_list[i].m_position);
          if((m_tween_list[i].m_function == "Fade In NPC" && m_tween_list[i].m_position >= m_tween_list[i].m_end) || (m_tween_list[i].m_function == "Fade Out NPC" && m_tween_list[i].m_position <= m_tween_list[i].m_end))
          {
            m_tween_list[i].m_position = m_tween_list[i].m_end;
            map_handler->change_entity_alpha(m_tween_list[i].m_target, m_tween_list[i].m_position);
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
          if(map_handler->npc_path_finished(m_tween_list[i].m_target) == true)
          {
            m_tween_list[i].m_done = true;
            ++m_inner_index2;
          }
        }

        else if(m_tween_list[i].m_function == "Say" || m_tween_list[i].m_function == "Talk")
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
          map_handler->set_manual_cam_x(m_tween_list[i].m_position);
          if((m_tween_list[i].m_velocity < 0 && m_tween_list[i].m_position <= m_tween_list[i].m_end) || (m_tween_list[i].m_velocity >= 0 && m_tween_list[i].m_position >= m_tween_list[i].m_end))
          {
            m_tween_list[i].m_position = m_tween_list[i].m_end;
            map_handler->set_manual_cam_x(m_tween_list[i].m_position);
            m_tween_list[i].m_done = true;
          }
        }
        
        else if(m_tween_list[i].m_function == "Move Camera To Tile Y")
        {
          m_tween_list[i].m_position += m_tween_list[i].m_velocity;
          map_handler->set_manual_cam_y(m_tween_list[i].m_position);
          if((m_tween_list[i].m_velocity < 0 && m_tween_list[i].m_position <= m_tween_list[i].m_end) || (m_tween_list[i].m_velocity >= 0 && m_tween_list[i].m_position >= m_tween_list[i].m_end))
          {
            m_tween_list[i].m_position = m_tween_list[i].m_end;
            map_handler->set_manual_cam_y(m_tween_list[i].m_position);
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
}

void Map_Handler::Script::render(World* world) const
{
  for(long i{0}; i < static_cast<long>(m_screen_list.size()); ++i)
  {
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Color{static_cast<unsigned char>(m_screen_list[i]->m_red), static_cast<unsigned char>(m_screen_list[i]->m_green), static_cast<unsigned char>(m_screen_list[i]->m_blue), static_cast<unsigned char>(m_screen_list[i]->m_alpha)});
  }
  
  if(m_textbox != nullptr)
  {
    m_textbox->render(world);
  }

  for(long i{0}; i < static_cast<long>(m_caption_list.size()); ++i)
  {
    world->render_text_center(m_caption_list[i]->m_font, m_caption_list[i]->m_text, m_caption_list[i]->m_y_pos, m_caption_list[i]->m_alpha);
  }
}

bool Map_Handler::Script::finished() const
{
  return m_outer_index == static_cast<long>(m_events.m_steps.size());
}

long Map_Handler::Script::get_next_script() const
{
  return m_new_script;
}

Map_Handler::Script::Caption_Data::Caption_Data(const long & font, const string & id, const string & text, const long & y_pos, const long & alpha)
{
  m_id = id;
  m_text = text;
  m_y_pos = y_pos;
  m_alpha = alpha;
  m_font = font;
}

#include "Main.h"
#include "State_Machine.h"
#include "Selection.hpp"

void State_Machine::set_start_state_front_menu(World* world)
{
  state_ID = FRONT_MENU_STATE;
  next_state = NULL_STATE;
  current_state = new State_Machine::Front_Menu(world);
  ++mem;
  world->play_global_sound("Confirm");
}

State_Machine::~State_Machine()
{
  delete current_state;
  current_state = nullptr;
  --mem;
}

void State_Machine::update()
{
  current_state->update();
}

void State_Machine::update_input(State_Machine* machine, World* world)
{
  current_state->update_input(machine, world);
}

void State_Machine::change_state(World* world)
{
  //If the state needs to be changed
  if(next_state != NULL_STATE)
  {
    //Delete the current state
    delete current_state;
    current_state = nullptr;
    --mem;
    //Change the state
    switch(next_state)
    {
      case FRONT_MENU_STATE:
        current_state = new State_Machine::Front_Menu(world);
        ++mem;
        break;
      case ITEM_MENU_STATE:
        current_state = new State_Machine::Item_Menu(world);
        ++mem;
        break;
      case STATUS_MENU_STATE:
        current_state = new State_Machine::Status_Menu(world, m_selected_party_member_name);
        ++mem;
        break;
      default:
        break;
    }
        
    //Change the current state ID
    state_ID = next_state;
        
    //NULL the next state ID
    next_state = NULL_STATE;   
    m_selected_party_member_name = "NULL";
  }
  return;
}

void State_Machine::render(World* world) const
{
  current_state->render(world);
}

void State_Machine::set_next_state(const state_list & new_state, const string & selected_party_member_name)
{
  //Set the next state
  next_state = new_state;
  
  if(selected_party_member_name != "NULL")
  {
    m_selected_party_member_name = selected_party_member_name;
  }
}

bool State_Machine::check_exit() const
{
  return state_ID == FRONT_MENU_STATE && current_state != nullptr && current_state->root_menu_cursor_shown() == true;
}

bool State_Machine::Machine_State::root_menu_cursor_shown() const
{
  return false;
}

State_Machine::Front_Menu::Front_Menu(World* world)
{
  vector<Player_Summary*> party_info{};
  vector<Player_Summary*> party_info2{};
  for(long i{0}; i < world->get_party_size(); ++i)
  {
    party_info.push_back(new Player_Summary{TEXTBOX_PADDING_SCREEN + (SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2) / FRONT_MENU_SPLIT, TEXTBOX_PADDING_SCREEN_Y + PLAYER_SUMMARY_SECTION_PADDING + i * (TEXT_FONT_HEIGHT * 4 + PLAYER_SUMMARY_SECTION_PADDING), world->get_party_member_name(i), world->get_party_member_row(world->get_party_member_name(i))});
    ++mem;
    party_info2.push_back(new Player_Summary{TEXTBOX_PADDING_SCREEN + (SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2) / FRONT_MENU_SPLIT, TEXTBOX_PADDING_SCREEN_Y + PLAYER_SUMMARY_SECTION_PADDING + i * (TEXT_FONT_HEIGHT * 4 + PLAYER_SUMMARY_SECTION_PADDING), world->get_party_member_name(i), world->get_party_member_row(world->get_party_member_name(i))});
    ++mem;
  }
  m_party_info.add(party_info);

  m_gold = new Panel;
  ++mem;
  m_map = new Panel;
  ++mem;
  m_party = new Panel;
  ++mem;
  m_menu = new Panel;
  ++mem;
  m_formation = new Panel;
  ++mem;
  m_selection = new Selection{to_pointers(FRONT_MENU_CHOICES), NUM_FRONT_MENU_COLUMNS, NUM_FRONT_MENU_CHOICES, NUM_FRONT_MENU_CHOICES, TEXT_FONT_HEIGHT};
  ++mem;
  m_party_menu = new Selection{party_info2, 1, MAX_PARTY_SIZE, world->get_party_size(), TEXT_FONT_HEIGHT * 4 + PLAYER_SUMMARY_SECTION_PADDING, false};
  ++mem;
  m_selection->set_position(TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG, TEXTBOX_PADDING_SHORT + TEXTBOX_PADDING_SCREEN_Y);
  m_selection->set_spacing_x((SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2) / FRONT_MENU_SPLIT);
  m_party_menu->set_position(TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG + (SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2) / FRONT_MENU_SPLIT, TEXTBOX_PADDING_SHORT + TEXTBOX_PADDING_SCREEN_Y + PLAYER_SUMMARY_SECTION_PADDING);
  m_party_menu->set_spacing_x((SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2) - (SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2) / FRONT_MENU_SPLIT);
  m_gold->set_position(TEXTBOX_PADDING_SCREEN, SCREEN_HEIGHT - (2 * TEXT_FONT_HEIGHT + TEXTBOX_PADDING_SHORT * 2) - TEXTBOX_PADDING_SCREEN_Y, (SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2) / FRONT_MENU_SPLIT, 2 * TEXT_FONT_HEIGHT + TEXTBOX_PADDING_SHORT * 2);
  m_map->set_position(TEXTBOX_PADDING_SCREEN, SCREEN_HEIGHT - ((2 * TEXT_FONT_HEIGHT + TEXTBOX_PADDING_SHORT * 2) * 2) - TEXTBOX_PADDING_SCREEN_Y, (SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2) / FRONT_MENU_SPLIT, 2 * TEXT_FONT_HEIGHT + TEXTBOX_PADDING_SHORT * 2);
  m_party->set_position(TEXTBOX_PADDING_SCREEN + (SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2) / FRONT_MENU_SPLIT, TEXTBOX_PADDING_SCREEN_Y, (SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2) - (SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2) / FRONT_MENU_SPLIT, SCREEN_HEIGHT - TEXTBOX_PADDING_SCREEN_Y * 2);
  m_menu->set_position(TEXTBOX_PADDING_SCREEN, TEXTBOX_PADDING_SCREEN_Y, (SCREEN_WIDTH  - TEXTBOX_PADDING_SCREEN * 2) / FRONT_MENU_SPLIT, TEXT_FONT_HEIGHT * NUM_FRONT_MENU_CHOICES + TEXTBOX_PADDING_SHORT * 2);
  m_formation->set_position(TEXTBOX_PADDING_SCREEN, TEXTBOX_PADDING_SCREEN_Y, (SCREEN_WIDTH  - TEXTBOX_PADDING_SCREEN * 2) / FRONT_MENU_SPLIT, TEXT_FONT_HEIGHT * FORMATION_MENU_TEXT.size() + TEXTBOX_PADDING_SHORT * 2);
}

State_Machine::Front_Menu::~Front_Menu()
{
  delete m_gold;
  delete m_map;
  delete m_party;
  delete m_menu;
  delete m_selection;
  delete m_party_menu;
  delete m_formation;
  m_gold = nullptr;
  m_map = nullptr;
  m_party = nullptr;
  m_menu = nullptr;
  m_selection = nullptr;
  m_party_menu = nullptr;
  m_formation = nullptr;
  --mem;
  --mem;
  --mem;
  --mem;
  --mem;
  --mem;
  --mem;
}

void State_Machine::Front_Menu::update_input(State_Machine* machine, World* world)
{
  m_selection->update_input(world);
  m_party_menu->update_input(world);
  for(long i{0}; i < m_party_info.get_list_size(); ++i)
  {
    m_party_info[i]->update_tweens(world);
  }

  string highlighted_item{"NULL"};
  long highlighted_index{-1};
  string switch_name{"NULL"};
  long switch_index{-1};

  if(m_selection->cursor_shown() == true)
  {
    highlighted_index = m_selection->get_highlighted_item();
    if(IsKeyPressed(KEY_Z) == true)
    {
      if(highlighted_index == 0)
      {
        world->play_global_sound("Confirm");
        machine->set_next_state(State_Machine::ITEM_MENU_STATE);
      }
      else if(highlighted_index == 1)
      {
        world->play_global_sound("Buzzer");
        m_option_selected = FRONT_MENU_CHOICES[1];
      }
      else if(highlighted_index == 2)
      {
        world->play_global_sound("Confirm");
        m_selection->hide_cursor();
        m_party_menu->show_cursor();
        m_option_selected = FRONT_MENU_CHOICES[2];
      }
      else if(highlighted_index == 3)
      {
        world->play_global_sound("Confirm");
        m_selection->hide_cursor();
        m_party_menu->show_cursor();
        m_option_selected = FRONT_MENU_CHOICES[3];
      }
      else if(highlighted_index == 4)
      {
        world->play_global_sound("Buzzer");
      }
      else
      {
        crash("Error: Tried to select invalid option " + to_string(highlighted_index) + " in selection menu \"" + m_selection->c_get_options(world) + "\".");
      }
    }
  }
  else if(m_party_menu->cursor_shown() == true)
  {
    for(long i{0}; i < m_party_info.get_list_size(); ++i)
    {
      if(m_option_selected == FRONT_MENU_CHOICES[3] && m_party_info[i]->get_switch() == true)
      {
        switch_index = i;
        switch_name = world->get_party_member_name(i);
      }
    }
    for(long i{0}; i < m_party_info.get_list_size(); ++i)
    {
      if(i == m_party_menu->get_highlighted_item())
      {
        highlighted_item = world->get_party_member_name(i);
        highlighted_index = i;
      }
    }

    if(m_option_selected == FRONT_MENU_CHOICES[2])
    {
      if(IsKeyPressed(KEY_Z) == true)
      {
        world->play_global_sound("Confirm");
        machine->set_next_state(State_Machine::STATUS_MENU_STATE, highlighted_item);
      }
    }
    else if(m_option_selected == FRONT_MENU_CHOICES[3])
    {
      if(IsKeyPressed(KEY_LEFT) == true)
      {
        if(world->set_party_member_front_row(highlighted_item) == true)
        {
          world->play_global_sound("Cursor");
          m_party_info[highlighted_item]->set_portrait_tween(true);
         }
      }
      if(IsKeyPressed(KEY_RIGHT) == true)
      {
        if(world->set_party_member_back_row(highlighted_item) == true)
        {
          world->play_global_sound("Cursor");
          m_party_info[highlighted_item]->set_portrait_tween(false);
        }
      }
      if(IsKeyPressed(KEY_Z) == true)
      {
        world->play_global_sound("Confirm");
        if(highlighted_index == switch_index || switch_index == -1)
        {
          m_party_info[highlighted_item]->toggle_switch_rect();
        }
        else if(switch_index != -1)
        {
          m_party_info[switch_name]->toggle_switch_rect();
          world->swap_party_members(highlighted_item, switch_name);
          m_party_info[highlighted_item]->set_y_tween(switch_index, highlighted_index, 0);
          m_party_info[switch_name]->set_y_tween(highlighted_index, switch_index, 0);
          m_party_info.swap(highlighted_item, switch_name);

          vector<Player_Summary*> party_info{};
          for(long i{0}; i < world->get_party_size(); ++i)
          {
            party_info.push_back(new Player_Summary{TEXTBOX_PADDING_SCREEN + (SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2) / FRONT_MENU_SPLIT, TEXTBOX_PADDING_SCREEN_Y + PLAYER_SUMMARY_SECTION_PADDING + i * (TEXT_FONT_HEIGHT * 4 + PLAYER_SUMMARY_SECTION_PADDING), world->get_party_member_name(i), world->get_party_member_row(world->get_party_member_name(i))});
            ++mem;
          }
          m_party_menu->rebuild_choices(party_info);
        }
      }
    }

    if(IsKeyPressed(KEY_X) == true)
    {
      world->play_global_sound("Back");
      m_party_menu->hide_cursor();
      m_selection->show_cursor();
      m_option_selected = -1;
      if(switch_index != -1)
      {
        m_party_info[switch_name]->toggle_switch_rect();
      }
    }
  }
}

void State_Machine::Front_Menu::render(World* world) const
{
  m_gold->render(world);
  m_map->render(world);
  m_party->render(world);
  m_menu->render(world);
  m_selection->render(world);
  m_party_menu->render(world);
  string map_first_line{split_map_name_text(0)};
  string map_second_line{split_map_name_text(1)};
  world->render_text("Text", map_first_line, TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG, SCREEN_HEIGHT - (4 * world->get_font_height("Text") + TEXTBOX_PADDING_SHORT * 3) - TEXTBOX_PADDING_SCREEN_Y);
  world->render_text("Text", map_second_line, TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG, SCREEN_HEIGHT - (3 * world->get_font_height("Text") + TEXTBOX_PADDING_SHORT * 3) - TEXTBOX_PADDING_SCREEN_Y);
  world->render_text("Text", to_string(world->get_money()) + " Bits", TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG, SCREEN_HEIGHT - (2 * world->get_font_height("Text") + TEXTBOX_PADDING_SHORT) - TEXTBOX_PADDING_SCREEN_Y);
  world->render_text("Text", "Play Time: " + world->get_time(), TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG, SCREEN_HEIGHT - (world->get_font_height("Text") + TEXTBOX_PADDING_SHORT) - TEXTBOX_PADDING_SCREEN_Y);
  if(m_option_selected == FRONT_MENU_CHOICES[3])
  {
    m_formation->render(world);
    for(long i{0}; i < static_cast<long>(FORMATION_MENU_TEXT.size()); ++i)
    {
      world->render_text("Text", FORMATION_MENU_TEXT[i], TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT + world->get_font_height("Text") * i);
    }
  }

  for(long i{0}; i < m_party_info.get_list_size(); ++i)
  {
    m_party_info[i]->render(world);
  }
}

bool State_Machine::Front_Menu::root_menu_cursor_shown() const
{
  return m_selection->cursor_shown();
}

string State_Machine::Front_Menu::split_map_name_text(const bool & line_number) const
{
  long num_words{count_words(m_top_bar_text)};
  string word1{""};
  string word2{""};
  long i{0};
  switch(num_words)
  {
    case 1:
      return line_number == 0 ? m_top_bar_text : "";
      break;
      
    case 2:
      while(m_top_bar_text[i] != ' ')
      {
        ++i;
      }
      word1 = m_top_bar_text.substr(0, i);
      word2 = m_top_bar_text.substr(i + 1, m_top_bar_text.length());
      return line_number == 0 ? word1 : word2;
      break;
      
    case 3:
    case 4:
      while(m_top_bar_text[i] != ' ')
      {
        ++i;
      }
      ++i;
      while(m_top_bar_text[i] != ' ')
      {
        ++i;
      }
      word1 = m_top_bar_text.substr(0, i);
      word2 = m_top_bar_text.substr(i + 1, m_top_bar_text.length());
      return line_number == 0 ? word1 : word2;
      break;

    default:
      crash("Error: " + m_top_bar_text + " has too many words.");
      break;
  }
  return "NULL";
}

State_Machine::Item_Menu::Item_Menu(World* world)
{
  m_switch = new Panel;
  m_item_text = new Panel;
  m_description = new Panel;
  m_item_list = new Panel;

  m_switch->set_position(TEXTBOX_PADDING_SCREEN + (SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2) / ITEM_MENU_SPLIT, TEXTBOX_PADDING_SCREEN_Y, (SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2) - (SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2) / ITEM_MENU_SPLIT, TEXT_FONT_HEIGHT + TEXTBOX_PADDING_SHORT * 2);
  m_item_text->set_position(TEXTBOX_PADDING_SCREEN, TEXTBOX_PADDING_SCREEN_Y, (SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2) / ITEM_MENU_SPLIT, TEXT_FONT_HEIGHT + TEXTBOX_PADDING_SHORT * 2);
  m_description->set_position(TEXTBOX_PADDING_SCREEN, TEXTBOX_PADDING_SCREEN_Y + TEXT_FONT_HEIGHT + TEXTBOX_PADDING_SHORT * 2, SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2, TEXT_FONT_HEIGHT + TEXTBOX_PADDING_SHORT * 2);
  m_item_list->set_position(TEXTBOX_PADDING_SCREEN, TEXTBOX_PADDING_SCREEN_Y + TEXT_FONT_HEIGHT * 2 + TEXTBOX_PADDING_SHORT * 4, SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2, SCREEN_HEIGHT - TEXTBOX_PADDING_SCREEN_Y * 2 - (TEXT_FONT_HEIGHT + TEXTBOX_PADDING_SHORT * 2) * 2);
  m_category = new Selection{to_pointers(ITEM_MENU_CHOICES), NUM_ITEM_MENU_CHOICES, 1, 1, TEXT_FONT_HEIGHT};
  m_category->set_position(TEXTBOX_PADDING_SCREEN + (SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2) / ITEM_MENU_SPLIT + TEXTBOX_PADDING_LONG, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT);
  m_category->set_spacing_x(SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2 - TEXTBOX_PADDING_LONG * 2 - ((SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2) / ITEM_MENU_SPLIT));
  m_items = new Selection{to_pointers(world->get_items()), NUM_ITEM_MENU_COLUMNS, MAX_ITEM_MENU_ROWS, ITEM_MENU_ROWS, TEXT_FONT_HEIGHT, false, true, "Items"};
  m_items->set_position(TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG, TEXTBOX_PADDING_SCREEN_Y + TEXT_FONT_HEIGHT * 2 + TEXTBOX_PADDING_SHORT * 5);
  m_items->set_spacing_x(SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2 - TEXTBOX_PADDING_LONG * 2);
  m_key_items = new Selection{to_pointers(world->get_key_items()), NUM_ITEM_MENU_COLUMNS, MAX_ITEM_MENU_ROWS, ITEM_MENU_ROWS, TEXT_FONT_HEIGHT, false, false, "Key Items"};
  m_key_items->set_position(TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG, TEXTBOX_PADDING_SCREEN_Y + TEXT_FONT_HEIGHT * 2 + TEXTBOX_PADDING_SHORT * 5);
  m_key_items->set_spacing_x(SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2 - TEXTBOX_PADDING_LONG * 2);
  ++mem;
  ++mem;
  ++mem;
  ++mem;
  ++mem;
  ++mem;
  ++mem;
}

State_Machine::Item_Menu::~Item_Menu()
{
  delete m_switch;
  delete m_item_text;
  delete m_description;
  delete m_item_list;
  delete m_category;
  delete m_items;
  delete m_key_items;
  m_switch = nullptr;
  m_item_text = nullptr;
  m_description = nullptr;
  m_item_list = nullptr;
  m_category = nullptr;
  m_items = nullptr;
  m_key_items = nullptr;
  --mem;
  --mem;
  --mem;
  --mem;
  --mem;
  --mem;
  --mem;
}

void State_Machine::Item_Menu::update_input(State_Machine* machine, World* world)
{
  if(IsKeyPressed(KEY_X) == true && m_category->cursor_shown() == true)
  {
    world->play_global_sound("Back");
    machine->set_next_state(State_Machine::FRONT_MENU_STATE);
  }

  long highlighted_item{0};

  m_category->update_input(world);
  m_items->update_input(world);
  m_key_items->update_input(world);

  if(m_category->cursor_shown() == true)
  {
    highlighted_item = m_category->get_highlighted_item();
    if(highlighted_item == 0)
    {
      m_key_items->hide_menu();
      m_items->show_menu();
    }
    else if(highlighted_item == 1)
    {
      m_items->hide_menu();
      m_key_items->show_menu();
    }
    else
    {
      crash("Error: Tried to highlight invalid option " + to_string(highlighted_item) + " in selection menu \"" + m_category->c_get_options(world) + "\".");
    }

    if(IsKeyPressed(KEY_Z) == true)
    {
      if(highlighted_item == 0)
      {
        if(world->has_items() == true)
        {
          world->play_global_sound("Confirm");
          m_category->hide_cursor();
          m_items->show_cursor();
        }
        else
        {
          world->play_global_sound("Buzzer");
        }
      }
      else if(highlighted_item == 1)
      {
        if(world->has_key_items() == true)
        {
          world->play_global_sound("Confirm");
          m_category->hide_cursor();
          m_key_items->show_cursor();
        }
        else
        {
          world->play_global_sound("Buzzer");
        }
      }
      else
      {
        crash("Error: Tried to select invalid option " + to_string(highlighted_item) + " in selection menu \"" + m_category->c_get_options(world) + "\".");
      }
    }
  }
  else if(m_items->cursor_shown() == true || m_key_items->cursor_shown() == true)
  {
    if(IsKeyPressed(KEY_X) == true)
    {
      world->play_global_sound("Back");
      m_items->hide_cursor();
      m_key_items->hide_cursor();
      m_category->show_cursor();
    }
    else if(m_items->cursor_shown() == true)
    {
      if(IsKeyPressed(KEY_Z) == true)
      {
        world->play_global_sound("Confirm");
        world->remove_item(*m_items->get_highlighted_item_obj());
        m_items->update_input(world);
      }
      if(world->has_items() == false)
      {
        m_items->hide_cursor();
        m_key_items->hide_cursor();
        m_category->show_cursor();
      }
    }
    else if(m_key_items->cursor_shown() == true)
    {
      if(IsKeyPressed(KEY_Z) == true)
      {
        world->play_global_sound("Buzzer");
      }
    }
  }
}

void State_Machine::Item_Menu::render(World* world) const
{
  m_switch->render(world);
  m_item_text->render(world);
  m_description->render(world);
  m_item_list->render(world);
  m_category->render(world);
  m_items->render(world);
  m_key_items->render(world);
  world->render_text("Text", m_top_bar_text, TEXTBOX_PADDING_SCREEN + (SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2) / ITEM_MENU_SPLIT / 2 - world->get_word_width("Text", m_top_bar_text) / 2, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT);
  if(m_items->cursor_shown() == true)
  {
    world->render_text("Text", world->get_item_description(*m_items->get_highlighted_item_obj()), TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT * 3 + world->get_font_height("Text"));
  }
  if(m_key_items->cursor_shown() == true)
  {
    world->render_text("Text", world->get_item_description(*m_key_items->get_highlighted_item_obj()), TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT * 3 + world->get_font_height("Text"));
  }
}

State_Machine::Status_Menu::Status_Menu(World* world, const string & character_name)
{
  long section_width{(SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2 - TEXTBOX_PADDING_LONG * 2) / 3};
  m_character_name = character_name;
  m_panel = new Panel;
  ++mem;
  m_panel->set_position(TEXTBOX_PADDING_SCREEN, TEXTBOX_PADDING_SCREEN_Y, SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2, SCREEN_HEIGHT - TEXTBOX_PADDING_SCREEN_Y * 2);
  m_selection = new Selection{to_pointers(STAT_STRINGS), NUM_STATUS_MENU_COLUMNS, STATUS_MENU_ROWS, STATUS_MENU_ROWS, TEXT_FONT_HEIGHT, true, true, "Stats"};
  ++mem;
  m_selection->set_position(TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * 12);
  m_selection->set_spacing_x(SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2 - TEXTBOX_PADDING_LONG * 2);

  m_hp = new Progress_Bar{"Progress Bar Background", "Progress Bar Green", section_width - STATUS_PROGRESS_BAR_PADDING};
  m_mp = new Progress_Bar{"Progress Bar Background", "Progress Bar Blue", section_width - STATUS_PROGRESS_BAR_PADDING};
  m_exp = new Progress_Bar{"Progress Bar Background", "Progress Bar Pink", section_width - STATUS_PROGRESS_BAR_PADDING};
  m_soul_break = new Progress_Bar{"Progress Bar Background", "Progress Bar Red", section_width - STATUS_PROGRESS_BAR_PADDING};
  m_scroll = new Progress_Bar{"Progress Bar Background", "Progress Bar Orange", section_width - STATUS_PROGRESS_BAR_PADDING};
  ++mem;
  ++mem;
  ++mem;
  ++mem;
  ++mem;

  m_equipment_panel = new Panel;
  ++mem;
  m_equipment_panel->set_position(TEXTBOX_PADDING_SCREEN, TEXTBOX_PADDING_SCREEN_Y, section_width, TEXTBOX_PADDING_SHORT * 2 + TEXT_FONT_HEIGHT * 9);

  vector<Equipment*> weapons{world->get_weapons(world)};
  vector<Equipment*> shields{world->get_shields(world)};
  vector<Equipment*> helms{world->get_helms(world)};
  vector<Equipment*> armor{world->get_armor(world)};
  vector<Equipment*> accessories{world->get_accessories(world)};

  m_weapons = new Selection{weapons, NUM_EQUIPMENT_MENU_COLUMNS, MAX_NUM_EQUIPMENT_MENU_ROWS, NUM_EQUIPMENT_MENU_ROWS, TEXT_FONT_HEIGHT, false, false, "Weapons"};
  m_weapons->set_position(TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT);
  m_weapons->set_spacing_x(section_width);
  m_shields = new Selection{shields, NUM_EQUIPMENT_MENU_COLUMNS, MAX_NUM_EQUIPMENT_MENU_ROWS, NUM_EQUIPMENT_MENU_ROWS, TEXT_FONT_HEIGHT, false, false, "Shields"};
  m_shields->set_position(TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT);
  m_shields->set_spacing_x(section_width);
  m_helms = new Selection{helms, NUM_EQUIPMENT_MENU_COLUMNS, MAX_NUM_EQUIPMENT_MENU_ROWS, NUM_EQUIPMENT_MENU_ROWS, TEXT_FONT_HEIGHT, false, false, "Helms"};
  m_helms->set_position(TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT);
  m_helms->set_spacing_x(section_width);
  m_armor = new Selection{armor, NUM_EQUIPMENT_MENU_COLUMNS, MAX_NUM_EQUIPMENT_MENU_ROWS, NUM_EQUIPMENT_MENU_ROWS, TEXT_FONT_HEIGHT, false, false, "Armor"};
  m_armor->set_position(TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT);
  m_armor->set_spacing_x(section_width);
  m_accessories = new Selection{accessories, NUM_EQUIPMENT_MENU_COLUMNS, MAX_NUM_EQUIPMENT_MENU_ROWS, NUM_EQUIPMENT_MENU_ROWS, TEXT_FONT_HEIGHT, false, false, "Accessories"};
  m_accessories->set_position(TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT);
  m_accessories->set_spacing_x(section_width);
  ++mem;
  ++mem;
  ++mem;
  ++mem;
  ++mem;
}

State_Machine::Status_Menu::~Status_Menu()
{
  delete m_panel;
  m_panel = nullptr;
  --mem;
  delete m_equipment_panel;
  m_equipment_panel = nullptr;
  --mem;
  delete m_selection;
  m_selection = nullptr;
  --mem;
  delete m_weapons;
  m_weapons = nullptr;
  --mem;
  delete m_shields;
  m_shields = nullptr;
  --mem;
  delete m_helms;
  m_helms = nullptr;
  --mem;
  delete m_armor;
  m_armor = nullptr;
  --mem;
  delete m_accessories;
  m_accessories = nullptr;
  --mem;
  delete m_hp;
  delete m_mp;
  delete m_exp;
  delete m_soul_break;
  delete m_scroll;
  m_hp = nullptr;
  m_mp = nullptr;
  m_exp = nullptr;
  m_soul_break = nullptr;
  m_scroll = nullptr;
  --mem;
  --mem;
  --mem;
  --mem;
  --mem;
}

void State_Machine::Status_Menu::update_input(State_Machine* machine, World* world)
{
  if(IsKeyPressed(KEY_X) == true && m_selection->cursor_shown() == true)
  {
    world->play_global_sound("Back");
    machine->set_next_state(State_Machine::FRONT_MENU_STATE);
  }
  else if(IsKeyPressed(KEY_W) == true && m_selection->cursor_shown() == true)
  {
    world->play_global_sound("Cursor");
    m_character_name = world->get_next_party_member_name(m_character_name);
  }
  else if(IsKeyPressed(KEY_Q) == true && m_selection->cursor_shown() == true)
  {
    world->play_global_sound("Cursor");
    m_character_name = world->get_previous_party_member_name(m_character_name);
  }

  long highlighted_item{0};

  m_selection->update_input(world);
  m_weapons->update_input(world);
  m_shields->update_input(world);
  m_helms->update_input(world);
  m_armor->update_input(world);
  m_accessories->update_input(world);
  m_equipment_stat_differences.clear();

  if(m_selection->cursor_shown() == true)
  {
    m_weapons->hide_menu();
    m_shields->hide_menu();
    m_helms->hide_menu();
    m_armor->hide_menu();
    m_accessories->hide_menu();
    highlighted_item = m_selection->get_highlighted_item();

    if(IsKeyPressed(KEY_Z) == true)
    {
      if(highlighted_item == 2)
      {
        if(world->has_weapons() == true)
        {
          world->play_global_sound("Confirm");
          m_selection->hide_cursor();
          m_weapons->show_menu();
          m_weapons->show_cursor();
        }
        else
        {
          world->play_global_sound("Buzzer");
        }
      }
      else if(highlighted_item == 5)
      {
        if(world->has_shields() == true)
        {
          world->play_global_sound("Confirm");
          m_selection->hide_cursor();
          m_shields->show_menu();
          m_shields->show_cursor();
        }
        else
        {
          world->play_global_sound("Buzzer");
        }
      }
      else if(highlighted_item == 8)
      {
        if(world->has_helms() == true)
        {
          world->play_global_sound("Confirm");
          m_selection->hide_cursor();
          m_helms->show_menu();
          m_helms->show_cursor();
        }
        else
        {
          world->play_global_sound("Buzzer");
        }
      }
      else if(highlighted_item == 11)
      {
        if(world->has_armor() == true)
        {
          world->play_global_sound("Confirm");
          m_selection->hide_cursor();
          m_armor->show_menu();
          m_armor->show_cursor();
        }
        else
        {
          world->play_global_sound("Buzzer");
        }
      }
      else if(highlighted_item == 14)
      {
        if(world->has_accessories() == true)
        {
          world->play_global_sound("Confirm");
          m_selection->hide_cursor();
          m_accessories->show_menu();
          m_accessories->show_cursor();
          m_slot = 0;
        }
        else
        {
          world->play_global_sound("Buzzer");
        }
      }
      else if(highlighted_item == 17)
      {
        if(world->has_accessories() == true)
        {
          world->play_global_sound("Confirm");
          m_selection->hide_cursor();
          m_accessories->show_menu();
          m_accessories->show_cursor();
          m_slot = 1;
        }
        else
        {
          world->play_global_sound("Buzzer");
        }
      }
      else
      {
        world->play_global_sound("Buzzer");
      }
    }
  }
  else
  {
    if(IsKeyPressed(KEY_X) == true)
    {
      world->play_global_sound("Back");
      m_weapons->hide_menu();
      m_shields->hide_menu();
      m_helms->hide_menu();
      m_armor->hide_menu();
      m_accessories->hide_menu();
      m_selection->show_cursor();
    }
    else if(m_weapons->cursor_shown() == true)
    {
      if(world->can_use_equipment(m_character_name, m_weapons->get_highlighted_item_obj()->get_name(), "Weapon") == true)
      {
        m_equipment_stat_differences = world->build_equipment_stat_differences(world, m_weapons->get_highlighted_item_obj()->get_name(), m_character_name, 0, m_weapons->get_highlighted_item_obj()->get_equipped_by(), 0);
      }
      if(IsKeyPressed(KEY_Z) == true)
      {
        if(world->can_use_equipment(m_character_name, m_weapons->get_highlighted_item_obj()->get_name(), "Weapon") == true)
        {
          world->play_global_sound("Confirm");
          world->equip(world, m_weapons->get_highlighted_item_obj()->get_name(), m_character_name, 0, m_weapons->get_highlighted_item_obj()->get_equipped_by(), 0);
          m_weapons->rebuild_choices(world->get_weapons(world));
        }
        else
        {
          world->play_global_sound("Buzzer");
        }
      }
      if(world->has_weapons() == false)
      {
        m_weapons->hide_menu();
        m_selection->show_cursor();
      }
    }

    else if(m_shields->cursor_shown() == true)
    {
      if(world->can_use_equipment(m_character_name, m_shields->get_highlighted_item_obj()->get_name(), "Shield") == true)
      {
        m_equipment_stat_differences = world->build_equipment_stat_differences(world, m_shields->get_highlighted_item_obj()->get_name(), m_character_name, 0, m_shields->get_highlighted_item_obj()->get_equipped_by(), 0);
      }
      if(IsKeyPressed(KEY_Z) == true)
      {
        if(world->can_use_equipment(m_character_name, m_shields->get_highlighted_item_obj()->get_name(), "Shield") == true)
        {
          world->play_global_sound("Confirm");
          world->equip(world, m_shields->get_highlighted_item_obj()->get_name(), m_character_name, 0, m_shields->get_highlighted_item_obj()->get_equipped_by(), 0);
          m_shields->rebuild_choices(world->get_shields(world));
        }
        else
        {
          world->play_global_sound("Buzzer");
        }
      }
      if(world->has_shields() == false)
      {
        m_shields->hide_menu();
        m_selection->show_cursor();
      }
    }

    else if(m_helms->cursor_shown() == true)
    {
      if(world->can_use_equipment(m_character_name, m_helms->get_highlighted_item_obj()->get_name(), "Helm") == true)
      {
        m_equipment_stat_differences = world->build_equipment_stat_differences(world, m_helms->get_highlighted_item_obj()->get_name(), m_character_name, 0, m_helms->get_highlighted_item_obj()->get_equipped_by(), 0);
      }
      if(IsKeyPressed(KEY_Z) == true)
      {
        if(world->can_use_equipment(m_character_name, m_helms->get_highlighted_item_obj()->get_name(), "Helm") == true)
        {
          world->play_global_sound("Confirm");
          world->equip(world, m_helms->get_highlighted_item_obj()->get_name(), m_character_name, 0, m_helms->get_highlighted_item_obj()->get_equipped_by(), 0);
          m_helms->rebuild_choices(world->get_helms(world));
        }
        else
        {
          world->play_global_sound("Buzzer");
        }
      }
      if(world->has_helms() == false)
      {
        m_helms->hide_menu();
        m_selection->show_cursor();
      }
    }

    else if(m_armor->cursor_shown() == true)
    {
      if(world->can_use_equipment(m_character_name, m_armor->get_highlighted_item_obj()->get_name(), "Armor") == true)
      {
        m_equipment_stat_differences = world->build_equipment_stat_differences(world, m_armor->get_highlighted_item_obj()->get_name(), m_character_name, 0, m_armor->get_highlighted_item_obj()->get_equipped_by(), 0);
      }
      if(IsKeyPressed(KEY_Z) == true)
      {
        if(world->can_use_equipment(m_character_name, m_armor->get_highlighted_item_obj()->get_name(), "Armor") == true)
        {
          world->play_global_sound("Confirm");
          world->equip(world, m_armor->get_highlighted_item_obj()->get_name(), m_character_name, 0, m_armor->get_highlighted_item_obj()->get_equipped_by(), 0);
          m_armor->rebuild_choices(world->get_armor(world));
        }
        else
        {
          world->play_global_sound("Buzzer");
        }
      }
      if(world->has_armor() == false)
      {
        m_armor->hide_menu();
        m_selection->show_cursor();
      }
    }

    else if(m_accessories->cursor_shown() == true)
    {
      if(world->can_use_equipment(m_character_name, m_accessories->get_highlighted_item_obj()->get_name(), "Accessory") == true)
      {
        m_equipment_stat_differences = world->build_equipment_stat_differences(world, m_accessories->get_highlighted_item_obj()->get_name(), m_character_name, m_slot, m_accessories->get_highlighted_item_obj()->get_equipped_by(), m_accessories->get_highlighted_item_obj()->get_slot());
      }
      if(IsKeyPressed(KEY_Z) == true)
      {
        if(world->can_use_equipment(m_character_name, m_accessories->get_highlighted_item_obj()->get_name(), "Accessory") == true)
        {
          world->play_global_sound("Confirm");
          world->equip(world, m_accessories->get_highlighted_item_obj()->get_name(), m_character_name, m_slot, m_accessories->get_highlighted_item_obj()->get_equipped_by(), m_accessories->get_highlighted_item_obj()->get_slot());
          m_accessories->rebuild_choices(world->get_accessories(world));
        }
        else
        {
          world->play_global_sound("Buzzer");
        }
      }
      if(world->has_accessories() == false)
      {
        m_accessories->hide_menu();
        m_selection->show_cursor();
      }
    }
  }

  m_hp->set_value(world->get_party_member_unmodified_stat(m_character_name, "HP"), world->get_party_member_stat(m_character_name, "Max HP"));
  m_mp->set_value(world->get_party_member_unmodified_stat(m_character_name, "MP"), world->get_party_member_stat(m_character_name, "Max MP"));
  m_exp->set_value(world->get_party_member_unmodified_stat(m_character_name, "EXP"), world->get_party_member_unmodified_stat(m_character_name, "Next Level Total EXP"), world->get_party_member_unmodified_stat(m_character_name, "Current Level Starting EXP"));
}

void State_Machine::Status_Menu::render(World* world) const
{
  long section_width{(SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2 - TEXTBOX_PADDING_LONG * 2) / 3};
  m_panel->render(world);
  world->render_party_member_portrait(m_character_name, 1, TEXTBOX_PADDING_LONG + TEXTBOX_PADDING_SCREEN, TEXTBOX_PADDING_SHORT + TEXTBOX_PADDING_SCREEN_Y);
  world->render_text("Text", m_character_name + " Lv. " + to_string(world->get_party_member_unmodified_stat(m_character_name, "Level")), TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG + section_width, TEXTBOX_PADDING_SHORT + TEXTBOX_PADDING_SCREEN_Y);
  world->render_text("Text", world->get_party_member_species(m_character_name), TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG + section_width, TEXTBOX_PADDING_SHORT + TEXTBOX_PADDING_SCREEN_Y + TEXT_FONT_HEIGHT);
  world->render_text("Text", world->get_party_member_class(m_character_name), TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG + section_width, TEXTBOX_PADDING_SHORT + TEXTBOX_PADDING_SCREEN_Y + TEXT_FONT_HEIGHT * 2);
  world->render_text("Text", "HP                " + to_string(world->get_party_member_unmodified_stat(m_character_name, "HP")) + "/" + to_string(world->get_party_member_stat(m_character_name, "Max HP")), TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG + section_width, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * 3 + PLAYER_SUMMARY_PROGRESS_BAR_TEXT_OFFSET);
  world->render_text("Text", "MP                " + to_string(world->get_party_member_unmodified_stat(m_character_name, "MP")) + "/" + to_string(world->get_party_member_stat(m_character_name, "Max MP")), TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG + section_width, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * 4 + PLAYER_SUMMARY_PROGRESS_BAR_TEXT_OFFSET);
  m_hp->render(world, TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG + section_width, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * 4 + PLAYER_SUMMARY_PROGRESS_BAR_BAR_OFFSET);
  m_mp->render(world, TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG + section_width, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * 5 + PLAYER_SUMMARY_PROGRESS_BAR_BAR_OFFSET);
  world->render_text("Text", "Status: Normal", TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG + section_width, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * 5);
  world->render_text("Text", "Scroll", TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG + section_width * 2, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * 4);
  world->render_text("Text", "Total EXP          " + to_string(world->get_party_member_unmodified_stat(m_character_name, "EXP")), TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG + section_width * 2, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT);
  world->render_text("Text", "To Next Level     " + to_string(world->get_party_member_unmodified_stat(m_character_name, "Next Level EXP")), TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG + section_width * 2, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT + PLAYER_SUMMARY_PROGRESS_BAR_TEXT_OFFSET);
  world->render_text("Text", "Soul Break Level  " + to_string(world->get_party_member_soul_break_level(m_character_name)), TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG + section_width * 2, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * 2 + PLAYER_SUMMARY_PROGRESS_BAR_TEXT_OFFSET);
  world->render_text("Text", "AP                   0/10", TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG + section_width * 2, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * 3 + PLAYER_SUMMARY_PROGRESS_BAR_TEXT_OFFSET);
  world->render_text("Text", "Equipment", TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG + section_width * 2, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * 11);
  m_exp->render(world, TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG + section_width * 2, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * 2 + PLAYER_SUMMARY_PROGRESS_BAR_BAR_OFFSET);
  m_soul_break->render(world, TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG + section_width * 2, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * 3 + PLAYER_SUMMARY_PROGRESS_BAR_BAR_OFFSET);
  m_scroll->render(world, TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG + section_width * 2, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * 4 + PLAYER_SUMMARY_PROGRESS_BAR_BAR_OFFSET);
  if(m_selection->cursor_shown() == true)
  {
    world->render_text("Text", STAT_DESCRIPTIONS_LINE_1[m_selection->get_highlighted_item()], TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * 10);
    world->render_text("Text", STAT_DESCRIPTIONS_LINE_2[m_selection->get_highlighted_item()], TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * 11);
    m_selection->render(world, m_character_name);
  }
  else
  {
    m_equipment_panel->render(world);
    if(m_weapons->cursor_shown() == true)
    {
      world->render_text("Text", world->get_item_description(m_weapons->get_highlighted_item_obj()->get_name()), TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * 10);
      m_selection->render(world, m_character_name, m_equipment_stat_differences);
    }
    else if(m_shields->cursor_shown() == true)
    {
      world->render_text("Text", world->get_item_description(m_shields->get_highlighted_item_obj()->get_name()), TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * 10);
      m_selection->render(world, m_character_name, m_equipment_stat_differences);
    }
    else if(m_helms->cursor_shown() == true)
    {
      world->render_text("Text", world->get_item_description(m_helms->get_highlighted_item_obj()->get_name()), TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * 10);
      m_selection->render(world, m_character_name, m_equipment_stat_differences);
    }
    else if(m_armor->cursor_shown() == true)
    {
      world->render_text("Text", world->get_item_description(m_armor->get_highlighted_item_obj()->get_name()), TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * 10);
      m_selection->render(world, m_character_name, m_equipment_stat_differences);
    }
    else if(m_accessories->cursor_shown() == true)
    {
      world->render_text("Text", world->get_item_description(m_accessories->get_highlighted_item_obj()->get_name()), TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * 10);
      m_selection->render(world, m_character_name, m_equipment_stat_differences);
    }
  }
  m_weapons->render(world, m_character_name);
  m_shields->render(world, m_character_name);
  m_helms->render(world, m_character_name);
  m_armor->render(world, m_character_name);
  m_accessories->render(world, m_character_name);
}

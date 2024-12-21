#include "Main.h"
#include "State_Machine.h"

void State_Machine::set_start_state_front_menu(const World* const world)
{
  m_state_ID = FRONT_MENU_STATE;
  m_next_state = NULL_STATE;
  m_current_state = new State_Machine::Front_Menu(world);
  m_current_state_renderer = new State_Machine::Front_Menu_Renderer(static_cast<State_Machine::Front_Menu*>(m_current_state));
  ++mem;
  ++mem;
  g_sound_player->play_global_sound("Confirm");
}

State_Machine::~State_Machine()
{
  delete m_current_state;
  m_current_state = nullptr;
  --mem;
  delete m_current_state_renderer;
  m_current_state_renderer = nullptr;
  --mem;
}

void State_Machine::update()
{
  m_current_state->update();
}

void State_Machine::update_input(State_Machine* machine, World* world)
{
  m_current_state->update_input(machine, world);
}

void State_Machine::render(const World* const world) const
{
  m_current_state_renderer->render(world);
}

void State_Machine::change_state(const World* const world)
{
  //If the state needs to be changed
  if(m_next_state != NULL_STATE)
  {
    //Delete the current state
    delete m_current_state;
    m_current_state = nullptr;
    --mem;
    delete m_current_state_renderer;
    m_current_state_renderer = nullptr;
    --mem;
    //Change the state
    switch(m_next_state)
    {
      case FRONT_MENU_STATE:
        m_current_state = new State_Machine::Front_Menu(world);
        m_current_state_renderer = new State_Machine::Front_Menu_Renderer(static_cast<State_Machine::Front_Menu*>(m_current_state));
        ++mem;
        ++mem;
        break;
      case ITEM_MENU_STATE:
        m_current_state = new State_Machine::Item_Menu(world);
        m_current_state_renderer = new State_Machine::Item_Menu_Renderer(static_cast<State_Machine::Item_Menu*>(m_current_state));
        ++mem;
        ++mem;
        break;
      case STATUS_MENU_STATE:
        m_current_state = new State_Machine::Status_Menu(world, m_selected_party_member);
        m_current_state_renderer = new State_Machine::Status_Menu_Renderer(static_cast<State_Machine::Status_Menu*>(m_current_state));
        ++mem;
        ++mem;
        break;
      default:
        break;
    }
        
    //Change the current state ID
    m_state_ID = m_next_state;
        
    //NULL the next state ID
    m_next_state = NULL_STATE;
    m_selected_party_member = "NULL";
  }
  return;
}

void State_Machine::set_next_state(const state_list & new_state, const string & selected_party_member)
{
  //Set the next state
  m_next_state = new_state;

  if(selected_party_member != "NULL")
  {
    m_selected_party_member = selected_party_member;
  }
}

bool State_Machine::check_exit() const
{
  return m_state_ID == FRONT_MENU_STATE && m_current_state != nullptr && m_current_state->root_menu_cursor_shown() == true;
}

bool State_Machine::Machine_State::root_menu_cursor_shown() const
{
  return false;
}

State_Machine::Front_Menu::Front_Menu(const World* const world)
{
  vector<Player_Summary*> party_info{};
  for(long i{0}; i < world->get_party_size(); ++i)
  {
    party_info.push_back(new Player_Summary{TEXTBOX_PADDING_SCREEN + (SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2) / FRONT_MENU_SPLIT, TEXTBOX_PADDING_SCREEN_Y + PLAYER_SUMMARY_SECTION_PADDING + i * (TEXT_FONT_HEIGHT * 4 + PLAYER_SUMMARY_SECTION_PADDING), world->get_party_member_info(world->get_party_member_name(i)), world->get_party_member_name(i), world->get_party_member_row(world->get_party_member_name(i)), world->get_party_member_species(world->get_party_member_name(i)), world->get_party_member_class(world->get_party_member_name(i)), world->get_party_member_unmodified_stat(world->get_party_member_name(i), "Level"), world->get_party_member_unmodified_stat(world->get_party_member_name(i), "HP"), world->get_party_member_stat(world->get_party_member_name(i), "Max HP"), world->get_party_member_unmodified_stat(world->get_party_member_name(i), "MP"), world->get_party_member_stat(world->get_party_member_name(i), "Max MP"), world->get_party_member_unmodified_stat(world->get_party_member_name(i), "EXP"), world->get_party_member_unmodified_stat(world->get_party_member_name(i), "Next Level EXP")});
    ++mem;
  }
  m_party_info.add(party_info);

  m_selection = new Selection{NUM_FRONT_MENU_CHOICES, 1, NUM_FRONT_MENU_CHOICES, NUM_FRONT_MENU_CHOICES};
  ++mem;
  m_party_menu = new Selection{world->get_party_size(), 1, MAX_PARTY_SIZE, world->get_party_size(), false};
  ++mem;
}

State_Machine::Front_Menu::~Front_Menu()
{
  delete m_selection;
  delete m_party_menu;
  m_selection = nullptr;
  m_party_menu = nullptr;
  --mem;
  --mem;
}

State_Machine::Front_Menu_Renderer::~Front_Menu_Renderer()
{
  delete m_gold;
  delete m_map;
  delete m_party_panel;
  delete m_menu;
  delete m_selection_renderer;
  delete m_party_menu_renderer;
  delete m_formation;
  --mem;
  --mem;
  --mem;
  --mem;
  --mem;
  --mem;
  --mem;
}

const Selection* State_Machine::Front_Menu::get_selection() const
{
  return m_selection;
}

const Selection* State_Machine::Front_Menu::get_party_menu() const
{
  return m_party_menu;
}

void State_Machine::Front_Menu::update_input(State_Machine* machine, World* world)
{
  m_selection->update_input(world, TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG, TEXTBOX_PADDING_SHORT + TEXTBOX_PADDING_SCREEN_Y, (SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2) / FRONT_MENU_SPLIT);
  m_party_menu->update_input(world, TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG + (SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2) / FRONT_MENU_SPLIT, TEXTBOX_PADDING_SHORT + TEXTBOX_PADDING_SCREEN_Y + PLAYER_SUMMARY_SECTION_PADDING, (SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2) - (SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2) / FRONT_MENU_SPLIT, TEXT_FONT_HEIGHT * 4 + PLAYER_SUMMARY_SECTION_PADDING);
  for(long i{0}; i < m_party_info.get_list_size(); ++i)
  {
    m_party_info[i]->update_tweens();
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
        g_sound_player->play_global_sound("Confirm");
        machine->set_next_state(State_Machine::ITEM_MENU_STATE);
      }
      else if(highlighted_index == 1)
      {
        g_sound_player->play_global_sound("Buzzer");
        m_option_selected = FRONT_MENU_CHOICES[1];
      }
      else if(highlighted_index == 2)
      {
        g_sound_player->play_global_sound("Confirm");
        m_selection->hide_cursor();
        m_party_menu->show_cursor();
        m_option_selected = FRONT_MENU_CHOICES[2];
      }
      else if(highlighted_index == 3)
      {
        g_sound_player->play_global_sound("Confirm");
        m_selection->hide_cursor();
        m_party_menu->show_cursor();
        m_option_selected = FRONT_MENU_CHOICES[3];
      }
      else if(highlighted_index == 4)
      {
        g_sound_player->play_global_sound("Buzzer");
      }
      else
      {
        crash("Error: Tried to select invalid option " + to_string(highlighted_index) + " in the front menu.");
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
        g_sound_player->play_global_sound("Confirm");
        machine->set_next_state(State_Machine::STATUS_MENU_STATE, highlighted_item);
      }
    }
    else if(m_option_selected == FRONT_MENU_CHOICES[3])
    {
      if(IsKeyPressed(KEY_LEFT) == true)
      {
        if(world->set_party_member_front_row(highlighted_item) == true)
        {
          m_party_info[highlighted_item]->set_member_front_row();
          g_sound_player->play_global_sound("Cursor");
          m_party_info[highlighted_item]->set_portrait_tween(true);
         }
      }
      if(IsKeyPressed(KEY_RIGHT) == true)
      {
        if(world->set_party_member_back_row(highlighted_item) == true)
        {
          m_party_info[highlighted_item]->set_member_back_row();
          g_sound_player->play_global_sound("Cursor");
          m_party_info[highlighted_item]->set_portrait_tween(false);
        }
      }
      if(IsKeyPressed(KEY_Z) == true)
      {
        g_sound_player->play_global_sound("Confirm");
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
        }
      }
    }

    if(IsKeyPressed(KEY_X) == true)
    {
      g_sound_player->play_global_sound("Back");
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

bool State_Machine::Front_Menu::root_menu_cursor_shown() const
{
  return m_selection->cursor_shown();
}

string State_Machine::Front_Menu::get_option_selected() const
{
  return m_option_selected;
}

void State_Machine::Front_Menu::render_party_info(const World* const world) const
{
  for(long i{0}; i < m_party_info.get_list_size(); ++i)
  {
    m_party_info[i]->render(world);
  }
}

string State_Machine::Front_Menu_Renderer::split_map_name_text(const bool & line_number) const
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

void State_Machine::Front_Menu_Renderer::render(const World* const world) const
{
  m_gold->render(world);
  m_map->render(world);
  m_party_panel->render(world);
  m_menu->render(world);
  m_selection_renderer->render(FRONT_MENU_CHOICES, world);


  string map_first_line{split_map_name_text(0)};
  string map_second_line{split_map_name_text(1)};
  world->render_text("Text", map_first_line, TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG, SCREEN_HEIGHT - (4 * TEXT_FONT_HEIGHT + TEXTBOX_PADDING_SHORT * 3) - TEXTBOX_PADDING_SCREEN_Y);
  world->render_text("Text", map_second_line, TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG, SCREEN_HEIGHT - (3 * TEXT_FONT_HEIGHT + TEXTBOX_PADDING_SHORT * 3) - TEXTBOX_PADDING_SCREEN_Y);
  world->render_text("Text", to_string(world->get_money()) + " Bits", TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG, SCREEN_HEIGHT - (2 * TEXT_FONT_HEIGHT + TEXTBOX_PADDING_SHORT) - TEXTBOX_PADDING_SCREEN_Y);
  world->render_text("Text", "Play Time: " + get_play_time(world->get_play_time_ticks()), TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG, SCREEN_HEIGHT - (TEXT_FONT_HEIGHT + TEXTBOX_PADDING_SHORT) - TEXTBOX_PADDING_SCREEN_Y);
  if(m_front_menu->get_option_selected() == FRONT_MENU_CHOICES[3])
  {
    m_formation->render(world);
    for(long i{0}; i < static_cast<long>(FORMATION_MENU_TEXT.size()); ++i)
    {
      world->render_text("Text", FORMATION_MENU_TEXT[i], TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * i);
    }
  }
  m_front_menu->render_party_info(world);
}

string State_Machine::Front_Menu_Renderer::get_play_time(const double & play_time_ticks) const
{
  string hours{to_string(static_cast<long>(play_time_ticks) / 3600)};
  long minutes{static_cast<long>(play_time_ticks) / 60 % 60};
  string min_str;
  (minutes < 10) ? (min_str = "0" + to_string(minutes)) : (min_str = to_string(minutes));
  long seconds{static_cast<long>(play_time_ticks) % 60};
  string sec_str;
  (seconds < 10) ? (sec_str = "0" + to_string(seconds)) : (sec_str = to_string(seconds));
  return hours + ":" + min_str + ":" + sec_str;
}

State_Machine::Item_Menu::~Item_Menu()
{
  delete m_category;
  delete m_items_menu;
  delete m_key_items_menu;
  --mem;
  --mem;
  --mem;
}

State_Machine::Item_Menu_Renderer::~Item_Menu_Renderer()
{
  delete m_switch;
  delete m_item_text;
  delete m_description;
  delete m_item_list;
  delete m_category_renderer;
  delete m_items_renderer;
  delete m_key_items_renderer;
  --mem;
  --mem;
  --mem;
  --mem;
  --mem;
  --mem;
  --mem;
}

const Selection* State_Machine::Item_Menu::get_category_menu() const
{
  return m_category;
}

const Selection* State_Machine::Item_Menu::get_item_menu() const
{
  return m_items_menu;
}

const Selection* State_Machine::Item_Menu::get_key_item_menu() const
{
  return m_key_items_menu;
}

void State_Machine::Item_Menu::update_input(State_Machine* machine, World* world)
{
  if(IsKeyPressed(KEY_X) == true && m_category->cursor_shown() == true)
  {
    g_sound_player->play_global_sound("Back");
    machine->set_next_state(State_Machine::FRONT_MENU_STATE);
  }

  long highlighted_item{0};

  m_category->update_input(world, TEXTBOX_PADDING_SCREEN + (SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2) / ITEM_MENU_SPLIT + TEXTBOX_PADDING_LONG, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT, SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2 - TEXTBOX_PADDING_LONG * 2 - ((SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2) / ITEM_MENU_SPLIT));
  m_items_menu->update_input(world, TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG, TEXTBOX_PADDING_SCREEN_Y + TEXT_FONT_HEIGHT * 2 + TEXTBOX_PADDING_SHORT * 5, SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2 - TEXTBOX_PADDING_LONG * 2);
  m_key_items_menu->update_input(world, TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG, TEXTBOX_PADDING_SCREEN_Y + TEXT_FONT_HEIGHT * 2 + TEXTBOX_PADDING_SHORT * 5, SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2 - TEXTBOX_PADDING_LONG * 2);

  if(m_category->cursor_shown() == true)
  {
    highlighted_item = m_category->get_highlighted_item();
    if(highlighted_item == 0)
    {
      m_key_items_menu->hide_menu();
      m_items_menu->show_menu();
    }
    else if(highlighted_item == 1)
    {
      m_items_menu->hide_menu();
      m_key_items_menu->show_menu();
    }
    else
    {
      crash("Error: Tried to highlight invalid option " + to_string(highlighted_item) + " in the item category menu.");
    }

    if(IsKeyPressed(KEY_Z) == true)
    {
      if(highlighted_item == 0)
      {
        if(world->has_items() == true)
        {
          g_sound_player->play_global_sound("Confirm");
          m_category->hide_cursor();
          m_items_menu->show_cursor();
        }
        else
        {
          g_sound_player->play_global_sound("Buzzer");
        }
      }
      else if(highlighted_item == 1)
      {
        if(world->has_key_items() == true)
        {
          g_sound_player->play_global_sound("Confirm");
          m_category->hide_cursor();
          m_key_items_menu->show_cursor();
        }
        else
        {
          g_sound_player->play_global_sound("Buzzer");
        }
      }
      else
      {
        crash("Error: Tried to select invalid option " + to_string(highlighted_item) + " in the item category menu.");
      }
    }
  }
  else if(m_items_menu->cursor_shown() == true || m_key_items_menu->cursor_shown() == true)
  {
    if(IsKeyPressed(KEY_X) == true)
    {
      g_sound_player->play_global_sound("Back");
      m_items_menu->hide_cursor();
      m_key_items_menu->hide_cursor();
      m_category->show_cursor();
    }
    else if(m_items_menu->cursor_shown() == true)
    {
      if(IsKeyPressed(KEY_Z) == true)
      {
        g_sound_player->play_global_sound("Confirm");
        world->remove_item(world->get_item_name(m_items_menu->get_highlighted_item()));
        m_items_menu->change_number_of_choices(world->get_number_of_items());
        m_items_menu->update_input(world, TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG, TEXTBOX_PADDING_SCREEN_Y + TEXT_FONT_HEIGHT * 2 + TEXTBOX_PADDING_SHORT * 5, SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2 - TEXTBOX_PADDING_LONG * 2);
      }
      if(world->has_items() == false)
      {
        m_items_menu->hide_cursor();
        m_key_items_menu->hide_cursor();
        m_category->show_cursor();
      }
    }
    else if(m_key_items_menu->cursor_shown() == true)
    {
      if(IsKeyPressed(KEY_Z) == true)
      {
        g_sound_player->play_global_sound("Buzzer");
      }
    }
  }
}

void State_Machine::Item_Menu_Renderer::render(const World* const world) const
{
  m_switch->render(world);
  m_item_text->render(world);
  m_description->render(world);
  m_item_list->render(world);
  m_category_renderer->render(ITEM_MENU_CHOICES, world);
  m_items_renderer->render_items(world->get_inventory_item_names(), world, world->get_inventory_item_descriptions(), world->get_inventory_item_quantities());
  m_key_items_renderer->render_key_items(world->get_inventory_key_item_names(), world, world->get_inventory_key_item_descriptions());
  world->render_text("Text", m_top_bar_text, TEXTBOX_PADDING_SCREEN + (SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2) / ITEM_MENU_SPLIT / 2 - get_text_font_word_width(m_top_bar_text) / 2, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT);
}

State_Machine::Status_Menu::~Status_Menu()
{
  delete m_selection_menu;
  m_selection_menu = nullptr;
  --mem;
  delete m_weapons_menu;
  m_weapons_menu = nullptr;
  --mem;
  delete m_shields_menu;
  m_shields_menu = nullptr;
  --mem;
  delete m_helms_menu;
  m_helms_menu = nullptr;
  --mem;
  delete m_armor_menu;
  m_armor_menu = nullptr;
  --mem;
  delete m_accessories_menu;
  m_accessories_menu = nullptr;
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


State_Machine::Status_Menu_Renderer::~Status_Menu_Renderer()
{
  delete m_panel;
  --mem;
  delete m_equipment_panel;
  --mem;
  delete m_selection_renderer;
  --mem;
  delete m_weapons_renderer;
  --mem;
  delete m_shields_renderer;
  --mem;
  delete m_helms_renderer;
  --mem;
  delete m_armor_renderer;
  --mem;
  delete m_accessories_renderer;
  --mem;
}

const Selection* State_Machine::Status_Menu::get_selection_menu() const
{
  return m_selection_menu;
}

const Selection* State_Machine::Status_Menu::get_weapons_menu() const
{
  return m_weapons_menu;
}

const Selection* State_Machine::Status_Menu::get_shields_menu() const
{
  return m_shields_menu;
}

const Selection* State_Machine::Status_Menu::get_helms_menu() const
{
  return m_helms_menu;
}

const Selection* State_Machine::Status_Menu::get_armor_menu() const
{
  return m_armor_menu;
}

const Selection* State_Machine::Status_Menu::get_accessories_menu() const
{
  return m_accessories_menu;
}

void State_Machine::Status_Menu::render_hp_bar(const World* const world, const long & x, const long & y) const
{
 m_hp->render(world, x, y);
}

void State_Machine::Status_Menu::render_mp_bar(const World* const world, const long & x, const long & y) const
{
 m_mp->render(world, x, y);
}

void State_Machine::Status_Menu::render_exp_bar(const World* const world, const long & x, const long & y) const
{
 m_exp->render(world, x, y);
}

void State_Machine::Status_Menu::render_soul_bar(const World* const world, const long & x, const long & y) const
{
 m_soul_break->render(world, x, y);
}

void State_Machine::Status_Menu::render_scroll_bar(const World* const world, const long & x, const long & y) const
{
 m_scroll->render(world, x, y);
}

void State_Machine::Status_Menu::update_input(State_Machine* machine, World* world)
{
  if(IsKeyPressed(KEY_X) == true && m_selection_menu->cursor_shown() == true)
  {
    g_sound_player->play_global_sound("Back");
    machine->set_next_state(State_Machine::FRONT_MENU_STATE);
  }
  else if(IsKeyPressed(KEY_W) == true && m_selection_menu->cursor_shown() == true)
  {
    g_sound_player->play_global_sound("Cursor");
    m_character = world->get_next_party_member(m_character);
  }
  else if(IsKeyPressed(KEY_Q) == true && m_selection_menu->cursor_shown() == true)
  {
    g_sound_player->play_global_sound("Cursor");
    m_character = world->get_previous_party_member(m_character);
  }

  long highlighted_item{0};

  m_selection_menu->update_input(world, TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * 12, SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2 - TEXTBOX_PADDING_LONG * 2);
  m_weapons_menu->update_input(world, TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT, (SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2 - TEXTBOX_PADDING_LONG * 2) / 3);
  m_shields_menu->update_input(world, TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT, (SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2 - TEXTBOX_PADDING_LONG * 2) / 3);
  m_helms_menu->update_input(world, TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT, (SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2 - TEXTBOX_PADDING_LONG * 2) / 3);
  m_armor_menu->update_input(world, TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT, (SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2 - TEXTBOX_PADDING_LONG * 2) / 3);
  m_accessories_menu->update_input(world, TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT, (SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2 - TEXTBOX_PADDING_LONG * 2) / 3);

  if(m_selection_menu->cursor_shown() == true)
  {
    m_weapons_menu->hide_menu();
    m_shields_menu->hide_menu();
    m_helms_menu->hide_menu();
    m_armor_menu->hide_menu();
    m_accessories_menu->hide_menu();
    highlighted_item = m_selection_menu->get_highlighted_item();

    if(IsKeyPressed(KEY_Z) == true)
    {
      if(highlighted_item == 2)
      {
        if(world->get_number_of_equipped_and_inventory_weapons() != 0)
        {
          g_sound_player->play_global_sound("Confirm");
          m_selection_menu->hide_cursor();
          m_weapons_menu->show_menu();
          m_weapons_menu->show_cursor();
        }
        else
        {
          g_sound_player->play_global_sound("Buzzer");
        }
      }
      else if(highlighted_item == 5)
      {
        if(world->get_number_of_equipped_and_inventory_shields() != 0)
        {
          g_sound_player->play_global_sound("Confirm");
          m_selection_menu->hide_cursor();
          m_shields_menu->show_menu();
          m_shields_menu->show_cursor();
        }
        else
        {
          g_sound_player->play_global_sound("Buzzer");
        }
      }
      else if(highlighted_item == 8)
      {
        if(world->get_number_of_equipped_and_inventory_helms() != 0)
        {
          g_sound_player->play_global_sound("Confirm");
          m_selection_menu->hide_cursor();
          m_helms_menu->show_menu();
          m_helms_menu->show_cursor();
        }
        else
        {
          g_sound_player->play_global_sound("Buzzer");
        }
      }
      else if(highlighted_item == 11)
      {
        if(world->get_number_of_equipped_and_inventory_armor() != 0)
        {
          g_sound_player->play_global_sound("Confirm");
          m_selection_menu->hide_cursor();
          m_armor_menu->show_menu();
          m_armor_menu->show_cursor();
        }
        else
        {
          g_sound_player->play_global_sound("Buzzer");
        }
      }
      else if(highlighted_item == 14)
      {
        if(world->get_number_of_equipped_and_inventory_accessories() != 0)
        {
          g_sound_player->play_global_sound("Confirm");
          m_selection_menu->hide_cursor();
          m_accessories_menu->show_menu();
          m_accessories_menu->show_cursor();
          m_slot = 0;
        }
        else
        {
          g_sound_player->play_global_sound("Buzzer");
        }
      }
      else if(highlighted_item == 17)
      {
        if(world->get_number_of_equipped_and_inventory_accessories() != 0)
        {
          g_sound_player->play_global_sound("Confirm");
          m_selection_menu->hide_cursor();
          m_accessories_menu->show_menu();
          m_accessories_menu->show_cursor();
          m_slot = 1;
        }
        else
        {
          g_sound_player->play_global_sound("Buzzer");
        }
      }
      else
      {
        g_sound_player->play_global_sound("Buzzer");
      }
    }
  }
  else
  {
    if(IsKeyPressed(KEY_X) == true)
    {
      g_sound_player->play_global_sound("Back");
      m_weapons_menu->hide_menu();
      m_shields_menu->hide_menu();
      m_helms_menu->hide_menu();
      m_armor_menu->hide_menu();
      m_accessories_menu->hide_menu();
      m_selection_menu->show_cursor();
    }

    else if(m_weapons_menu->cursor_shown() == true)
    {
      if(IsKeyPressed(KEY_Z) == true)
      {
        vector<string> weapon_names{world->get_equipped_and_inventory_weapon_names()};
        vector<string> weapon_equip_bys{world->get_equipped_and_inventory_weapon_equipped_bys()};
        if(world->can_use_equipment(m_character, weapon_names[m_weapons_menu->get_highlighted_item()]) == true)
        {
          g_sound_player->play_global_sound("Confirm");
          world->equip(world, m_character, weapon_names[m_weapons_menu->get_highlighted_item()], "Weapon", 0, weapon_equip_bys[m_weapons_menu->get_highlighted_item()]);
          m_weapons_menu->change_number_of_choices(world->get_number_of_equipped_and_inventory_weapons());
          m_weapons_menu->update_input(world, TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT, (SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2 - TEXTBOX_PADDING_LONG * 2) / 3);
        }
        else
        {
          g_sound_player->play_global_sound("Buzzer");
        }
      }
      if(world->get_number_of_equipped_and_inventory_weapons() == 0)
      {
        m_weapons_menu->hide_menu();
        m_selection_menu->show_cursor();
      }
    }

    else if(m_shields_menu->cursor_shown() == true)
    {
      if(IsKeyPressed(KEY_Z) == true)
      {
        vector<string> shield_names{world->get_equipped_and_inventory_shield_names()};
        vector<string> shield_equip_bys{world->get_equipped_and_inventory_shield_equipped_bys()};
        if(world->can_use_equipment(m_character, shield_names[m_shields_menu->get_highlighted_item()]) == true)
        {
          g_sound_player->play_global_sound("Confirm");
          world->equip(world, m_character, shield_names[m_shields_menu->get_highlighted_item()], "Shield", 0, shield_equip_bys[m_shields_menu->get_highlighted_item()]);
          m_shields_menu->change_number_of_choices(world->get_number_of_equipped_and_inventory_shields());
          m_shields_menu->update_input(world, TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT, (SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2 - TEXTBOX_PADDING_LONG * 2) / 3);
        }
        else
        {
          g_sound_player->play_global_sound("Buzzer");
        }
      }
      if(world->get_number_of_equipped_and_inventory_shields() == 0)
      {
        m_shields_menu->hide_menu();
        m_selection_menu->show_cursor();
      }
    }

    else if(m_helms_menu->cursor_shown() == true)
    {
      if(IsKeyPressed(KEY_Z) == true)
      {
        vector<string> helm_names{world->get_equipped_and_inventory_helm_names()};
        vector<string> helm_equip_bys{world->get_equipped_and_inventory_helm_equipped_bys()};
        if(world->can_use_equipment(m_character, helm_names[m_helms_menu->get_highlighted_item()]) == true)
        {
          g_sound_player->play_global_sound("Confirm");
          world->equip(world, m_character, helm_names[m_helms_menu->get_highlighted_item()], "Helm", 0, helm_equip_bys[m_helms_menu->get_highlighted_item()]);
          m_helms_menu->change_number_of_choices(world->get_number_of_equipped_and_inventory_helms());
          m_helms_menu->update_input(world, TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT, (SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2 - TEXTBOX_PADDING_LONG * 2) / 3);
        }
        else
        {
          g_sound_player->play_global_sound("Buzzer");
        }
      }
      if(world->get_number_of_equipped_and_inventory_helms() == 0)
      {
        m_helms_menu->hide_menu();
        m_selection_menu->show_cursor();
      }
    }

    else if(m_armor_menu->cursor_shown() == true)
    {
      if(IsKeyPressed(KEY_Z) == true)
      {
        vector<string> armor_names{world->get_equipped_and_inventory_armor_names()};
        vector<string> armor_equip_bys{world->get_equipped_and_inventory_armor_equipped_bys()};
        if(world->can_use_equipment(m_character, armor_names[m_armor_menu->get_highlighted_item()]) == true)
        {
          g_sound_player->play_global_sound("Confirm");
          world->equip(world, m_character, armor_names[m_armor_menu->get_highlighted_item()], "Armor", 0, armor_equip_bys[m_armor_menu->get_highlighted_item()]);
          m_armor_menu->change_number_of_choices(world->get_number_of_equipped_and_inventory_armor());
          m_armor_menu->update_input(world, TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT, (SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2 - TEXTBOX_PADDING_LONG * 2) / 3);
        }
        else
        {
          g_sound_player->play_global_sound("Buzzer");
        }
      }
      if(world->get_number_of_equipped_and_inventory_armor() == 0)
      {
        m_armor_menu->hide_menu();
        m_selection_menu->show_cursor();
      }
    }

    else if(m_accessories_menu->cursor_shown() == true)
    {
      if(IsKeyPressed(KEY_Z) == true)
      {
        vector<string> accessory_names{world->get_equipped_and_inventory_accessory_names()};
        vector<string> accessory_equip_bys{world->get_equipped_and_inventory_accessory_equipped_bys()};
        vector<long> accessory_slots{world->get_equipped_and_inventory_accessory_slots()};
        if(world->can_use_equipment(m_character, accessory_names[m_accessories_menu->get_highlighted_item()]) == true)
        {
          g_sound_player->play_global_sound("Confirm");
          world->equip(world, m_character, accessory_names[m_accessories_menu->get_highlighted_item()], "Accessory", m_slot, accessory_equip_bys[m_accessories_menu->get_highlighted_item()], accessory_slots[m_accessories_menu->get_highlighted_item()]);
          m_accessories_menu->change_number_of_choices(world->get_number_of_equipped_and_inventory_accessories());
          m_accessories_menu->update_input(world, TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT, (SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2 - TEXTBOX_PADDING_LONG * 2) / 3);
        }
        else
        {
          g_sound_player->play_global_sound("Buzzer");
        }
      }
      if(world->get_number_of_equipped_and_inventory_accessories() == 0)
      {
        m_accessories_menu->hide_menu();
        m_selection_menu->show_cursor();
      }
    }
  }
  m_hp->set_value(world->get_party_member_unmodified_stat(m_character, "HP"), world->get_party_member_stat(m_character, "Max HP"));
  m_mp->set_value(world->get_party_member_unmodified_stat(m_character, "MP"), world->get_party_member_stat(m_character, "Max MP"));
  m_exp->set_value(world->get_party_member_unmodified_stat(m_character, "EXP"), world->get_party_member_unmodified_stat(m_character, "Next Level Total EXP"), world->get_party_member_unmodified_stat(m_character, "Current Level Starting EXP"));
}

void State_Machine::Status_Menu_Renderer::render(const World* const world) const
{
  long section_width{(SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2 - TEXTBOX_PADDING_LONG * 2) / 3};
  m_panel->render(world);
  world->render_party_member_portrait(m_status_menu->get_character(), TEXTBOX_PADDING_LONG + TEXTBOX_PADDING_SCREEN, TEXTBOX_PADDING_SHORT + TEXTBOX_PADDING_SCREEN_Y);
  world->render_text("Text", m_status_menu->get_character() + " Lv. " + to_string(world->get_party_member_unmodified_stat(m_status_menu->get_character(), "Level")), TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG + section_width, TEXTBOX_PADDING_SHORT + TEXTBOX_PADDING_SCREEN_Y);
  world->render_text("Text", world->get_party_member_species(m_status_menu->get_character()), TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG + section_width, TEXTBOX_PADDING_SHORT + TEXTBOX_PADDING_SCREEN_Y + TEXT_FONT_HEIGHT);
  world->render_text("Text", world->get_party_member_class(m_status_menu->get_character()), TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG + section_width, TEXTBOX_PADDING_SHORT + TEXTBOX_PADDING_SCREEN_Y + TEXT_FONT_HEIGHT * 2);
  m_status_menu->render_hp_bar(world, TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG + section_width, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * 4 + PLAYER_SUMMARY_PROGRESS_BAR_BAR_OFFSET);
  m_status_menu->render_mp_bar(world, TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG + section_width, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * 5 + PLAYER_SUMMARY_PROGRESS_BAR_BAR_OFFSET);
  world->render_text("Text", "Status: Normal", TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG + section_width, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * 5);
  world->render_text("Text", "Scroll", TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG + section_width * 2, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * 4);
  world->render_text("Text", "Total EXP          " + to_string(world->get_party_member_unmodified_stat(m_status_menu->get_character(), "EXP")), TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG + section_width * 2, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT);
  world->render_text("Text", "To Next Level     " + to_string(world->get_party_member_unmodified_stat(m_status_menu->get_character(), "Next Level EXP")), TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG + section_width * 2, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT + PLAYER_SUMMARY_PROGRESS_BAR_TEXT_OFFSET);
  world->render_text("Text", "Soul Break Level  " + to_string(1), TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG + section_width * 2, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * 2 + PLAYER_SUMMARY_PROGRESS_BAR_TEXT_OFFSET);
  world->render_text("Text", "AP                   0/10", TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG + section_width * 2, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * 3 + PLAYER_SUMMARY_PROGRESS_BAR_TEXT_OFFSET);
  world->render_text("Text", "Equipment", TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG + section_width * 2, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * 11);
  m_status_menu->render_exp_bar(world, TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG + section_width * 2, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * 2 + PLAYER_SUMMARY_PROGRESS_BAR_BAR_OFFSET);
  m_status_menu->render_soul_bar(world, TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG + section_width * 2, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * 3 + PLAYER_SUMMARY_PROGRESS_BAR_BAR_OFFSET);
  m_status_menu->render_scroll_bar(world, TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG + section_width * 2, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * 4 + PLAYER_SUMMARY_PROGRESS_BAR_BAR_OFFSET);

  if(m_status_menu->get_selection_menu()->cursor_shown() == true)
  {
    world->render_text("Text", STAT_DESCRIPTIONS_LINE_1[m_status_menu->get_selection_menu()->get_highlighted_item()], TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * 10);
    world->render_text("Text", STAT_DESCRIPTIONS_LINE_2[m_status_menu->get_selection_menu()->get_highlighted_item()], TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * 11);
  }
  else
  {
    m_equipment_panel->render(world);
  }

  vector<string> weapon_names{world->get_equipped_and_inventory_weapon_names()};
  vector<string> weapon_descriptions{world->get_equipped_and_inventory_weapon_descriptions()};
  vector<long> weapon_quantities{world->get_equipped_and_inventory_weapon_quantities()};
  vector<string> weapon_equipped_bys{world->get_equipped_and_inventory_weapon_equipped_bys()};
  vector<long> weapon_icons{world->get_equipped_and_inventory_weapon_icons()};
  vector<bool> weapon_usable_bys{world->get_equipped_and_inventory_weapon_usable_bys(m_status_menu->get_character())};

  vector<string> shield_names{world->get_equipped_and_inventory_shield_names()};
  vector<string> shield_descriptions{world->get_equipped_and_inventory_shield_descriptions()};
  vector<long> shield_quantities{world->get_equipped_and_inventory_shield_quantities()};
  vector<string> shield_equipped_bys{world->get_equipped_and_inventory_shield_equipped_bys()};
  vector<long> shield_icons{world->get_equipped_and_inventory_shield_icons()};
  vector<bool> shield_usable_bys{world->get_equipped_and_inventory_shield_usable_bys(m_status_menu->get_character())};

  vector<string> helm_names{world->get_equipped_and_inventory_helm_names()};
  vector<string> helm_descriptions{world->get_equipped_and_inventory_helm_descriptions()};
  vector<long> helm_quantities{world->get_equipped_and_inventory_helm_quantities()};
  vector<string> helm_equipped_bys{world->get_equipped_and_inventory_helm_equipped_bys()};
  vector<long> helm_icons{world->get_equipped_and_inventory_helm_icons()};
  vector<bool> helm_usable_bys{world->get_equipped_and_inventory_helm_usable_bys(m_status_menu->get_character())};

  vector<string> armor_names{world->get_equipped_and_inventory_armor_names()};
  vector<string> armor_descriptions{world->get_equipped_and_inventory_armor_descriptions()};
  vector<long> armor_quantities{world->get_equipped_and_inventory_armor_quantities()};
  vector<string> armor_equipped_bys{world->get_equipped_and_inventory_armor_equipped_bys()};
  vector<long> armor_icons{world->get_equipped_and_inventory_armor_icons()};
  vector<bool> armor_usable_bys{world->get_equipped_and_inventory_armor_usable_bys(m_status_menu->get_character())};

  vector<string> accessory_names{world->get_equipped_and_inventory_accessory_names()};
  vector<string> accessory_descriptions{world->get_equipped_and_inventory_accessory_descriptions()};
  vector<long> accessory_quantities{world->get_equipped_and_inventory_accessory_quantities()};
  vector<string> accessory_equipped_bys{world->get_equipped_and_inventory_accessory_equipped_bys()};
  vector<long> accessory_icons{world->get_equipped_and_inventory_accessory_icons()};
  vector<bool> accessory_usable_bys{world->get_equipped_and_inventory_accessory_usable_bys(m_status_menu->get_character())};
  vector<long> accessory_slots{world->get_equipped_and_inventory_accessory_slots()};

  vector<long> stat_predictions;
  if(m_status_menu->get_weapons_menu()->menu_shown() == true)
  {
    stat_predictions = world->predict_stats(world, m_status_menu->get_character(), weapon_names[m_status_menu->get_weapons_menu()->get_highlighted_item()], "Weapon", weapon_equipped_bys[m_status_menu->get_weapons_menu()->get_highlighted_item()] == m_status_menu->get_character());
  }
  if(m_status_menu->get_shields_menu()->menu_shown() == true)
  {
    stat_predictions = world->predict_stats(world, m_status_menu->get_character(), shield_names[m_status_menu->get_shields_menu()->get_highlighted_item()], "Shield", shield_equipped_bys[m_status_menu->get_shields_menu()->get_highlighted_item()] == m_status_menu->get_character());
  }
  if(m_status_menu->get_helms_menu()->menu_shown() == true)
  {
    stat_predictions = world->predict_stats(world, m_status_menu->get_character(), helm_names[m_status_menu->get_helms_menu()->get_highlighted_item()], "Helm", helm_equipped_bys[m_status_menu->get_helms_menu()->get_highlighted_item()] == m_status_menu->get_character());
  }
  if(m_status_menu->get_armor_menu()->menu_shown() == true)
  {
    stat_predictions = world->predict_stats(world, m_status_menu->get_character(), armor_names[m_status_menu->get_armor_menu()->get_highlighted_item()], "Armor", armor_equipped_bys[m_status_menu->get_armor_menu()->get_highlighted_item()] == m_status_menu->get_character());
  }
  if(m_status_menu->get_accessories_menu()->menu_shown() == true)
  {
    stat_predictions = world->predict_stats(world, m_status_menu->get_character(), accessory_names[m_status_menu->get_accessories_menu()->get_highlighted_item()], "Accessory", accessory_equipped_bys[m_status_menu->get_accessories_menu()->get_highlighted_item()] == m_status_menu->get_character() && m_status_menu->get_slot() == accessory_slots[m_status_menu->get_accessories_menu()->get_highlighted_item()], m_status_menu->get_slot(), accessory_slots[m_status_menu->get_accessories_menu()->get_highlighted_item()], accessory_equipped_bys[m_status_menu->get_accessories_menu()->get_highlighted_item()]);
  }

  long max_hp_difference = stat_predictions.empty() == true ? 0 : stat_predictions[12];
  long max_mp_difference = stat_predictions.empty() == true ? 0 : stat_predictions[13];
  string hp_difference{max_hp_difference != 0 ? (max_hp_difference > 0 ? "+" + to_string(max_hp_difference) : to_string(max_hp_difference)) : " "};
  string mp_difference{max_mp_difference != 0 ? (max_mp_difference > 0 ? "+" + to_string(max_mp_difference) : to_string(max_mp_difference)) : " "};
  string hp_font{max_hp_difference != 0 ? (max_hp_difference > 0 ? "Green" : "Red") : "Text"};
  string mp_font{max_mp_difference != 0 ? (max_mp_difference > 0 ? "Green" : "Red") : "Text"};
  world->render_text(hp_font, "HP                " + to_string(world->get_party_member_unmodified_stat(m_status_menu->get_character(), "HP")) + "/" + to_string(world->get_party_member_stat(m_status_menu->get_character(), "Max HP")) + " " + hp_difference, TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG + section_width, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * 3 + PLAYER_SUMMARY_PROGRESS_BAR_TEXT_OFFSET);
  world->render_text(mp_font, "MP                " + to_string(world->get_party_member_unmodified_stat(m_status_menu->get_character(), "MP")) + "/" + to_string(world->get_party_member_stat(m_status_menu->get_character(), "Max MP")) + " " + mp_difference, TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG + section_width, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * 4 + PLAYER_SUMMARY_PROGRESS_BAR_TEXT_OFFSET);

  m_weapons_renderer->render_equipment(weapon_names, world, m_status_menu->get_character(), "weapon", 0, weapon_descriptions, weapon_quantities, weapon_equipped_bys, weapon_icons, weapon_usable_bys);
  m_shields_renderer->render_equipment(shield_names, world, m_status_menu->get_character(), "shield", 0, shield_descriptions, shield_quantities, shield_equipped_bys, shield_icons, shield_usable_bys);
  m_helms_renderer->render_equipment(helm_names, world, m_status_menu->get_character(), "helmet", 0, helm_descriptions, helm_quantities, helm_equipped_bys, helm_icons, helm_usable_bys);
  m_armor_renderer->render_equipment(armor_names, world, m_status_menu->get_character(), "armor", 0, armor_descriptions, armor_quantities, armor_equipped_bys, armor_icons, armor_usable_bys);
  m_accessories_renderer->render_equipment(accessory_names, world, m_status_menu->get_character(), "accessory", m_status_menu->get_slot(), accessory_descriptions, accessory_quantities, accessory_equipped_bys, accessory_icons, accessory_usable_bys, accessory_slots);
  m_selection_renderer->render_status_menu(STAT_STRINGS, world,
                                           world->get_party_member_stat(m_status_menu->get_character(), "Strength"), world->get_party_member_unmodified_stat(m_status_menu->get_character(), "Strength"), stat_predictions.empty() == true ? 0 : stat_predictions[0],
                                           world->get_party_member_stat(m_status_menu->get_character(), "Attack"), world->get_party_member_unmodified_stat(m_status_menu->get_character(), "Attack"), stat_predictions.empty() == true ? 0 : stat_predictions[1],
                                           world->get_party_member_stat(m_status_menu->get_character(), "Speed"), world->get_party_member_unmodified_stat(m_status_menu->get_character(), "Speed"), stat_predictions.empty() == true ? 0 : stat_predictions[2],
                                           world->get_party_member_stat(m_status_menu->get_character(), "Defense"), world->get_party_member_unmodified_stat(m_status_menu->get_character(), "Defense"), stat_predictions.empty() == true ? 0 : stat_predictions[3],
                                           world->get_party_member_stat(m_status_menu->get_character(), "Intellect"), world->get_party_member_unmodified_stat(m_status_menu->get_character(), "Intellect"), stat_predictions.empty() == true ? 0 : stat_predictions[4],
                                           world->get_party_member_stat(m_status_menu->get_character(), "Resistance"), world->get_party_member_unmodified_stat(m_status_menu->get_character(), "Resistance"), stat_predictions.empty() == true ? 0 : stat_predictions[5],
                                           world->get_party_member_stat(m_status_menu->get_character(), "Stamina"), world->get_party_member_unmodified_stat(m_status_menu->get_character(), "Stamina"), stat_predictions.empty() == true ? 0 : stat_predictions[6],
                                           world->get_party_member_stat(m_status_menu->get_character(), "Accuracy"), world->get_party_member_unmodified_stat(m_status_menu->get_character(), "Accuracy"), stat_predictions.empty() == true ? 0 : stat_predictions[7],
                                           world->get_party_member_stat(m_status_menu->get_character(), "Spirit"), world->get_party_member_unmodified_stat(m_status_menu->get_character(), "Spirit"), stat_predictions.empty() == true ? 0 : stat_predictions[8],
                                           world->get_party_member_stat(m_status_menu->get_character(), "Critical"), world->get_party_member_unmodified_stat(m_status_menu->get_character(), "Critical"), stat_predictions.empty() == true ? 0 : stat_predictions[9],
                                           world->get_party_member_stat(m_status_menu->get_character(), "Evasion"), world->get_party_member_unmodified_stat(m_status_menu->get_character(), "Evasion"), stat_predictions.empty() == true ? 0 : stat_predictions[10],
                                           world->get_party_member_stat(m_status_menu->get_character(), "Magic Evasion"), world->get_party_member_unmodified_stat(m_status_menu->get_character(), "Magic Evasion"), stat_predictions.empty() == true ? 0 : stat_predictions[11],
                                           world->get_party_member_equipped_weapon_name(m_status_menu->get_character()), world->get_item_icon(world->get_party_member_equipped_weapon_name(m_status_menu->get_character())),
                                           world->get_party_member_equipped_shield_name(m_status_menu->get_character()), world->get_item_icon(world->get_party_member_equipped_shield_name(m_status_menu->get_character())),
                                           world->get_party_member_equipped_helm_name(m_status_menu->get_character()), world->get_item_icon(world->get_party_member_equipped_helm_name(m_status_menu->get_character())),
                                           world->get_party_member_equipped_armor_name(m_status_menu->get_character()), world->get_item_icon(world->get_party_member_equipped_armor_name(m_status_menu->get_character())),
                                           world->get_party_member_equipped_accessory_one_name(m_status_menu->get_character()), world->get_item_icon(world->get_party_member_equipped_accessory_one_name(m_status_menu->get_character())),
                                           world->get_party_member_equipped_accessory_two_name(m_status_menu->get_character()), world->get_item_icon(world->get_party_member_equipped_accessory_two_name(m_status_menu->get_character())));
}

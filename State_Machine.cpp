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
        current_state = new State_Machine::Item_Menu();
        ++mem;
        break;
      case STATUS_MENU_STATE:
        current_state = new State_Machine::Status_Menu(m_selected_party_member_name);
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
  Image image{LoadImageFromMemory(".png", binary_Image_simple_panel_png_start, reinterpret_cast<long>(&binary_Image_simple_panel_png_size))};
  m_panel_texture = LoadTextureFromImage(image);
  UnloadImage(image);
  
  for(long i{0}; i < world->get_party_size(); ++i)
  {
    m_party_info.push_back(new Player_Summary{TEXTBOX_PADDING_SCREEN + (SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2) / FRONT_MENU_SPLIT, TEXTBOX_PADDING_SCREEN_Y + PLAYER_SUMMARY_SECTION_PADDING + i * (TEXT_FONT_HEIGHT * 4 + PLAYER_SUMMARY_SECTION_PADDING), world->get_party_member_name(i), world->get_party_member_row(world->get_party_member_name(i))});
    ++mem;
  }

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
  m_selection = new Selection{to_pointers(FRONT_MENU_CHOICES), 1, NUM_FRONT_MENU_CHOICES, NUM_FRONT_MENU_CHOICES, TEXT_FONT_HEIGHT};
  ++mem;
  m_party_menu = new Selection{m_party_info, 1, world->get_party_size(), world->get_party_size(), TEXT_FONT_HEIGHT * 4 + PLAYER_SUMMARY_SECTION_PADDING, false};
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
  UnloadTexture(m_panel_texture);
  --mem;
  --mem;
  --mem;
  --mem;
  --mem;
  --mem;
  --mem;
  
  for(long i{0}; i < static_cast<long>(m_party_info.size()); ++i)
  {
    delete m_party_info[i];
    m_party_info[i] = nullptr;
    --mem;
  }
}

void State_Machine::Front_Menu::update_input(State_Machine* machine, World* world)
{
  m_selection->update_input(world);
  m_party_menu->update_input(world);
  for(long i{0}; i < static_cast<long>(m_party_info.size()); ++i)
  {
    m_party_info[i]->update_tweens(world);
  }
  
  long selected_item{-1};
  long highlighted_item{-1};

  if(m_selection->cursor_shown() == true)
  {
    selected_item = m_selection->get_selected_item();
    highlighted_item = m_selection->get_highlighted_item();
    switch(highlighted_item)
    {
      default:
        break;
    }
    switch(selected_item)
    {
      case -1:
        break;
      case 0:
        world->play_global_sound("Confirm");
        machine->set_next_state(State_Machine::ITEM_MENU_STATE);
        break;
      case 1:
        world->play_global_sound("Buzzer");
        m_option_selected = 1;
        break;
      case 2:
        world->play_global_sound("Confirm");
        m_selection->hide_cursor();
        m_party_menu->show_cursor();
        m_option_selected = 2;
        break;
      case 3:
        world->play_global_sound("Confirm");
        m_selection->hide_cursor();
        m_party_menu->show_cursor();
        m_option_selected = 3;
        break;
      case 4:
        world->play_global_sound("Buzzer");
        break;
      default:
        crash("Error: Tried to select invalid option " + to_string(selected_item) + " in selection menu \"" + m_selection->c_get_options() + "\".");
        break;
    }
  }
  if(m_party_menu->cursor_shown() == true)
  {
    long switch_on{-1};
    if(m_option_selected == 3)
    {
      for(long i{0}; i < static_cast<long>(m_party_info.size()); ++i)
      {
        if(m_party_info[i]->get_switch() == true)
        {
          switch_on = i;
        }
      }
    }

    if(IsKeyPressed(KEY_X) == true)
    {
      world->play_global_sound("Back");
      m_party_menu->hide_cursor();
      m_selection->show_cursor();
      m_option_selected = -1;
      if(switch_on != -1)
      {
        m_party_info[switch_on]->toggle_switch_rect();
      }
    }
    selected_item = m_party_menu->get_selected_item();
    highlighted_item = m_party_menu->get_highlighted_item();

    switch(m_option_selected)
    {
      case -1:
      case 0:
        break;
      case 1:
        break;
      case 2:
        if(IsKeyPressed(KEY_Z) == true)
        {
          world->play_global_sound("Confirm");
          machine->set_next_state(State_Machine::STATUS_MENU_STATE, world->get_party_member_name(highlighted_item));
        }
        break;
      case 3:
        if(IsKeyPressed(KEY_LEFT) == true)
        {
          if(world->set_party_member_front_row(world->get_party_member_name(highlighted_item)) == true)
          {
            world->play_global_sound("Cursor");
            m_party_info[highlighted_item]->set_portrait_tween(true);
          }
        }
        if(IsKeyPressed(KEY_RIGHT) == true)
        {
          if(world->set_party_member_back_row(world->get_party_member_name(highlighted_item)) == true)
          {
            world->play_global_sound("Cursor");
            m_party_info[highlighted_item]->set_portrait_tween(false);
          }
        }
        if(IsKeyPressed(KEY_Z) == true)
        {
          world->play_global_sound("Confirm");
          if(highlighted_item == switch_on || switch_on == -1)
          {
            m_party_info[highlighted_item]->toggle_switch_rect();
          }
          else if(switch_on != -1)
          {
            m_party_info[switch_on]->toggle_switch_rect();
            world->swap_party_members(world->get_party_member_name(highlighted_item), world->get_party_member_name(switch_on));
            m_party_info[highlighted_item]->set_y_tween(switch_on, highlighted_item, 0);
            m_party_info[switch_on]->set_y_tween(highlighted_item, switch_on, 0);
            Player_Summary* temp{m_party_info[highlighted_item]};
            m_party_info[highlighted_item] = m_party_info[switch_on];
            m_party_info[switch_on] = temp;
          }
        }
        break;
      case 4:
        break;
      default:
        crash("Error: Tried to select invalid option " + to_string(m_option_selected) + " in the party menu.");
        break;
    }
  }
}

void State_Machine::Front_Menu::render(World* world) const
{
  m_gold->render(m_panel_texture);
  m_map->render(m_panel_texture);
  m_party->render(m_panel_texture);
  m_menu->render(m_panel_texture);
  m_selection->render(world);
  m_party_menu->render(world);
  string map_first_line{split_map_name_text(0)};
  string map_second_line{split_map_name_text(1)};
  world->render_text(0, map_first_line, TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG, SCREEN_HEIGHT - (4 * world->get_font_height(0) + TEXTBOX_PADDING_SHORT * 3) - TEXTBOX_PADDING_SCREEN_Y);
  world->render_text(0, map_second_line, TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG, SCREEN_HEIGHT - (3 * world->get_font_height(0) + TEXTBOX_PADDING_SHORT * 3) - TEXTBOX_PADDING_SCREEN_Y);
  world->render_text(0, to_string(world->get_money()) + " Bits", TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG, SCREEN_HEIGHT - (2 * world->get_font_height(0) + TEXTBOX_PADDING_SHORT) - TEXTBOX_PADDING_SCREEN_Y);
  world->render_text(0, "Play Time: " + world->get_time(), TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG, SCREEN_HEIGHT - (world->get_font_height(0) + TEXTBOX_PADDING_SHORT) - TEXTBOX_PADDING_SCREEN_Y);
  if(m_option_selected == 3)
  {
    m_formation->render(m_panel_texture);
    for(long i{0}; i < static_cast<long>(FORMATION_MENU_TEXT.size()); ++i)
    {
      world->render_text(0, FORMATION_MENU_TEXT[i], TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT + world->get_font_height(0) * i);
    }
  }
  for(long i{0}; i < static_cast<long>(m_party_info.size()); ++i)
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

State_Machine::Item_Menu::Item_Menu()
{
  Image image{LoadImageFromMemory(".png", binary_Image_simple_panel_png_start, reinterpret_cast<long>(&binary_Image_simple_panel_png_size))};
  m_panel_texture = LoadTextureFromImage(image);
  UnloadImage(image);
  
  Image image2{LoadImageFromMemory(".png", binary_Image_continue_arrow_png_start, reinterpret_cast<long>(&binary_Image_continue_arrow_png_size))};
  m_arrow_texture = LoadTextureFromImage(image2);
  UnloadImage(image2);

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
  m_items = new Selection{to_pointers(ITEM_MENU_CHOICES), NUM_ITEM_MENU_COLUMNS, ITEM_MENU_ROWS, ITEM_MENU_ROWS, TEXT_FONT_HEIGHT, false, true, "Items"};
  m_items->set_position(TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG, TEXTBOX_PADDING_SCREEN_Y + TEXT_FONT_HEIGHT * 2 + TEXTBOX_PADDING_SHORT * 5);
  m_items->set_spacing_x(SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2 - TEXTBOX_PADDING_LONG * 2);
  m_key_items = new Selection{to_pointers(ITEM_MENU_CHOICES), NUM_ITEM_MENU_COLUMNS, ITEM_MENU_ROWS, ITEM_MENU_ROWS, TEXT_FONT_HEIGHT, false, false, "Key Items"};
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
  UnloadTexture(m_panel_texture);
  UnloadTexture(m_arrow_texture);
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
  long selected_item{-1};
  long highlighted_item{-1};

  m_category->update_input(world);
  m_items->update_input(world);
  m_key_items->update_input(world);

  if(m_category->cursor_shown() == true)
  {
    selected_item = m_category->get_selected_item();
    highlighted_item = m_category->get_highlighted_item();
    switch(highlighted_item)
    {
      case 0:
        m_key_items->hide_menu();
        m_items->show_menu();
        break;
      case 1:
        m_items->hide_menu();
        m_key_items->show_menu();
        break;
      default:
        break;
    }
    switch(selected_item)
    {
      case -1:
        break;
      case 0:
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
        break;
      case 1:
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
        break;
      default:
        crash("Error: Tried to select invalid option " + to_string(selected_item) + " in selection menu \"" + m_category->c_get_options() + "\".");
        break;
    }
  }
  if(m_items->cursor_shown() == true || m_key_items->cursor_shown() == true)
  {
    if(IsKeyPressed(KEY_X) == true)
    {
      world->play_global_sound("Back");
      m_items->hide_cursor();
      m_key_items->hide_cursor();
      m_category->show_cursor();
    }
  }
  if(m_items->cursor_shown() == true)
  {
    if(IsKeyPressed(KEY_Z) == true)
    {
      world->play_global_sound("Confirm");
    }
    selected_item = m_items->get_selected_item();
    world->remove_item(selected_item);
    if(world->has_items() == false)
    {
      m_items->hide_cursor();
      m_key_items->hide_cursor();
      m_category->show_cursor();
    }
  }
  if(m_key_items->cursor_shown() == true)
  {
    if(IsKeyPressed(KEY_Z) == true)
    {
      world->play_global_sound("Buzzer");
    }
    m_key_items->update_input(world);
  }
}

void State_Machine::Item_Menu::render(World* world) const
{
  m_switch->render(m_panel_texture);
  m_item_text->render(m_panel_texture);
  m_description->render(m_panel_texture);
  m_item_list->render(m_panel_texture);
  m_category->render(world);
  m_items->render(world);
  m_key_items->render(world);
  world->render_text(0, m_top_bar_text, TEXTBOX_PADDING_SCREEN + (SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2) / ITEM_MENU_SPLIT / 2 - world->get_word_width(0, m_top_bar_text) / 2, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT);
  if(m_items->cursor_shown() == true)
  {
    world->render_text(0, world->get_item(m_items->get_highlighted_item()).get_item().get_description(), TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT * 3 + world->get_font_height(0));
  }
  if(m_key_items->cursor_shown() == true)
  {
    world->render_text(0, world->get_key_item(m_key_items->get_highlighted_item()).get_description(), TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT * 3 + world->get_font_height(0));
  }
}

State_Machine::Status_Menu::Status_Menu(const string & character_name)
{
  long section_width{(SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2 - TEXTBOX_PADDING_LONG * 2) / 3};
  Image image{LoadImageFromMemory(".png", binary_Image_simple_panel_png_start, reinterpret_cast<long>(&binary_Image_simple_panel_png_size))};
  m_panel_texture = LoadTextureFromImage(image);
  UnloadImage(image);
  
  m_character_name = character_name;
  m_panel = new Panel;
  ++mem;
  m_panel->set_position(TEXTBOX_PADDING_SCREEN, TEXTBOX_PADDING_SCREEN_Y, SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2, SCREEN_HEIGHT - TEXTBOX_PADDING_SCREEN_Y * 2);
  m_selection = new Selection{to_pointers(ITEM_MENU_CHOICES), NUM_STATUS_MENU_COLUMNS, STATUS_MENU_ROWS, STATUS_MENU_ROWS, TEXT_FONT_HEIGHT, true, true, "Stats"};
  ++mem;
  m_selection->set_position(TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * 12);
  m_selection->set_spacing_x(SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2 - TEXTBOX_PADDING_LONG * 2);

  m_hp = new Progress_Bar{HP_PROGRESS, section_width - STATUS_PROGRESS_BAR_PADDING};
  m_mp = new Progress_Bar{MP_PROGRESS, section_width - STATUS_PROGRESS_BAR_PADDING};
  m_exp = new Progress_Bar{EXP_PROGRESS, section_width - STATUS_PROGRESS_BAR_PADDING};
  m_soul_break = new Progress_Bar{SOUL_BREAK_PROGRESS, section_width - STATUS_PROGRESS_BAR_PADDING};
  m_scroll = new Progress_Bar{SCROLL_PROGRESS, section_width - STATUS_PROGRESS_BAR_PADDING};
  ++mem;
  ++mem;
  ++mem;
  ++mem;
  ++mem;
}

State_Machine::Status_Menu::~Status_Menu()
{
  UnloadTexture(m_panel_texture);
  delete m_panel;
  m_panel = nullptr;
  --mem;
  delete m_selection;
  m_selection = nullptr;
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
  if(IsKeyPressed(KEY_X) == true/* && m_category->cursor_shown() == true*/)
  {
    world->play_global_sound("Back");
    machine->set_next_state(State_Machine::FRONT_MENU_STATE);
  }
  if(IsKeyPressed(KEY_Z) == true)
  {
    world->play_global_sound("Buzzer");
  }
  m_hp->set_value(world->get_party_member_unmodified_stat(m_character_name, "HP"), world->get_party_member_stat(m_character_name, "Max HP"));
  m_mp->set_value(world->get_party_member_unmodified_stat(m_character_name, "MP"), world->get_party_member_stat(m_character_name, "Max MP"));
  m_exp->set_value(world->get_party_member_unmodified_stat(m_character_name, "EXP"), world->get_party_member_unmodified_stat(m_character_name, "Next Level Total EXP"), world->get_party_member_unmodified_stat(m_character_name, "Current Level Starting EXP"));
  m_selection->update_input(world);
}

void State_Machine::Status_Menu::render(World* world) const
{
  long section_width{(SCREEN_WIDTH - TEXTBOX_PADDING_SCREEN * 2 - TEXTBOX_PADDING_LONG * 2) / 3};
  m_panel->render(m_panel_texture);
  m_selection->render(world, m_character_name);
  world->render_party_member_portrait(m_character_name, 1, TEXTBOX_PADDING_LONG + TEXTBOX_PADDING_SCREEN, TEXTBOX_PADDING_SHORT + TEXTBOX_PADDING_SCREEN_Y);
  world->render_text(0, m_character_name + " Lv. " + to_string(world->get_party_member_unmodified_stat(m_character_name, "Level")), TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG + section_width, TEXTBOX_PADDING_SHORT + TEXTBOX_PADDING_SCREEN_Y);
  world->render_text(0, world->get_party_member_species(m_character_name), TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG + section_width, TEXTBOX_PADDING_SHORT + TEXTBOX_PADDING_SCREEN_Y + TEXT_FONT_HEIGHT);
  world->render_text(0, world->get_party_member_class(m_character_name), TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG + section_width, TEXTBOX_PADDING_SHORT + TEXTBOX_PADDING_SCREEN_Y + TEXT_FONT_HEIGHT * 2);
  world->render_text(0, "HP                " + to_string(world->get_party_member_unmodified_stat(m_character_name, "HP")) + "/" + to_string(world->get_party_member_stat(m_character_name, "Max HP")), TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG + section_width, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * 3 + PLAYER_SUMMARY_PROGRESS_BAR_TEXT_OFFSET);
  world->render_text(0, "MP                " + to_string(world->get_party_member_unmodified_stat(m_character_name, "MP")) + "/" + to_string(world->get_party_member_stat(m_character_name, "Max MP")), TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG + section_width, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * 4 + PLAYER_SUMMARY_PROGRESS_BAR_TEXT_OFFSET);
  m_hp->render(TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG + section_width, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * 4 + PLAYER_SUMMARY_PROGRESS_BAR_BAR_OFFSET);
  m_mp->render(TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG + section_width, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * 5 + PLAYER_SUMMARY_PROGRESS_BAR_BAR_OFFSET);
  world->render_text(0, "Status: Normal", TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG + section_width, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * 5);
  world->render_text(0, "Scroll", TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG + section_width * 2, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * 4);
  world->render_text(0, "Total EXP          " + to_string(world->get_party_member_unmodified_stat(m_character_name, "EXP")), TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG + section_width * 2, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT);
  world->render_text(0, "To Next Level     " + to_string(world->get_party_member_unmodified_stat(m_character_name, "Next Level EXP")), TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG + section_width * 2, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT + PLAYER_SUMMARY_PROGRESS_BAR_TEXT_OFFSET);
  world->render_text(0, "Soul Break Level  " + to_string(world->get_party_member_soul_break_level(m_character_name)), TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG + section_width * 2, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * 2 + PLAYER_SUMMARY_PROGRESS_BAR_TEXT_OFFSET);
  world->render_text(0, "AP                   0/10", TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG + section_width * 2, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * 3 + PLAYER_SUMMARY_PROGRESS_BAR_TEXT_OFFSET);
  world->render_text(0, "Equipment", TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG + section_width * 2, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * 11);
  m_exp->render(TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG + section_width * 2, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * 2 + PLAYER_SUMMARY_PROGRESS_BAR_BAR_OFFSET);
  m_soul_break->render(TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG + section_width * 2, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * 3 + PLAYER_SUMMARY_PROGRESS_BAR_BAR_OFFSET);
  m_scroll->render(TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG + section_width * 2, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * 4 + PLAYER_SUMMARY_PROGRESS_BAR_BAR_OFFSET);
  world->render_text(0, STAT_DESCRIPTIONS_LINE_1[m_selection->get_highlighted_item()], TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * 10);
  world->render_text(0, STAT_DESCRIPTIONS_LINE_2[m_selection->get_highlighted_item()], TEXTBOX_PADDING_SCREEN + TEXTBOX_PADDING_LONG, TEXTBOX_PADDING_SCREEN_Y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * 11);
}
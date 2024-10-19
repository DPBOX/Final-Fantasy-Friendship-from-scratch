#include "Main.h"
#include "UI.h"
#include "Selection.hpp"

Fnt::Fnt(const Font_Params & font_to_load)
{
  m_name = font_to_load.m_name;
  m_cell_width = font_to_load.m_cell_width;
  m_char_widths = font_to_load.m_char_widths;
  Image image{LoadImageFromMemory(".png", font_to_load.m_data, font_to_load.m_size)};
  m_font_img = LoadTextureFromImage(image);
  UnloadImage(image);
}

Fnt::~Fnt()
{
  UnloadTexture(m_font_img);
}

string Fnt::get_name() const
{
  return m_name;
}

long Fnt::get_height() const
{
  return m_font_img.height;
}

long Fnt::get_cell_width() const
{
  return m_cell_width;
}

long Fnt::get_char_width(const long & index) const
{
  return m_char_widths[index];
}

long Fnt::get_word_width(string word) const
{
  long current_pos{0};

  while(word != "")
  {
    current_pos += get_char_width(word[0]);
    word.erase(word.begin());
  }
  return current_pos;
}

void Fnt::render_text(string text, const long & x_pos, const long & y_pos, const long & alpha) const
{
  long current_pos{x_pos};

  while(text != "")
  {
    render_letter(current_pos, y_pos, text[0], alpha);
    current_pos += m_char_widths[text[0]];
    text.erase(text.begin());
  }
}

void Fnt::render_text_center(string text, const long & y_pos, const long & alpha) const
{
  render_text(text, SCREEN_WIDTH / 2 - get_word_width(text) / 2, y_pos, alpha);
}

void Fnt::render_letter(const long & x, const long & y, const char & id, const long & alpha) const
{
  DrawTexturePro(m_font_img, Rectangle{static_cast<float>(m_cell_width * id), 0, static_cast<float>(m_cell_width), static_cast<float>(m_font_img.height)}, Rectangle{static_cast<float>(x), static_cast<float>(y), static_cast<float>(m_cell_width), static_cast<float>(m_font_img.height)}, Vector2{0, 0}, 0, Color{0xFF, 0xFF, 0xFF, static_cast<unsigned char>(alpha)});
}

void Progress_Bar::set_value(const long & value, const long & maximum, const long & minimum)
{
  m_value = static_cast<double>(value - minimum) / (maximum - minimum) * MAX_PROGRESS_BAR_VALUE;
}

void Progress_Bar::render(World* world, const long & x, const long & y) const
{
  for(long i{0}; i < m_length; ++i)
  {
    world->render_progress_bar(m_background_image_name, x + i, y);
  }

  if(m_value > 0)
  {
    if(m_value >= MAX_PROGRESS_BAR_VALUE)
    {
      for(long i{0}; i < m_length; ++i)
      {
        world->render_progress_bar(m_bar_image_name, x + i, y);
      }
    }
    else
    {
      long value{static_cast<long>(m_length * m_value / MAX_PROGRESS_BAR_VALUE + .5)};

      if(value <= 0)
      {
        world->render_progress_bar(m_bar_image_name, x, y);
      }
      else if(value >= m_length)
      {
        for(long i{0}; i < m_length - 1; ++i)
        {
          world->render_progress_bar(m_bar_image_name, x + i, y);
        }
      }
      else
      {
        for(long i{0}; i < value; ++i)
        {
          world->render_progress_bar(m_bar_image_name, x + i, y);
        }
      }
    }
  }
}

void Textbox::add_text(const string & text)
{
  m_text = text;
}

void Textbox::add_title(const string & title)
{
  m_title_text = title;
}

void Textbox::add_portrait(const Image_Params & image)
{
  Image the_image{LoadImageFromMemory(".png", image.m_data, image.m_size)};
  m_portrait_img = LoadTextureFromImage(the_image);
  UnloadImage(the_image);
}

void Textbox::add_selection_menu(Selection<string>* s)
{
  m_selection = s;  
}

void Textbox::create_fitted(const long & size_x, const long & size_y, World* world)
{
  create_fixed(size_x, size_y, world->get_word_width("Text", m_text) + TEXTBOX_PADDING_LONG * 2, world->get_font_height("Text") + TEXTBOX_PADDING_SHORT * 2, world);
}

void Textbox::create_fitted_choices(const long & size_x, const long & size_y, const vector<string> & choices, World* world)
{
  Selection<string>* s{new Selection{to_pointers(choices), static_cast<long>(choices.size()), 1, 1, 0}};
  ++mem;
  add_selection_menu(s);
  create_fixed(size_x, size_y, world->get_word_width("Text", m_text) + TEXTBOX_PADDING_LONG * 2, world->get_font_height("Text") * 2 + TEXTBOX_PADDING_SHORT * 2, world);
}

void Textbox::create_fixed(const long & size_x, const long & size_y, const long & size_width, const long & size_height, World* world)
{
  m_size_x = size_x;
  m_size_y = size_y;
  m_size_w = size_width;
  m_size_h = size_height;
  m_text_area_x = m_size_x + TEXTBOX_PADDING_LONG;
  m_text_area_y = m_size_y + TEXTBOX_PADDING_SHORT;
  m_text_area_w = m_size_w - TEXTBOX_PADDING_LONG * 2;
  m_text_area_h = m_size_h - TEXTBOX_PADDING_SHORT * 2;
  long temp_x{m_text_area_x};
  long temp_y{m_text_area_y};
  m_panel = new Panel;
  ++mem;
  m_center_x = m_size_x + m_size_w / 2;
  m_center_y = m_size_y + m_size_h / 2;
  m_start_x = m_size_x + m_size_w / 2 - 4.5;
  m_start_y = m_size_y + m_size_h / 2 - 4.5;
  m_start_w = 9;
  m_start_h = 9;
  m_x_speed = (m_size_w / 2 - 4.5) / PANEL_SPEED;
  m_y_speed = (m_size_h / 2 - 4.5) / PANEL_SPEED;
  m_continue_arrow_animation = Blinking_Animation(false, false, CONTINUE_ARROW_INTERVAL);

  if(m_title_text != "")
  {
    m_title_x = temp_x;
    m_title_y = temp_y;
    m_text_area_y += TEXT_FONT_HEIGHT;
    m_text_area_h -= TEXT_FONT_HEIGHT;
  }
  
  if(m_portrait_img.id != 0)
  {
    m_portrait_x = temp_x;
    m_portrait_y = temp_y;
    m_text_area_x += m_portrait_img.width + TEXTBOX_PADDING_SHORT;
    m_text_area_w -= m_portrait_img.width + TEXTBOX_PADDING_SHORT;
    m_title_x += m_portrait_img.width + TEXTBOX_PADDING_SHORT;
  }
  
  if(m_selection != nullptr)
  {
    long selection_y_pos{m_text_area_y + m_text_area_h - m_selection->get_height()};
    m_text_area_h -= m_selection->get_height();
    m_selection->set_position(m_text_area_x, selection_y_pos);
    m_selection->set_spacing_x(m_text_area_w);
  }
  
  break_text(m_text, world, "Text");
  
  if(m_text_chunks.size() >= 2)
  {
    m_continue_arrow_animation.set_loop(true);
  }
}

Textbox::~Textbox()
{
  if(m_panel != nullptr)
  {
    delete m_panel;
    m_panel = nullptr;
    --mem;
  }
  if(m_selection != nullptr)
  {
    delete m_selection;
    m_selection = nullptr;
    --mem;
  }
  if(m_portrait_img.id != 0)
  {
    UnloadTexture(m_portrait_img);
  }
}

void Textbox::update_input(World* world)
{
  m_start = true;

  if(m_start == true && m_dead == false)
  {
    if(m_expanded == false)
    {
      if(m_start_x > m_size_x)
      {
        m_start_x -= m_x_speed;
        m_start_y -= m_y_speed;
        m_start_w = (m_size_x + m_size_w / 2 - m_start_x) * 2;
        m_start_h = (m_size_y + m_size_h / 2 - m_start_y) * 2;
      }
      else
      {
        m_start_x = m_size_x;
        m_start_y = m_size_y;
        m_start_w = m_size_w;
        m_start_h = m_size_h;
        m_expanded = true;
      }
    }

    if(m_shrink == true && m_expanded == true)
    {
      if(m_start_w > 9 && m_dead == false)
      {
        m_start_x += m_x_speed;
        m_start_y += m_y_speed;
        m_start_w = (m_size_x + m_size_w / 2 - m_start_x) * 2;
        m_start_h = (m_size_y + m_size_h / 2 - m_start_y) * 2;
      }
      else
      {
        m_dead = true;
      }
    }
    
    if(m_expanded == true && m_shrink == false)
    {
      if(m_selection != nullptr)
      {
        m_selection->update_input(world);
        if(IsKeyPressed(KEY_Z) == true)
        {
          on_click();
        }
      }
      else
      {
        m_continue_arrow_animation.update();
        if(IsKeyPressed(KEY_Z) == true)
        {
          on_click();
        }
      }
    }
    m_panel->set_position(m_start_x, m_start_y, m_start_w, m_start_h);
  }
}

void Textbox::render(World* world) const
{
  if(m_start == true && m_dead == false)
  {
    m_panel->render(world);
    if(m_expanded == true && m_shrink == false)
    {
      render_textbox(m_text_chunks[0], world, "Text");
      if(m_title_text != "")
      {
        world->render_text("Character Title", m_title_text, m_title_x, m_title_y);
      }
      if(m_portrait_img.id != 0)
      {
        DrawTexture(m_portrait_img, m_portrait_x, m_portrait_y, Color{0xFF, 0xFF, 0xFF, 0xFF});
      }
      if(m_selection != nullptr)
      {
        m_selection->render(world);
      }
      if(m_continue_arrow_animation.is_visible() == true)
      {
        world->render_continue_arrow(m_size_x + m_size_w / 2.0, m_size_y + m_size_h);
      }
    }
  }
}

long Textbox::get_selected_item() const
{
  return m_selection->get_highlighted_item();
}

bool Textbox::dead() const
{
  return m_dead;
}

void Textbox::on_click()
{
  if(m_expanded == false)
  {
    return;
  }
  
  if(m_text_chunks.empty() == false)
  {
    m_text_chunks.erase(m_text_chunks.begin());
  }
  if(m_text_chunks.size() == 0)
  {
    m_shrink = true;
  }
  else if(m_text_chunks.size() == 1)
  {
    m_continue_arrow_animation.set_loop(false);
    m_continue_arrow_animation.set_visibility(false);
  }
}

void Textbox::break_text(string text, World* world, const string & font_name)
{
  long current_x_pos{m_text_area_x};
  string current_word{""};
  long word_width{0};
  char next_char{'a'};
  string build_text;
  long lines_left{static_cast<long>(floor(m_text_area_h / world->get_font_height(font_name)))};

  while(text.empty() == false)
  {
    while(text.empty() == false && lines_left != 0)
    {
      // If there's a space at the beginning of the current word, add the space to the current word string.
      next_char = text[0];
      if(next_char == ' ')
      {
        word_width += world->get_char_width(font_name, text[0]);
        current_word.push_back(' ');
        text.erase(text.begin());
      }
      // Keep adding characters to the current word string until a space is hit or the text box text is empty.
      next_char = text[0];
      while(next_char != ' ' && text.empty() == false)
      {
        word_width += world->get_char_width(font_name, text[0]);
        current_word.push_back(text[0]);
        text.erase(text.begin());
        if(text.empty() == false)
        {
          next_char = text[0];
        }
      }

      // If the width of the current word exceeds the width of the text box,
      // change the rendering position of the letters and erase the leading space from the current word.
      if(current_x_pos - m_text_area_x + word_width > m_text_area_w)
      {
        current_x_pos = m_text_area_x;
        --lines_left;
        if(current_word.empty() == false)
        {
          next_char = current_word[0];
          if(next_char == ' ')
          {
            current_word.erase(current_word.begin());
            build_text.push_back(' ');
          }
        }
      }
      word_width = 0;

      if(lines_left == 0)
      {
        string temp(current_word);
        for(long i{0}; i < static_cast<long>(temp.size()); ++i)
        {
          text.insert(text.begin() + i, temp[i]);
        }
        current_word = "";
      }

      while(current_word.empty() == false)
      {
        current_x_pos += world->get_char_width(font_name, current_word[0]);
        build_text.push_back(current_word[0]);
        current_word.erase(current_word.begin());
      }
    }
    lines_left = static_cast<long>(floor(m_text_area_h / world->get_font_height(font_name)));
    m_text_chunks.push_back(build_text);
    build_text = "";
  }
}

void Textbox::render_textbox(string text, World* world, const string & font_name) const
{
  long current_x_pos{m_text_area_x};
  long current_y_pos{m_text_area_y};
  string current_word{""};
  long word_width{0};
  char next_char{'a'};
  long lines_left{static_cast<long>(floor(m_text_area_h / world->get_font_height(font_name)))};

  // Repeat until the text box text is empty.
  while(text.empty() == false && lines_left != 0)
  {
    // If there's a space at the beginning of the current word, add the space to the current word string.
    next_char = text[0];
    if(next_char == ' ')
    {
      word_width += world->get_char_width(font_name, text[0]);
      current_word.push_back(' ');
      text.erase(text.begin());
    }
    // Keep adding characters to the current word string until a space is hit or the text box text is empty.
    next_char = text[0];
    while(next_char != ' ' && text.empty() == false)
    {
      word_width += world->get_char_width(font_name, text[0]);
      current_word.push_back(text[0]);
      text.erase(text.begin());
      if(text.empty() == false)
      {
        next_char = text[0];
      }
    }

    // If the width of the current word exceeds the width of the text box,
    // change the rendering position of the letters and erase the leading space from the current word.
    if(current_x_pos - m_text_area_x + word_width > m_text_area_w)
    {
      current_y_pos += world->get_font_height(font_name);
      current_x_pos = m_text_area_x;
      --lines_left;
      if(current_word.empty() == false)
      {
        next_char = current_word[0];
        if(next_char == ' ')
        {
          current_word.erase(current_word.begin());
        }
      }
    }
    word_width = 0;

    // Draw the letters in the current word to the screen letter by letter.
    while(current_word.empty() == false)
    {
      world->render_letter(font_name, current_x_pos, current_y_pos, current_word[0]);
      current_x_pos += world->get_char_width(font_name, current_word[0]);
      current_word.erase(current_word.begin());
    }
  }
}

void Panel::set_position(const double & x, const double & y, const double & width, const double & height)
{
  m_x = x;
  m_y = y;
  m_w = width;
  m_h = height;
}

void Panel::render(World* world) const
{
  world->render_panel(m_x, m_y, m_w, m_h);
}

Player_Summary::Player_Summary(const long & x, const long & y, const string & party_member_name, const bool & row)
{
  m_x = x;
  m_y = y;
  m_y_tween_current = m_y;
  m_y_tween_end = m_y;
  m_player_name = party_member_name;
  m_portrait_tween_current = row == true ? 0 : PLAYER_SUMMARY_ROW_OFFSET;
  m_portrait_tween_end = row == true ? 0 : PLAYER_SUMMARY_ROW_OFFSET;
  m_hp = new Progress_Bar{"Progress Bar Background", "Progress Bar Green", PLAYER_SUMMARY_PROGRESS_BAR_LENGTH};
  m_mp = new Progress_Bar{"Progress Bar Background", "Progress Bar Blue", PLAYER_SUMMARY_PROGRESS_BAR_LENGTH};
  m_exp = new Progress_Bar{"Progress Bar Background", "Progress Bar Pink", PLAYER_SUMMARY_PROGRESS_BAR_LENGTH};
  m_soul_break = new Progress_Bar{"Progress Bar Background", "Progress Bar Red", PLAYER_SUMMARY_PROGRESS_BAR_LENGTH};
  m_scroll = new Progress_Bar{"Progress Bar Background", "Progress Bar Orange", PLAYER_SUMMARY_PROGRESS_BAR_LENGTH};
  ++mem;
  ++mem;
  ++mem;
  ++mem;
  ++mem;
}

void Player_Summary::set_portrait_tween(const bool & start)
{
  m_portrait_tween_end = start == true ? 0 : PLAYER_SUMMARY_ROW_OFFSET;
}

void Player_Summary::set_y_tween(const long & index1, const long & index2, const bool & index)
{
  m_difference_of_swap_indexes = index2 - index1;
  if(index == 0)
  {
    m_y_tween_end = -m_difference_of_swap_indexes * (PLAYER_SUMMARY_SECTION_PADDING + TEXT_FONT_HEIGHT * 4) + m_y;
  }
  if(index == 1)
  {
    m_y_tween_end = -m_difference_of_swap_indexes * (PLAYER_SUMMARY_SECTION_PADDING + TEXT_FONT_HEIGHT * 4) + m_y;
  }
  m_difference_of_swap_indexes = abs(m_difference_of_swap_indexes);
}

void Player_Summary::toggle_switch_rect()
{
  if(m_switch_rect == true)
  {
    m_switch_rect = false;
  }
  else
  {
    m_switch_rect = true;
  }
}

string Player_Summary::get_name() const
{
  return m_player_name;
}

bool Player_Summary::get_switch() const
{
  return m_switch_rect;
}

void Player_Summary::update_tweens(World* world)
{
  m_hp->set_value(world->get_party_member_unmodified_stat(m_player_name, "HP"), world->get_party_member_stat(m_player_name, "Max HP"));
  m_mp->set_value(world->get_party_member_unmodified_stat(m_player_name, "MP"), world->get_party_member_stat(m_player_name, "Max MP"));
  m_exp->set_value(world->get_party_member_unmodified_stat(m_player_name, "EXP"), world->get_party_member_unmodified_stat(m_player_name, "Next Level Total EXP"), world->get_party_member_unmodified_stat(m_player_name, "Current Level Starting EXP"));

  if(m_portrait_tween_current < m_portrait_tween_end - .001 || m_portrait_tween_current > m_portrait_tween_end + .001)
  {
    if(m_portrait_tween_current >= m_portrait_tween_end)
    {
      m_portrait_tween_current -= PLAYER_SUMMARY_ROW_OFFSET / (PLAYER_SUMMARY_ROW_PORTRAIT_TWEEN_TIME * SCREEN_FPS);
      if(m_portrait_tween_current <= m_portrait_tween_end)
      {
        m_portrait_tween_current = m_portrait_tween_end;
      }
    }
    if(m_portrait_tween_current <= m_portrait_tween_end)
    {
      m_portrait_tween_current += PLAYER_SUMMARY_ROW_OFFSET / (PLAYER_SUMMARY_ROW_PORTRAIT_TWEEN_TIME * SCREEN_FPS);
      if(m_portrait_tween_current >= m_portrait_tween_end)
      {
        m_portrait_tween_current = m_portrait_tween_end;
      }
    }
  }
  
  if(m_y_tween_current < m_y_tween_end - .001 || m_y_tween_current > m_y_tween_end + .001)
  {
    if(m_y_tween_current >= m_y_tween_end)
    {
      m_y_tween_current -= m_difference_of_swap_indexes * (PLAYER_SUMMARY_SECTION_PADDING + TEXT_FONT_HEIGHT * 4) / (PLAYER_SUMMARY_ROW_PORTRAIT_TWEEN_TIME * SCREEN_FPS);
      if(m_y_tween_current <= m_y_tween_end)
      {
        m_y_tween_current = m_y_tween_end;
      }
      m_y = m_y_tween_current + .5;
    }
    if(m_y_tween_current <= m_y_tween_end)
    {
      m_y_tween_current += m_difference_of_swap_indexes * (PLAYER_SUMMARY_SECTION_PADDING + TEXT_FONT_HEIGHT * 4) / (PLAYER_SUMMARY_ROW_PORTRAIT_TWEEN_TIME * SCREEN_FPS);
      if(m_y_tween_current >= m_y_tween_end)
      {
        m_y_tween_current = m_y_tween_end;
      }
      m_y = m_y_tween_current + .5;
    }
  }
}

void Player_Summary::render(World* world) const
{
  if(m_switch_rect == true)
  {
    DrawRectangle(m_x + TEXTBOX_PADDING_LONG, m_y + TEXTBOX_PADDING_SHORT, PLAYER_SUMMARY_SECTION_WIDTH * 4, TEXT_FONT_HEIGHT * 4, Color{192, 255, 192, 255});
  }
  world->render_party_member_portrait(m_player_name, 0, m_x + TEXTBOX_PADDING_LONG + m_portrait_tween_current, m_y + TEXTBOX_PADDING_SHORT);
  world->render_text("Text", world->get_party_member_row(m_player_name) == true ? "Front" : "Back", m_x + TEXTBOX_PADDING_LONG, m_y + TEXTBOX_PADDING_SHORT);
  world->render_text("Text", "Row", m_x + TEXTBOX_PADDING_LONG, m_y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT);
  world->render_text("Text", m_player_name + " Lv. " + to_string(world->get_party_member_unmodified_stat(m_player_name, "Level")), m_x + TEXTBOX_PADDING_LONG + PLAYER_SUMMARY_SECTION_WIDTH + PLAYER_SUMMARY_SECTION_PADDING, m_y + TEXTBOX_PADDING_SHORT);
  world->render_text("Text", world->get_party_member_species(m_player_name), m_x + TEXTBOX_PADDING_LONG + PLAYER_SUMMARY_SECTION_WIDTH * 2 + PLAYER_SUMMARY_SECTION_PADDING, m_y + TEXTBOX_PADDING_SHORT);
  world->render_text("Text", world->get_party_member_class(m_player_name), m_x + TEXTBOX_PADDING_LONG + PLAYER_SUMMARY_SECTION_WIDTH * 3 + PLAYER_SUMMARY_SECTION_PADDING, m_y + TEXTBOX_PADDING_SHORT);
  world->render_text("Text", "HP    " + to_string(world->get_party_member_unmodified_stat(m_player_name, "HP")) + "/" + to_string(world->get_party_member_stat(m_player_name, "Max HP")), m_x + TEXTBOX_PADDING_LONG + PLAYER_SUMMARY_SECTION_WIDTH + PLAYER_SUMMARY_SECTION_PADDING, m_y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT + PLAYER_SUMMARY_PROGRESS_BAR_TEXT_OFFSET);
  world->render_text("Text", "MP    " + to_string(world->get_party_member_unmodified_stat(m_player_name, "MP")) + "/" + to_string(world->get_party_member_stat(m_player_name, "Max MP")), m_x + TEXTBOX_PADDING_LONG + PLAYER_SUMMARY_SECTION_WIDTH + PLAYER_SUMMARY_SECTION_PADDING, m_y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * 2 + PLAYER_SUMMARY_PROGRESS_BAR_TEXT_OFFSET);
  world->render_text("Text", "Soul Break    " + to_string(world->get_party_member_soul_break_level(m_player_name)), m_x + TEXTBOX_PADDING_LONG + PLAYER_SUMMARY_SECTION_WIDTH * 2 + PLAYER_SUMMARY_SECTION_PADDING, m_y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT + PLAYER_SUMMARY_PROGRESS_BAR_TEXT_OFFSET);
  world->render_text("Text", "Scroll", m_x + TEXTBOX_PADDING_LONG + PLAYER_SUMMARY_SECTION_WIDTH * 2 + PLAYER_SUMMARY_SECTION_PADDING, m_y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * 2 + PLAYER_SUMMARY_PROGRESS_BAR_TEXT_OFFSET);
  world->render_text("Text", "EXP " + to_string(world->get_party_member_unmodified_stat(m_player_name, "EXP")), m_x + TEXTBOX_PADDING_LONG + PLAYER_SUMMARY_SECTION_WIDTH * 3 + PLAYER_SUMMARY_SECTION_PADDING, m_y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT);
  world->render_text("Text", "Next Lv. " + to_string(world->get_party_member_unmodified_stat(m_player_name, "Next Level EXP")), m_x + TEXTBOX_PADDING_LONG + PLAYER_SUMMARY_SECTION_WIDTH * 3 + PLAYER_SUMMARY_SECTION_PADDING, m_y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * 2 + PLAYER_SUMMARY_PROGRESS_BAR_TEXT_OFFSET);
  m_hp->render(world, m_x + TEXTBOX_PADDING_LONG + PLAYER_SUMMARY_SECTION_WIDTH + PLAYER_SUMMARY_SECTION_PADDING, m_y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * 2 + PLAYER_SUMMARY_PROGRESS_BAR_BAR_OFFSET);
  m_mp->render(world, m_x + TEXTBOX_PADDING_LONG + PLAYER_SUMMARY_SECTION_WIDTH + PLAYER_SUMMARY_SECTION_PADDING, m_y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * 3 + PLAYER_SUMMARY_PROGRESS_BAR_BAR_OFFSET);
  m_exp->render(world, m_x + TEXTBOX_PADDING_LONG + PLAYER_SUMMARY_SECTION_WIDTH * 3 + PLAYER_SUMMARY_SECTION_PADDING, m_y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * 3 + PLAYER_SUMMARY_PROGRESS_BAR_BAR_OFFSET);
  m_soul_break->render(world, m_x + TEXTBOX_PADDING_LONG + PLAYER_SUMMARY_SECTION_WIDTH * 2 + PLAYER_SUMMARY_SECTION_PADDING, m_y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * 2 + PLAYER_SUMMARY_PROGRESS_BAR_BAR_OFFSET);
  m_scroll->render(world, m_x + TEXTBOX_PADDING_LONG + PLAYER_SUMMARY_SECTION_WIDTH * 2 + PLAYER_SUMMARY_SECTION_PADDING, m_y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * 3 + PLAYER_SUMMARY_PROGRESS_BAR_BAR_OFFSET);
}

Player_Summary::~Player_Summary()
{
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

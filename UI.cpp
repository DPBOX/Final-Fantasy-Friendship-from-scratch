#include "Main.h"
#include "UI.h"

Fnt::Fnt(const Font_Params & font_to_load)
{
  m_name = font_to_load.m_name;
  m_cell_width = font_to_load.m_cell_width;
  m_char_widths = font_to_load.m_char_widths;
  Image image{LoadImageFromMemory(".png", font_to_load.m_data, font_to_load.m_size)};
  m_font_img = LoadTextureFromImage(image);
  UnloadImage(image);
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

void Progress_Bar::render(const World* const world, const long & x, const long & y) const
{
  for(long i{0}; i < m_length; ++i)
  {
    world->render_progress_bar("Progress Bar Background", x + i, y);
  }

  if(m_value > 0)
  {
    if(m_value >= MAX_PROGRESS_BAR_VALUE)
    {
      for(long i{0}; i < m_length; ++i)
      {
        world->render_progress_bar(m_color, x + i, y);
      }
    }
    else
    {
      long value{static_cast<long>(m_length * m_value / MAX_PROGRESS_BAR_VALUE + .5)};

      if(value <= 0)
      {
        world->render_progress_bar(m_color, x, y);
      }
      else if(value >= m_length)
      {
        for(long i{0}; i < m_length - 1; ++i)
        {
          world->render_progress_bar(m_color, x + i, y);
        }
      }
      else
      {
        for(long i{0}; i < value; ++i)
        {
          world->render_progress_bar(m_color, x + i, y);
        }
      }
    }
  }
}

void Textbox::create_fitted_choices(const long & size_x, const long & size_y, const vector<string> & choices)
{
  m_choices = choices;
  Selection* s{new Selection{static_cast<long>(choices.size()), static_cast<long>(choices.size()), 1, 1}};
  ++mem;
  create_fixed(size_x, size_y, get_text_font_word_width(m_text) + TEXTBOX_PADDING_LONG * 2, TEXT_FONT_HEIGHT * 2 + TEXTBOX_PADDING_SHORT * 2);
  Selection_Renderer* sr{new Selection_Renderer{s, m_text_area_x, m_text_area_y + m_text_area_h - TEXT_FONT_HEIGHT, m_text_area_w}};
  ++mem;
  add_selection_menu(s, sr);
}

void Textbox::create_fixed(const long & size_x, const long & size_y, const long & size_width, const long & size_height)
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
  m_center_x = m_size_x + m_size_w / 2;
  m_center_y = m_size_y + m_size_h / 2;
  m_start_x = m_size_x + m_size_w / 2 - 4.5;
  m_start_y = m_size_y + m_size_h / 2 - 4.5;
  m_start_w = 9;
  m_start_h = 9;
  m_x_speed = (m_size_w / 2 - 4.5) / PANEL_SPEED;
  m_y_speed = (m_size_h / 2 - 4.5) / PANEL_SPEED;
  m_continue_arrow_animation = Blinking_Animation(false, false, CONTINUE_ARROW_INTERVAL);
  m_panel = new Panel(m_start_x, m_start_y, m_start_w, m_start_h);
  ++mem;
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

  break_text(m_text);
  
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
  if(m_selection_renderer != nullptr)
  {
    delete m_selection_renderer;
    m_selection_renderer = nullptr;
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
        m_selection->update_input(world, m_text_area_x, m_text_area_y + m_text_area_h - TEXT_FONT_HEIGHT, m_text_area_w);
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

void Textbox::render(const World* const world) const
{
  if(m_start == true && m_dead == false)
  {
    m_panel->render(world);
    if(m_expanded == true && m_shrink == false)
    {
      long current_x_pos{m_text_area_x};
      long current_y_pos{m_text_area_y};
      string current_word{""};
      long word_width{0};
      char next_char{'a'};
      long lines_left{static_cast<long>(floor(m_text_area_h / TEXT_FONT_HEIGHT))};
      string text{m_text_chunks[0]};

      // Repeat until the text box text is empty.
      while(text.empty() == false && lines_left != 0)
      {
        // If there's a space at the beginning of the current word, add the space to the current word string.
        next_char = text[0];
        if(next_char == ' ')
        {
          word_width += FONT_TEXT_CHAR_WIDTHS[text[0]];
          current_word.push_back(' ');
          text.erase(text.begin());
        }
        // Keep adding characters to the current word string until a space is hit or the text box text is empty.
        next_char = text[0];
        while(next_char != ' ' && text.empty() == false)
        {
          word_width += FONT_TEXT_CHAR_WIDTHS[text[0]];
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
          current_y_pos += TEXT_FONT_HEIGHT;
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
          world->render_letter("Text", current_x_pos, current_y_pos, current_word[0]);
          current_x_pos += FONT_TEXT_CHAR_WIDTHS[current_word[0]];
          current_word.erase(current_word.begin());
        }
      }

      if(m_title_text != "")
      {
        world->render_text("Character Title", m_title_text, m_title_x, m_title_y);
      }
      if(m_portrait_img.id != 0)
      {
        DrawTexture(m_portrait_img, m_portrait_x, m_portrait_y, Color{0xFF, 0xFF, 0xFF, 0xFF});
      }
      if(m_selection_renderer != nullptr)
      {
        m_selection_renderer->render(m_choices, world);
      }
      if(m_continue_arrow_animation.is_visible() == true)
      {
        world->render_continue_arrow(m_size_x + m_size_w / 2, m_size_y + m_size_h, false);
      }
    }
  }
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

void Textbox::break_text(string text)
{
  long current_x_pos{m_text_area_x};
  string current_word{""};
  long word_width{0};
  char next_char{'a'};
  string build_text;
  long lines_left{static_cast<long>(floor(m_text_area_h / TEXT_FONT_HEIGHT))};

  while(text.empty() == false)
  {
    while(text.empty() == false && lines_left != 0)
    {
      // If there's a space at the beginning of the current word, add the space to the current word string.
      next_char = text[0];
      if(next_char == ' ')
      {
        word_width += FONT_TEXT_CHAR_WIDTHS[text[0]];
        current_word.push_back(' ');
        text.erase(text.begin());
      }
      // Keep adding characters to the current word string until a space is hit or the text box text is empty.
      next_char = text[0];
      while(next_char != ' ' && text.empty() == false)
      {
        word_width += FONT_TEXT_CHAR_WIDTHS[text[0]];
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
        current_x_pos += FONT_TEXT_CHAR_WIDTHS[current_word[0]];
        build_text.push_back(current_word[0]);
        current_word.erase(current_word.begin());
      }
    }
    lines_left = static_cast<long>(floor(m_text_area_h / TEXT_FONT_HEIGHT));
    m_text_chunks.push_back(build_text);
    build_text = "";
  }
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

void Player_Summary::update_tweens()
{
  m_hp->set_value(m_current_hp, m_max_hp);
  m_mp->set_value(m_current_mp, m_max_mp);
  m_exp->set_value(m_current_exp, m_exp_to_next_level);

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

void Player_Summary::render(const World* const world) const
{
  if(m_switch_rect == true)
  {
    DrawRectangle(m_x + TEXTBOX_PADDING_LONG, m_y + TEXTBOX_PADDING_SHORT, PLAYER_SUMMARY_SECTION_WIDTH * 4, TEXT_FONT_HEIGHT * 4, Color{192, 255, 192, 255});
  }
  DrawTexturePro(m_small_portrait, Rectangle{0, 0, static_cast<float>(m_small_portrait.width), static_cast<float>(m_small_portrait.height)}, Rectangle{static_cast<float>(m_x + TEXTBOX_PADDING_LONG + m_portrait_tween_current), static_cast<float>(m_y + TEXTBOX_PADDING_SHORT), static_cast<float>(m_small_portrait.width), static_cast<float>(m_small_portrait.height)}, Vector2{0, 0}, 0, Color{0xFF, 0xFF, 0xFF, 0xFF});
  world->render_text("Text", m_row == true ? "Front" : "Back", m_x + TEXTBOX_PADDING_LONG, m_y + TEXTBOX_PADDING_SHORT);
  world->render_text("Text", "Row", m_x + TEXTBOX_PADDING_LONG, m_y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT);
  world->render_text("Text", m_player_name + " Lv. " + to_string(m_level), m_x + TEXTBOX_PADDING_LONG + PLAYER_SUMMARY_SECTION_WIDTH + PLAYER_SUMMARY_SECTION_PADDING, m_y + TEXTBOX_PADDING_SHORT);
  world->render_text("Text", m_player_species, m_x + TEXTBOX_PADDING_LONG + PLAYER_SUMMARY_SECTION_WIDTH * 2 + PLAYER_SUMMARY_SECTION_PADDING, m_y + TEXTBOX_PADDING_SHORT);
  world->render_text("Text", m_player_class, m_x + TEXTBOX_PADDING_LONG + PLAYER_SUMMARY_SECTION_WIDTH * 3 + PLAYER_SUMMARY_SECTION_PADDING, m_y + TEXTBOX_PADDING_SHORT);
  world->render_text("Text", "HP    " + to_string(m_current_hp) + "/" + to_string(m_max_hp), m_x + TEXTBOX_PADDING_LONG + PLAYER_SUMMARY_SECTION_WIDTH + PLAYER_SUMMARY_SECTION_PADDING, m_y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT + PLAYER_SUMMARY_PROGRESS_BAR_TEXT_OFFSET);
  world->render_text("Text", "MP    " + to_string(m_current_mp) + "/" + to_string(m_max_mp), m_x + TEXTBOX_PADDING_LONG + PLAYER_SUMMARY_SECTION_WIDTH + PLAYER_SUMMARY_SECTION_PADDING, m_y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * 2 + PLAYER_SUMMARY_PROGRESS_BAR_TEXT_OFFSET);
  world->render_text("Text", "Soul Break    " + to_string(1), m_x + TEXTBOX_PADDING_LONG + PLAYER_SUMMARY_SECTION_WIDTH * 2 + PLAYER_SUMMARY_SECTION_PADDING, m_y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT + PLAYER_SUMMARY_PROGRESS_BAR_TEXT_OFFSET);
  world->render_text("Text", "Scroll", m_x + TEXTBOX_PADDING_LONG + PLAYER_SUMMARY_SECTION_WIDTH * 2 + PLAYER_SUMMARY_SECTION_PADDING, m_y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * 2 + PLAYER_SUMMARY_PROGRESS_BAR_TEXT_OFFSET);
  world->render_text("Text", "EXP " + to_string(m_current_exp), m_x + TEXTBOX_PADDING_LONG + PLAYER_SUMMARY_SECTION_WIDTH * 3 + PLAYER_SUMMARY_SECTION_PADDING, m_y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT);
  world->render_text("Text", "Next Lv. " + to_string(m_exp_to_next_level), m_x + TEXTBOX_PADDING_LONG + PLAYER_SUMMARY_SECTION_WIDTH * 3 + PLAYER_SUMMARY_SECTION_PADDING, m_y + TEXTBOX_PADDING_SHORT + TEXT_FONT_HEIGHT * 2 + PLAYER_SUMMARY_PROGRESS_BAR_TEXT_OFFSET);
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
  UnloadTexture(m_small_portrait);
}

void Selection::update_input(World* world, const long & x, const long & y, const long & spacing_x, const long & spacing_y)
{
  m_continue_arrow_animation.update();

  if(m_show_cursor == true)
  {
    if(m_focus_x + m_focus_y * m_columns >= m_num_choices)
    {
      if(m_focus_x != 0)
      {
        --m_focus_x;
      }
      else if(m_focus_y != 0)
      {
        --m_focus_y;
        if(m_focus_y < m_display_start)
        {
          --m_display_start;
        }
      }
    }
    if(IsKeyPressed(KEY_UP) == true)
    {
      long m_focus_y_temp{max(m_focus_y - 1, static_cast<long>(0))};
      if(m_focus_x + m_focus_y_temp * m_columns < m_num_choices)
      {
        if(m_focus_y_temp != m_focus_y)
        {
          g_sound_player->play_global_sound("Cursor");
        }
        m_focus_y = max(m_focus_y - 1, static_cast<long>(0));
        if(m_focus_y < m_display_start)
        {
          --m_display_start;
        }
      }
    }

    if(IsKeyPressed(KEY_DOWN) == true)
    {
      long m_focus_y_temp{min(m_focus_y + 1, m_max_rows - 1)};
      if(m_focus_x + m_focus_y_temp * m_columns < m_num_choices)
      {
        if(m_focus_y_temp != m_focus_y)
        {
          g_sound_player->play_global_sound("Cursor");
        }
        m_focus_y = min(m_focus_y + 1, m_max_rows - 1);
        if(m_focus_y > m_display_start + m_display_rows - 1)
        {
          ++m_display_start;
        }
      }
    }

    if(IsKeyPressed(KEY_LEFT) == true)
    {
      long m_focus_x_temp{max(m_focus_x - 1, static_cast<long>(0))};
      if(m_focus_x_temp + m_focus_y * m_columns < m_num_choices)
      {
        if(m_focus_x_temp != m_focus_x)
        {
          g_sound_player->play_global_sound("Cursor");
        }
        m_focus_x = max(m_focus_x - 1, static_cast<long>(0));
      }
    }

    if(IsKeyPressed(KEY_RIGHT) == true)
    {
      long m_focus_x_temp{min(m_focus_x + 1, m_columns - 1)};
      if(m_focus_x_temp + m_focus_y * m_columns < m_num_choices)
      {
        if(m_focus_x_temp != m_focus_x)
        {
          g_sound_player->play_global_sound("Cursor");
        }
        m_focus_x = min(m_focus_x + 1, m_columns - 1);
      }
    }
    world->set_cursor_destination(x + spacing_x * m_focus_x / m_columns, y + spacing_y * (m_focus_y - m_display_start));
    m_highlighted_item = m_focus_x + m_focus_y * m_columns;

    long display_start{m_display_start};
    long display_end{m_display_start + m_display_rows};
    if(display_start != 0 || display_end * m_columns < m_num_choices)
    {
      m_continue_arrow_animation.set_loop(true);
    }
    else
    {
      m_continue_arrow_animation.set_loop(false);
      m_continue_arrow_animation.set_visibility(false);
    }
  }
  else
  {
    m_continue_arrow_animation.set_loop(false);
    m_continue_arrow_animation.set_visibility(false);
  }
}

void Selection_Renderer::render(const vector<string> & choices, const World* const world) const
{
  if(m_selection->menu_shown() == true)
  {
    long display_start{m_selection->get_display_start()};
    long display_end{display_start + m_selection->get_display_rows()};
    long x{m_x};
    long y{m_y};
    long item_index{display_start * m_selection->get_columns()};

    for(long i{display_start}; i < display_end; ++i)
    {
      for(long j{0}; j < m_selection->get_columns(); ++j)
      {
        if(item_index >= 0 && item_index < static_cast<long>(choices.size()))
        {
          world->render_text("Text", choices[item_index], x, y);
        }
        x += m_spacing_x;
        ++item_index;
      }
      y += m_spacing_y;
      x = m_x;
    }

    if(display_start != 0 && m_selection->animation_is_visible() == true)
    {
      world->render_continue_arrow(m_x + m_spacing_x * m_selection->get_columns() / 2, m_y, true);
    }
    if(display_end * m_selection->get_columns() < static_cast<long>(choices.size()) && m_selection->animation_is_visible() == true)
    {
      world->render_continue_arrow(m_x + m_spacing_x * m_selection->get_columns() / 2, m_y + m_spacing_y * m_selection->get_display_rows(), false);
    }
  }
}

void Selection_Renderer::render_items(const vector<string> & choices, const World* const world, const vector<string> & item_descriptions, const vector<long> & item_quantities) const
{
  if(m_selection->menu_shown() == true)
  {
    long display_start{m_selection->get_display_start()};
    long display_end{display_start + m_selection->get_display_rows()};
    long x{m_x};
    long y{m_y};
    long item_index{display_start * m_selection->get_columns()};

    for(long i{display_start}; i < display_end; ++i)
    {
      for(long j{0}; j < m_selection->get_columns(); ++j)
      {
        if(item_index >= 0 && item_index < static_cast<long>(choices.size()))
        {
          long current_pos{x};
          world->render_item_icon(CONSUMABLE_ITEM_ICON, x, y);
          current_pos += ICON_WIDTH;
          string text{choices[item_index]};
          while(text != "")
          {
            world->render_letter("Text", current_pos, y, text[0]);
            current_pos += FONT_TEXT_CHAR_WIDTHS[text[0]];
            text.erase(text.begin());
          }
          current_pos = x + m_spacing_x * ITEM_QUANTITY_LOCATION_FRACTION;
          text = "x" + to_string(item_quantities[item_index]);
          while(text != "")
          {
            world->render_letter("Text", current_pos, y, text[0]);
            current_pos += FONT_TEXT_CHAR_WIDTHS[text[0]];
            text.erase(text.begin());
          }
          if(m_selection->cursor_shown() == true)
          {
            world->render_text("Text", item_descriptions[m_selection->get_highlighted_item()], m_x, m_y - TEXTBOX_PADDING_SHORT * 2 - TEXT_FONT_HEIGHT);
          }
        }
        x += m_spacing_x;
        ++item_index;
      }
      y += m_spacing_y;
      x = m_x;
    }

    if(display_start != 0 && m_selection->animation_is_visible() == true)
    {
      world->render_continue_arrow(m_x + m_spacing_x * m_selection->get_columns() / 2, m_y, true);
    }
    if(display_end * m_selection->get_columns() < static_cast<long>(choices.size()) && m_selection->animation_is_visible() == true)
    {
      world->render_continue_arrow(m_x + m_spacing_x * m_selection->get_columns() / 2, m_y + m_spacing_y * m_selection->get_display_rows(), false);
    }
  }
}

void Selection_Renderer::render_key_items(const vector<string> & choices, const World* const world, const vector<string> & item_descriptions) const
{
  if(m_selection->menu_shown() == true)
  {
    long display_start{m_selection->get_display_start()};
    long display_end{display_start + m_selection->get_display_rows()};
    long x{m_x};
    long y{m_y};
    long item_index{display_start * m_selection->get_columns()};

    for(long i{display_start}; i < display_end; ++i)
    {
      for(long j{0}; j < m_selection->get_columns(); ++j)
      {
        if(item_index >= 0 && item_index < static_cast<long>(choices.size()))
        {
          long current_pos{x};
          world->render_item_icon(KEY_ITEM_ICON, x, y);
          current_pos += ICON_WIDTH;
          string text{choices[item_index]};
          while(text != "")
          {
            world->render_letter("Text", current_pos, y, text[0]);
            current_pos += FONT_TEXT_CHAR_WIDTHS[text[0]];
            text.erase(text.begin());
          }
          if(m_selection->cursor_shown() == true)
          {
            world->render_text("Text", item_descriptions[m_selection->get_highlighted_item()], m_x, m_y - TEXTBOX_PADDING_SHORT * 2 - TEXT_FONT_HEIGHT);
          }
        }
        x += m_spacing_x;
        ++item_index;
      }
      y += m_spacing_y;
      x = m_x;
    }

    if(display_start != 0 && m_selection->animation_is_visible() == true)
    {
      world->render_continue_arrow(m_x + m_spacing_x * m_selection->get_columns() / 2, m_y, true);
    }
    if(display_end * m_selection->get_columns() < static_cast<long>(choices.size()) && m_selection->animation_is_visible() == true)
    {
      world->render_continue_arrow(m_x + m_spacing_x * m_selection->get_columns() / 2, m_y + m_spacing_y * m_selection->get_display_rows(), false);
    }
  }
}

void Selection_Renderer::render_equipment(const vector<string> & choices, const World* const world, const string & character_name, const string & equipment_type, const long & slot, const vector<string> & item_descriptions, const vector<long> & item_quantities, const vector<string> & item_equipped_bys, const vector<long> & item_icons, const vector<bool> & item_usable_bys, const vector<long> & item_slots) const
{
  if(m_selection->menu_shown() == true)
  {
    long display_start{m_selection->get_display_start()};
    long display_end{display_start + m_selection->get_display_rows()};
    long x{m_x};
    long y{m_y};
    long item_index{display_start * m_selection->get_columns()};

    for(long i{display_start}; i < display_end; ++i)
    {
      for(long j{0}; j < m_selection->get_columns(); ++j)
      {
        if(item_index >= 0 && item_index < static_cast<long>(choices.size()))
        {
          long current_pos{x};
          world->render_item_icon(item_icons[item_index], x, y);
          current_pos += ICON_WIDTH;
          string text{choices[item_index]};
          while(text != "")
          {
            if(item_usable_bys[item_index] == false)
            {
              world->render_letter("Red", current_pos, y, text[0]);
            }
            else if(item_equipped_bys[item_index] == "NULL")
            {
              world->render_letter("Text", current_pos, y, text[0]);
            }
            else
            {
              world->render_letter("Character Title", current_pos, y, text[0]);
            }
            current_pos += FONT_TEXT_CHAR_WIDTHS[text[0]];
            text.erase(text.begin());
          }
          current_pos = x + m_spacing_x * ITEM_QUANTITY_LOCATION_FRACTION;
          if(item_equipped_bys[item_index] == "NULL")
          {
            text = "x" + to_string(item_quantities[item_index]);
          }
          else
          {
            text = "E";
          }
          while(text != "")
          {
            if(item_usable_bys[item_index] == false)
            {
              world->render_letter("Red", current_pos, y, text[0]);
            }
            else if(item_equipped_bys[item_index] == "NULL")
            {
              world->render_letter("Text", current_pos, y, text[0]);
            }
            else
            {
              world->render_letter("Character Title", current_pos, y, text[0]);
            }
            current_pos += FONT_TEXT_CHAR_WIDTHS[text[0]];
            text.erase(text.begin());
          }
          if(m_selection->cursor_shown() == true)
          {
            world->render_text("Text", item_descriptions[m_selection->get_highlighted_item()], m_x, m_y + TEXT_FONT_HEIGHT * 10);
            if(item_usable_bys[m_selection->get_highlighted_item()] == false)
            {
              world->render_text("Character Title", character_name + " can't equip this " + equipment_type + ".", m_x, m_y + TEXT_FONT_HEIGHT * 11);
            }
            else if((item_equipped_bys[m_selection->get_highlighted_item()] == character_name && item_slots.empty() == true) || (item_equipped_bys[m_selection->get_highlighted_item()] == character_name && item_slots.empty() == false && item_slots[m_selection->get_highlighted_item()] == slot))
            {
              world->render_text("Character Title", "Press A to unequip this.", m_x, m_y + TEXT_FONT_HEIGHT * 11);
            }
            else if(item_equipped_bys[m_selection->get_highlighted_item()] != "NULL")
            {
              if(equipment_type == "accessory")
              {
                world->render_text("Character Title", "Equipped by " + item_equipped_bys[m_selection->get_highlighted_item()] + " on Slot " + to_string(item_slots[m_selection->get_highlighted_item()] + 1) + ".", m_x, m_y + TEXT_FONT_HEIGHT * 11);
              }
              else
              {
                world->render_text("Character Title", "Equipped by " + item_equipped_bys[m_selection->get_highlighted_item()] + ".", m_x, m_y + TEXT_FONT_HEIGHT * 11);
              }
            }
          }
        }
        x += m_spacing_x;
        ++item_index;
      }
      y += m_spacing_y;
      x = m_x;
    }

    if(display_start != 0 && m_selection->animation_is_visible() == true)
    {
      world->render_continue_arrow(m_x + m_spacing_x * m_selection->get_columns() / 2, m_y, true);
    }
    if(display_end * m_selection->get_columns() < static_cast<long>(choices.size()) && m_selection->animation_is_visible() == true)
    {
      world->render_continue_arrow(m_x + m_spacing_x * m_selection->get_columns() / 2, m_y + m_spacing_y * m_selection->get_display_rows(), false);
    }
  }
}

void Selection_Renderer::render_status_menu(const vector<string> & choices, const World* const world,
                                            const long & strength, const long & unmodified_strength, const long & strength_difference,
                                            const long & attack, const long & unmodified_attack, const long & attack_difference,
                                            const long & speed, const long & unmodified_speed, const long & speed_difference,
                                            const long & defense, const long & unmodified_defense, const long & defense_difference,
                                            const long & intellect, const long & unmodified_intellect, const long & intellect_difference,
                                            const long & resistance, const long & unmodified_resistance, const long & resistance_difference,
                                            const long & stamina, const long & unmodified_stamina, const long & stamina_difference,
                                            const long & accuracy, const long & unmodified_accuracy, const long & accuracy_difference,
                                            const long & spirit, const long & unmodified_spirit, const long & spirit_difference,
                                            const long & critical, const long & unmodified_critical, const long & critical_difference,
                                            const long & evasion, const long & unmodified_evasion, const long & evasion_difference,
                                            const long & magic_evasion, const long & unmodified_magic_evasion, const long & magic_evasion_difference,
                                            const string & weapon_name, const long & weapon_icon, const string & shield_name, const long & shield_icon, const string & helm_name, const long & helm_icon, const string & armor_name, const long & armor_icon, const string & accessory_one_name, const long & accessory_one_icon, const string & accessory_two_name, const long & accessory_two_icon) const
{
  if(m_selection->menu_shown() == true)
  {
    long display_start{m_selection->get_display_start()};
    long display_end{display_start + m_selection->get_display_rows()};
    long x{m_x};
    long y{m_y};
    long item_index{display_start * m_selection->get_columns()};

    for(long i{display_start}; i < display_end; ++i)
    {
      for(long j{0}; j < m_selection->get_columns(); ++j)
      {
        if(item_index >= 0 && item_index < static_cast<long>(choices.size()))
        {
          long current_pos{x};
          string text{""};
          long font_color{0};
          switch(item_index)
          {
            case 0:
              text = choices[0] + " " + to_string(strength) + " (" + to_string(unmodified_strength) + ") " + (strength_difference != 0 ? (strength_difference > 0 ? "+" + to_string(strength_difference) : to_string(strength_difference)) : " ");
              font_color = strength_difference != 0 ? (strength_difference > 0 ? 2 : 1) : 0;
              break;
            case 1:
              text = choices[1] + " " + to_string(attack) + " (" + to_string(unmodified_attack) + ") " + (attack_difference != 0 ? (attack_difference > 0 ? "+" + to_string(attack_difference) : to_string(attack_difference)) : " ");
              font_color = attack_difference != 0 ? (attack_difference > 0 ? 2 : 1) : 0;
              break;
            case 2:
              if(weapon_name == "NULL")
              {
                text = "Weapon";
              }
              else
              {
                text = weapon_name;
              }
              break;
            case 3:
              text = choices[3] + " " + to_string(speed) + " (" + to_string(unmodified_speed) + ") " + (speed_difference != 0 ? (speed_difference > 0 ? "+" + to_string(speed_difference) : to_string(speed_difference)) : " ");
              font_color = speed_difference != 0 ? (speed_difference > 0 ? 2 : 1) : 0;
              break;
            case 4:
              text = choices[4] + " " + to_string(defense) + " (" + to_string(unmodified_defense) + ") " + (defense_difference != 0 ? (defense_difference > 0 ? "+" + to_string(defense_difference) : to_string(defense_difference)) : " ");
              font_color = defense_difference != 0 ? (defense_difference > 0 ? 2 : 1) : 0;
              break;
            case 5:
              if(shield_name == "NULL")
              {
                text = "Shield";
              }
              else
              {
                text = shield_name;
              }
              break;
            case 6:
              text = choices[6] + " " + to_string(intellect) + " (" + to_string(unmodified_intellect) + ") " + (intellect_difference != 0 ? (intellect_difference > 0 ? "+" + to_string(intellect_difference) : to_string(intellect_difference)) : " ");
              font_color = intellect_difference != 0 ? (intellect_difference > 0 ? 2 : 1) : 0;
              break;
            case 7:
              text = choices[7] + " " + to_string(resistance) + " (" + to_string(unmodified_resistance) + ") " + (resistance_difference != 0 ? (resistance_difference > 0 ? "+" + to_string(resistance_difference) : to_string(resistance_difference)) : " ");
              font_color = resistance_difference != 0 ? (resistance_difference > 0 ? 2 : 1) : 0;
              break;
            case 8:
              if(helm_name == "NULL")
              {
                text = "Helm";
              }
              else
              {
                text = helm_name;
             }
              break;
            case 9:
              text = choices[9] + " " + to_string(stamina) + " (" + to_string(unmodified_stamina) + ") " + (stamina_difference != 0 ? (stamina_difference > 0 ? "+" + to_string(stamina_difference) : to_string(stamina_difference)) : " ");
              font_color = stamina_difference != 0 ? (stamina_difference > 0 ? 2 : 1) : 0;
              break;
            case 10:
              text = choices[10] + " " + to_string(accuracy) + " (" + to_string(unmodified_accuracy) + ") " + (accuracy_difference != 0 ? (accuracy_difference > 0 ? "+" + to_string(accuracy_difference) : to_string(accuracy_difference)) : " ");
              font_color = accuracy_difference != 0 ? (accuracy_difference > 0 ? 2 : 1) : 0;
              break;
            case 11:
              if(armor_name == "NULL")
              {
                text = "Armor";
              }
              else
              {
                text = armor_name;
              }
              break;
            case 12:
              text = choices[12] + " " + to_string(spirit) + " (" + to_string(unmodified_spirit) + ") " + (spirit_difference != 0 ? (spirit_difference > 0 ? "+" + to_string(spirit_difference) : to_string(spirit_difference)) : " ");
              font_color = spirit_difference != 0 ? (spirit_difference > 0 ? 2 : 1) : 0;
              break;
            case 13:
              text = choices[13] + " " + to_string(critical) + " (" + to_string(unmodified_critical) + ") " + (critical_difference != 0 ? (critical_difference > 0 ? "+" + to_string(critical_difference) : to_string(critical_difference)) : " ");
              font_color = critical_difference != 0 ? (critical_difference > 0 ? 2 : 1) : 0;
              break;
            case 14:
              if(accessory_one_name == "NULL")
              {
                text = "Accessory 1";
              }
              else
              {
                text = accessory_one_name;
              }
              break;
            case 15:
              text = choices[15] + " " + to_string(evasion) + " (" + to_string(unmodified_evasion) + ") " + (evasion_difference != 0 ? (evasion_difference > 0 ? "+" + to_string(evasion_difference) : to_string(evasion_difference)) : " ");
              font_color = evasion_difference != 0 ? (evasion_difference > 0 ? 2 : 1) : 0;
              break;
            case 16:
              text = choices[16] + " " + to_string(magic_evasion) + " (" + to_string(unmodified_magic_evasion) + ") " + (magic_evasion_difference != 0 ? (magic_evasion_difference > 0 ? "+" + to_string(magic_evasion_difference) : to_string(magic_evasion_difference)) : " ");
              font_color = magic_evasion_difference != 0 ? (magic_evasion_difference > 0 ? 2 : 1) : 0;
              break;
            default:
              if(accessory_two_name == "NULL")
              {
                text = "Accessory 2";
              }
              else
              {
                text = accessory_two_name;
              }
              break;
          }
          switch(item_index)
          {
            case 2:
              if(weapon_name != "NULL")
              {
                world->render_item_icon(weapon_icon, x, y);
                current_pos += ICON_WIDTH;
              }
              break;
            case 5:
              if(shield_name != "NULL")
              {
                world->render_item_icon(shield_icon, x, y);
                current_pos += ICON_WIDTH;
              }
              break;
            case 8:
              if(helm_name != "NULL")
              {
                world->render_item_icon(helm_icon, x, y);
                current_pos += ICON_WIDTH;
              }
              break;
            case 11:
              if(armor_name != "NULL")
              {
                world->render_item_icon(armor_icon, x, y);
                current_pos += ICON_WIDTH;
              }
              break;
            case 14:
              if(accessory_one_name != "NULL")
              {
                world->render_item_icon(accessory_one_icon, x, y);
                current_pos += ICON_WIDTH;
              }
              break;
            case 17:
              if(accessory_two_name != "NULL")
              {
                world->render_item_icon(accessory_two_icon, x, y);
                current_pos += ICON_WIDTH;
              }
              break;
            default:
              break;
          }
          while(text != "")
          {
            switch(font_color)
            {
              case 1:
                world->render_letter("Red", current_pos, y, text[0]);
                break;
              case 2:
                world->render_letter("Green", current_pos, y, text[0]);
                break;
              default:
                world->render_letter("Text", current_pos, y, text[0]);
                break;
            }
            current_pos += FONT_TEXT_CHAR_WIDTHS[text[0]];
            text.erase(text.begin());
          }
        }
        x += m_spacing_x;
        ++item_index;
      }
      y += m_spacing_y;
      x = m_x;
    }

    if(display_start != 0 && m_selection->animation_is_visible() == true)
    {
      world->render_continue_arrow(m_x + m_spacing_x * m_selection->get_columns() / 2, m_y, true);
    }
    if(display_end * m_selection->get_columns() < static_cast<long>(choices.size()) && m_selection->animation_is_visible() == true)
    {
      world->render_continue_arrow(m_x + m_spacing_x * m_selection->get_columns() / 2, m_y + m_spacing_y * m_selection->get_display_rows(), false);
    }
  }
}

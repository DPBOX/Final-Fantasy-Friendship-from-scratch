#ifndef SELECTION_HPP
#define SELECTION_HPP

template <typename T>
void Selection<T>::rebuild_choices(const vector<T*> & data)
{
  m_choices.add(data);
}

template <typename T>
void Selection<T>::render_item(World* world, const string & font, const long & x, const long & y, const string & item_name) const{}

template <typename T>
void Selection<T>::update_input(World* world)
{
  m_continue_arrow_animation.update();

  if(m_show_cursor == true)
  {
    if(m_focus_x + m_focus_y * m_columns >= m_choices.get_list_size())
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
      if(m_focus_x + m_focus_y_temp * m_columns < m_choices.get_list_size())
      {
        if(m_focus_y_temp != m_focus_y)
        {
          world->play_global_sound("Cursor");
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
      if(m_focus_x + m_focus_y_temp * m_columns < m_choices.get_list_size())
      {
        if(m_focus_y_temp != m_focus_y)
        {
          world->play_global_sound("Cursor");
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
      if(m_focus_x_temp + m_focus_y * m_columns < m_choices.get_list_size())
      {
        if(m_focus_x_temp != m_focus_x)
        {
          world->play_global_sound("Cursor");
        }
        m_focus_x = max(m_focus_x - 1, static_cast<long>(0));
      }
    }

    if(IsKeyPressed(KEY_RIGHT) == true)
    {
      long m_focus_x_temp{min(m_focus_x + 1, m_columns - 1)};
      if(m_focus_x_temp + m_focus_y * m_columns < m_choices.get_list_size())
      {
        if(m_focus_x_temp != m_focus_x)
        {
          world->play_global_sound("Cursor");
        }
        m_focus_x = min(m_focus_x + 1, m_columns - 1);
      }
    }
    world->set_cursor_destination(m_x + m_spacing_x * m_focus_x, m_y + m_spacing_y * (m_focus_y - m_display_start));
    m_highlighted_item = m_focus_x + m_focus_y * m_columns;

    long display_start{m_display_start};
    long display_end{m_display_start + m_display_rows};
    if(display_start != 0 || display_end * m_columns < m_choices.get_list_size())
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

template <typename T>
void Selection<T>::render(World* world, const string & party_member_name, const vector<long> & equipment_stat_differences) const{}

template <typename T>
void Selection<T>::set_position(const long & x, const long & y)
{
  m_x = x;
  m_y = y;
}

template <typename T>
void Selection<T>::set_spacing_x(const long & text_area_width)
{
  m_spacing_x = text_area_width / m_columns;
}

template <typename T>
long Selection<T>::get_height() const
{
  return m_display_rows * TEXT_FONT_HEIGHT;
}

template <typename T>
string Selection<T>::c_get_options(World* world) const
{
  string menu_items{""};
  vector<string> choices{m_choices.get_list()};
  for(long i{0}; i < m_choices.get_list_size(); ++i)
  {
    menu_items += choices[i];
    if(i != m_choices.get_list_size() - 1)
    {
      menu_items += ", ";
    }
  }
  return menu_items;
}

template <typename T>
long Selection<T>::get_highlighted_item() const
{
  return m_highlighted_item;
}

template <typename T>
const T* Selection<T>::get_highlighted_item_obj() const
{
  return m_choices[m_highlighted_item];
}

template <typename T>
void Selection<T>::show_cursor()
{
  m_show_cursor = true;
}

template <typename T>
void Selection<T>::hide_cursor()
{
  m_show_cursor = false;
}

template <typename T>
bool Selection<T>::cursor_shown() const
{
  return m_show_cursor;
}

template <typename T>
void Selection<T>::show_menu()
{
  m_show_menu = true;
}

template <typename T>
void Selection<T>::hide_menu()
{
  m_show_cursor = false;
  m_show_menu = false;
}

template <typename T>
bool Selection<T>::menu_shown() const
{
  return m_show_menu;
}

#endif

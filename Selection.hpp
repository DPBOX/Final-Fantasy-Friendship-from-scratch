#ifndef SELECTION_HPP
#define SELECTION_HPP

template <typename T>
void Selection<T>::render_item(World* world, const long & font, const long & x, const long & y, const long & item_index) const{}

template <typename T>
void Selection<T>::update_input(World* world){}

template <typename T>
void Selection<T>::render(World* world, const string & party_member_name) const{}

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
string Selection<T>::c_get_options() const
{
  return "NULL";
}

template <typename T>
long Selection<T>::get_selected_item()
{
  if(m_show_cursor == true)
  {
    long selected_item{m_selected_item};
    m_selected_item = -1;
    return selected_item;
  }
  crash("Error: Tried to get the selected option in inactive selection menu \"" + c_get_options() + "\".");
  return -1;
}
  
template <typename T>
long Selection<T>::get_highlighted_item() const
{
  if(m_show_cursor == true && m_highlighted_item >= 0 && m_highlighted_item < static_cast<long>(m_choices.size()))
  {
    return m_highlighted_item;
  }
  if(m_highlighted_item < 0 || m_highlighted_item >= static_cast<long>(m_choices.size()))
  {
    crash("Error: Tried to highlight invalid option " + to_string(m_highlighted_item) + " in selection menu \"" + c_get_options() + "\".");
  }
  crash("Error: Tried to get the highlighted option in inactive selection menu \"" + c_get_options() + "\".");
  return -1;
}

template <typename T>
void Selection<T>::show_cursor()
{
  m_queue_show_cursor = true;
}

template <typename T>
void Selection<T>::hide_cursor()
{
  m_queue_show_cursor = false;
}

template <typename T>
bool Selection<T>::cursor_shown() const
{
  return m_show_cursor;
}

template <typename T>
void Selection<T>::show_menu()
{
  m_queue_show_menu = true;
}

template <typename T>
void Selection<T>::hide_menu()
{
  m_queue_show_cursor = false;
  m_queue_show_menu = false;
}

template <typename T>
bool Selection<T>::menu_shown() const
{
  return m_show_menu;
}

template <typename T>
void Selection<T>::on_click()
{
  m_selected_item = m_focus_x + m_focus_y * m_columns;
}

#endif
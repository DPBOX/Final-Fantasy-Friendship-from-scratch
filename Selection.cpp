#include "Main.h"
#include "UI.h"

template <>
void Selection<string>::render_item(World* world, const string & font, const long & x, const long & y, const string & item_name) const
{
  world->render_text(font, item_name, x, y);
}

template <>
void Selection<string>::update_input(World* world)
{
  m_continue_arrow_animation.update();

  if(m_render_mode == "Items")
  {
    m_choices.add(to_pointers(world->get_items()));
  }
  if(m_render_mode == "Key Items")
  {
    m_choices.add(to_pointers(world->get_key_items()));
  }
  if(m_render_mode == "Stats")
  {
    vector<string> choices{STAT_STRINGS};
    m_choices.add(to_pointers(choices));
  }

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

template <>
void Selection<string>::render(World* world, const string & party_member_name, const vector<long> & equipment_stat_differences) const
{
  if(m_show_menu == true)
  {
    long display_start{m_display_start};
    long display_end{m_display_start + m_display_rows};
    long x{m_x};
    long y{m_y};
    long item_index{display_start * m_columns};

    for(long i{display_start}; i < display_end; ++i)
    {
      for(long j{0}; j < m_columns; ++j)
      {
        if(item_index >= 0 && item_index < m_choices.get_list_size())
        {
          if(m_render_mode == "Normal")
          {
            render_item(world, "Text", x, y, *m_choices[item_index]);
          }
          else if(m_render_mode == "Items")
          {
            world->render_item(x, y, "Text", *m_choices[item_index], m_spacing_x);
          }
          else if(m_render_mode == "Key Items")
          {
            world->render_key_item(x, y, "Text", *m_choices[item_index]);
          }
          else if(m_render_mode == "Stats")
          {
            if(*m_choices[item_index] == "Weapon")
            {
              if(world->get_party_member_equipped_equipment(party_member_name, "Weapon") != "NULL")
              {
                world->render_equipment(x, y, "Text", world->get_party_member_equipped_equipment(party_member_name, "Weapon"), m_spacing_x, false);
              }
              else
              {
                render_item(world, "Text", x, y, *m_choices[item_index]);
              }
            }
            else if(*m_choices[item_index] == "Shield")
            {
              if(world->get_party_member_equipped_equipment(party_member_name, "Shield") != "NULL")
              {
                world->render_equipment(x, y, "Text", world->get_party_member_equipped_equipment(party_member_name, "Shield"), m_spacing_x, false);
              }
              else
              {
                render_item(world, "Text", x, y, *m_choices[item_index]);
              }
            }
            else if(*m_choices[item_index] == "Helm")
            {
              if(world->get_party_member_equipped_equipment(party_member_name, "Helm") != "NULL")
              {
                world->render_equipment(x, y, "Text", world->get_party_member_equipped_equipment(party_member_name, "Helm"), m_spacing_x, false);
              }
              else
              {
                render_item(world, "Text", x, y, *m_choices[item_index]);
              }
            }
            else if(*m_choices[item_index] == "Armor")
            {
              if(world->get_party_member_equipped_equipment(party_member_name, "Armor") != "NULL")
              {
                world->render_equipment(x, y, "Text", world->get_party_member_equipped_equipment(party_member_name, "Armor"), m_spacing_x, false);
              }
              else
              {
                render_item(world, "Text", x, y, *m_choices[item_index]);
              }
            }
            else if(*m_choices[item_index] == "Accessory 1")
            {
              if(world->get_party_member_equipped_equipment(party_member_name, "Accessory 1") != "NULL")
              {
                world->render_equipment(x, y, "Text", world->get_party_member_equipped_equipment(party_member_name, "Accessory 1"), m_spacing_x, false);
              }
              else
              {
                render_item(world, "Text", x, y, *m_choices[item_index]);
              }
            }
            else if(*m_choices[item_index] == "Accessory 2")
            {
              if(world->get_party_member_equipped_equipment(party_member_name, "Accessory 2") != "NULL")
              {
                world->render_equipment(x, y, "Text", world->get_party_member_equipped_equipment(party_member_name, "Accessory 2"), m_spacing_x, false);
              }
              else
              {
                render_item(world, "Text", x, y, *m_choices[item_index]);
              }
            }
            else
            {
              render_item(world, "Text", x, y, *m_choices[item_index]);
              world->render_stat(x, y, "Text", *m_choices[item_index], m_spacing_x, party_member_name, equipment_stat_differences);
            }
          }
          else
          {
            crash("Error: Invalid render mode \"m_render_mode\".");
          }
        }
        x += m_spacing_x;
        ++item_index;
      }
      y += m_spacing_y;
      x = m_x;
    }

    if(display_start != 0 && m_continue_arrow_animation.is_visible() == true)
    {
      world->render_continue_arrow(m_x + m_spacing_x * m_columns / 2.0, m_y, true);
    }
    if(display_end * m_columns < m_choices.get_list_size() && m_continue_arrow_animation.is_visible() == true)
    {
      world->render_continue_arrow(m_x + m_spacing_x * m_columns / 2.0, m_y + m_spacing_y * m_display_rows);
    }
  }
}

template <>
void Selection<Equipment>::render(World* world, const string & party_member_name, const vector<long> & equipment_stat_differences) const
{
  if(m_show_menu == true)
  {
    long display_start{m_display_start};
    long display_end{m_display_start + m_display_rows};
    long x{m_x};
    long y{m_y};
    long item_index{display_start * m_columns};

    for(long i{display_start}; i < display_end; ++i)
    {
      for(long j{0}; j < m_columns; ++j)
      {
        if(item_index >= 0 && item_index < m_choices.get_list_size())
        {
          if(m_render_mode == "Weapons")
          {
            if(world->can_use_equipment(party_member_name, m_choices[item_index]->get_name(), "Weapon"))
            {
              world->render_equipment(x, y, "Text", m_choices[item_index]->get_name(), m_spacing_x, true, m_choices[item_index]->get_equipped_by());
            }
            else
            {
              world->render_equipment(x, y, "Red", m_choices[item_index]->get_name(), m_spacing_x, true, m_choices[item_index]->get_equipped_by());
            }
          }
          else if(m_render_mode == "Shields")
          {
            if(world->can_use_equipment(party_member_name, m_choices[item_index]->get_name(), "Shield"))
            {
              world->render_equipment(x, y, "Text", m_choices[item_index]->get_name(), m_spacing_x, true, m_choices[item_index]->get_equipped_by());
            }
            else
            {
              world->render_equipment(x, y, "Red", m_choices[item_index]->get_name(), m_spacing_x, true, m_choices[item_index]->get_equipped_by());
            }
          }
          else if(m_render_mode == "Helms")
          {
            if(world->can_use_equipment(party_member_name, m_choices[item_index]->get_name(), "Helm"))
            {
              world->render_equipment(x, y, "Text", m_choices[item_index]->get_name(), m_spacing_x, true, m_choices[item_index]->get_equipped_by());
            }
            else
            {
              world->render_equipment(x, y, "Red", m_choices[item_index]->get_name(), m_spacing_x, true, m_choices[item_index]->get_equipped_by());
            }
          }
          else if(m_render_mode == "Armor")
          {
            if(world->can_use_equipment(party_member_name, m_choices[item_index]->get_name(), "Armor"))
            {
              world->render_equipment(x, y, "Text", m_choices[item_index]->get_name(), m_spacing_x, true, m_choices[item_index]->get_equipped_by());
            }
            else
            {
              world->render_equipment(x, y, "Red", m_choices[item_index]->get_name(), m_spacing_x, true, m_choices[item_index]->get_equipped_by());
            }
          }
          else if(m_render_mode == "Accessories")
          {
            if(world->can_use_equipment(party_member_name, m_choices[item_index]->get_name(), "Accessory"))
            {
              world->render_equipment(x, y, "Text", m_choices[item_index]->get_name(), m_spacing_x, true, m_choices[item_index]->get_equipped_by());
            }
            else
            {
              world->render_equipment(x, y, "Red", m_choices[item_index]->get_name(), m_spacing_x, true, m_choices[item_index]->get_equipped_by());
            }
          }
          else
          {
            crash("Error: Invalid render mode \"m_render_mode\".");
          }
        }
        x += m_spacing_x;
        ++item_index;
      }
      y += m_spacing_y;
      x = m_x;
    }

    if(display_start != 0 && m_continue_arrow_animation.is_visible() == true)
    {
      world->render_continue_arrow(m_x + m_spacing_x * m_columns / 2.0, m_y, true);
    }
    if(display_end * m_columns < m_choices.get_list_size() && m_continue_arrow_animation.is_visible() == true)
    {
      world->render_continue_arrow(m_x + m_spacing_x * m_columns / 2.0, m_y + m_spacing_y * m_display_rows);
    }
  }
}

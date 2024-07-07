#include "Main.h"
#include "Cursor.h"

Cursor::Cursor()
//Loads the cursor image graphic at startup.
{
  Image image{LoadImageFromMemory(".png", binary_Image_smolder_fly_right_png_start, reinterpret_cast<long>(&binary_Image_smolder_fly_right_png_size))};
  m_cursor = LoadTextureFromImage(image);
  UnloadImage(image);
}

Cursor::~Cursor()
//Unloads the image graphic at shutdown.
{
  UnloadTexture(m_cursor);
}

void Cursor::update()
{
  m_animation.update();
  if((m_start_x != m_end_x || m_start_y != m_end_y) && m_calculated_velocity == true)
  {
    m_x += m_vx;
    m_y += m_vy;

    // If it has reached its destination,
    if((m_vx >= 0 && m_vy >= 0 && m_x >= m_end_x && m_y >= m_end_y) ||
       (m_vx < 0 && m_vy >= 0 && m_x <= m_end_x && m_y >= m_end_y) ||
       (m_vx >= 0 && m_vy < 0 && m_x >= m_end_x && m_y <= m_end_y) ||
       (m_vx < 0 && m_vy < 0 && m_x <= m_end_x && m_y <= m_end_y))
    {
      m_x = m_end_x;
      m_y = m_end_y;
      m_start_x = m_end_x;
      m_start_y = m_end_y;
      m_calculated_velocity = false;
    }
  }
}

void Cursor::set_destination(const long & end_x, const long & end_y)
{
  m_destination_set = true;
  if(m_calculated_velocity == false)
  {
    m_end_x = end_x + CURSOR_PADDING_X;
    m_end_y = end_y + CURSOR_PADDING_Y;

    if(m_start_x != m_end_x || m_start_y != m_end_y)
    {
      m_calculated_velocity = true;
      if(m_start_x == m_end_x)
      {
        m_vx = 0;
      }
      else
      {
        m_vx = (static_cast<double>(m_end_x) - static_cast<double>(m_start_x)) / CURSOR_MOVE_TIME / static_cast<double>(SCREEN_FPS);
      }
      if(m_start_y == m_end_y)
      {
        m_vy = 0;
      }
      else
      {
        m_vy = (static_cast<double>(m_end_y) - static_cast<double>(m_start_y)) / CURSOR_MOVE_TIME / static_cast<double>(SCREEN_FPS);
      }
    }
  }
}

void Cursor::finish()
//Moves cursor offscreen.
{
  if(m_destination_set == false)
  {
    set_destination(CURSOR_START_X, CURSOR_START_Y);
  }
  m_destination_set = false;
}

void Cursor::render() const
{
  DrawTexturePro(m_cursor, Rectangle{static_cast<float>(m_animation.get_frame() * CURSOR_WIDTH), 0, CURSOR_WIDTH, static_cast<float>(m_cursor.height)}, Rectangle{static_cast<float>(m_x), static_cast<float>(m_y), CURSOR_WIDTH, static_cast<float>(m_cursor.height)}, Vector2{0, 0}, 0, Color{0xFF, 0xFF, 0xFF, 0xFF});
}

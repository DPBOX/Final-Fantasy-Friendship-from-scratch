#include "Main.h"
#include "Animation.h"

void Animation::update()
{
  // Count frames then change the animation frame when the frame count reaches the animation speed
  ++m_time;
  if(m_time == m_speed)
  {
    ++m_index;
    m_time = 0;
    if(m_index == static_cast<long>(m_frames.size()))
    {
      if(m_loop == true)
      {
        m_index = 0;
      }
      else
      {
        --m_index;
      }
    }
  }
}

void Animation::set_frames(const vector<long> & frames)
{
  if(frames != m_frames)
  {
    m_frames = frames;
    m_index = min(m_index, static_cast<long>(frames.size()) - 1);
  }
}

long Animation::get_frame() const
{
  return m_frames[m_index];
}

long Animation::get_frames() const
{
  return m_frames.size();
}

void Animation::set_loop(const bool & loop)
{
  m_loop = loop;
}

bool Animation::is_finished() const
{
  return m_loop == false && m_index == static_cast<long>(m_frames.size()) - 1;
}
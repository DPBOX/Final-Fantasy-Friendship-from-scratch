#include "Main.h"
#include "LTimer.h"

void LTimer::start()
{
  m_started = true;
  m_paused = false;
  m_start_ticks = GetTime();
  m_paused_ticks = 0;
}

void LTimer::stop()
{
  m_started = false;
  m_paused = false;
  m_start_ticks = 0;
  m_paused_ticks = 0;
}

void LTimer::pause()
{
  if(m_started == true && m_paused == false)
  {
    m_paused = true;
    m_paused_ticks = GetTime() - m_start_ticks;
    m_start_ticks = 0;
  }
}

void LTimer::unpause()
{
  if(m_started == true && m_paused == true)
  {
    m_paused = false;
    m_start_ticks = GetTime() - m_paused_ticks;
    m_paused_ticks = 0;
  }
}

double LTimer::get_ticks() const
{
  double time = 0;
  if(m_started == true)
  {
    if(m_paused == true)
    {
      time = m_paused_ticks;
    }
    else
    {
      time = GetTime() - m_start_ticks;
    }
  }
  return time;
}

bool LTimer::is_started() const
{
  return m_started;
}

bool LTimer::is_paused() const
{
  return m_paused;
}

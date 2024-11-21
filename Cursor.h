//Defines cursor processing.

#ifndef CURSOR_H
#define CURSOR_H
#include "Animation.h"

// The cursor is always displayed. When it's done being used, finished() is called, which simply calls set_destination() to a point offscreen.

class Cursor
{
  public:
    explicit Cursor();
    Cursor(const Cursor & obj) = delete;
    Cursor & operator =(const Cursor & obj) = delete;
    ~Cursor();

    void update();
    void set_destination(const long & end_x, const long & end_y);
    void finish();
    void render() const;
  private:
    long m_start_x{CURSOR_START_X};
    long m_start_y{CURSOR_START_Y};
    double m_x{CURSOR_START_X};
    double m_y{CURSOR_START_Y};
    long m_end_x{CURSOR_START_X};
    long m_end_y{CURSOR_START_Y};
    double m_vx{0};
    double m_vy{0};
    bool m_calculated_velocity{false};
    bool m_destination_set{false};
    Texture2D m_cursor{};
    Animation m_animation{CURSOR_ANIM, 0, true, CURSOR_ANIMATION_SPEED};
};

#endif

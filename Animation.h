#ifndef ANIMATION_H
#define ANIMATION_H

class Animation
{
  public:
    explicit Animation(const vector<long> & frames, const long & start_frame, const bool & loop, const long & speed) : m_frames(frames), m_index(start_frame), m_loop(loop), m_speed(speed){}
    void update();
    void set_frames(const vector<long> & frames);
    long get_frame() const;
    long get_frames() const;
    void set_loop(const bool & loop);
    bool is_finished() const;
  private:
    vector<long> m_frames{};
    long m_index{0};
    bool m_loop{true};
    long m_speed{1};
    long m_time{0};
};

#endif
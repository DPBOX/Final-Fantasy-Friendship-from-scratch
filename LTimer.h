#ifndef LTIMER_H
#define LTIMER_H

class LTimer
{
  public:
    //Initializes variables
    explicit LTimer(){}

    //The various clock actions
    void start();
    void stop();
    void pause();
    void unpause();

    //Gets the timer's time
    long get_ticks() const;

    //Checks the status of the timer
    bool is_started() const;
    bool is_paused() const;

  private:
    //The clock time when the timer started
    double m_start_ticks{0};

    //The ticks stored when the timer was paused
    double m_paused_ticks{0};

    //The timer status
    bool m_paused{false};
    bool m_started{false};
};

#endif

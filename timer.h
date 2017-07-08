#ifndef __TIMER__
#define __TIMER__

// Timer Class
class Timer
{

  private:

    // Timer
    unsigned long timer = 0;

    // Time out after this number of ticks
    unsigned long time_out_ticks = 0;

  public:

    // Begin timer
    void begin(unsigned long ticks);

    // Increment timer
    void increment();

    // Reset timer
    void reset();

    // Reset event
    void (* reset_event)();

    // Time out event
    void (* time_out_event)();

};

extern Timer timer;

#endif

#include <Arduino.h>

// Include Timer Header
#include "timer.h"

void Timer::begin(unsigned long ticks)
{
  time_out_ticks = ticks;
}

void Timer::increment()
{

  // Timer is not set
  if (time_out_ticks == 0) return;

  if (timer < time_out_ticks) timer ++;
  if (timer == time_out_ticks)
  {
    time_out_event();
    timer = 0;
  }
  
}

void Timer::reset()
{
  reset_event();
  timer = 0;
}

Timer timer;

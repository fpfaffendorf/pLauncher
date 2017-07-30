#include <Arduino.h>

// Include Timer Header
#include "timer.h"

void Timer::begin(unsigned long ticks)
{
  time_out_ticks = ticks;
}

bool Timer::increment()
{

  // Timer is not set
  if (time_out_ticks == 0) return false;

  if (timer < time_out_ticks) timer ++;
  if (timer == time_out_ticks)
  {
    time_out_event();
    return true;
  }

  return false;
  
}

void Timer::reset()
{
  reset_event();
  timer = 0;
}

Timer timer;

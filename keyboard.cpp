#include <Arduino.h>

// Include Keyboard Header
#include "keyboard.h"

// Include Application Header
#include "application.h"
// Include Timer Library
#include "timer.h"

// Keyboard begin
void Keyboard::begin(void (* keyboard_reset_event), void (* keyboard_time_out_event))
{
  // Use external reference for Analog Input
  analogReference(EXTERNAL);
  // Timer time out ticks
  timer.begin(BACKLIGHT_TIMER_TIME_OUT_TICKS);
  // Timer reset event
  timer.reset_event = keyboard_reset_event;
  // Timer time out event
  timer.time_out_event = keyboard_time_out_event;  
}
    
// Keyboard scan
unsigned char Keyboard::scan()
{

  // Loop until a key is pressed
  for (;;)
  {
    // Analog read keyboard
    unsigned int ar = analogRead(KEYBOARD_AIO);
    if (ar > KEYBOARD_OFF)
    {
      ar = analogRead(KEYBOARD_AIO);
      if (ar > KEYBOARD_OFF)
      {
        // Scan keyboard
        for (unsigned char i = 0; i < KEYBOARD_NUMBER_BUTTONS; i ++)
        {
          // Analog read value between button value delta, return button index
          if ((ar >= buttons[i] - KEYBOARD_DELTA) && (ar <= buttons[i] + KEYBOARD_DELTA)) 
          {
            // Return button id on key up
            while (analogRead(KEYBOARD_AIO) > KEYBOARD_OFF);
            // Reset timer
            timer.reset();
            // Return key pressed
            return i + 1;
          }
        }   
      }
    }
    else
    {
      // Increment timer
      timer.increment();
    }

  }
  
}        

Keyboard keyboard;

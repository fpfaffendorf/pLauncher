#include <Arduino.h>

// Include Keyboard Header
#include "keyboard.h"

// Include Screen Library
#include "screen.h"

// Keyboard begin
void Keyboard::begin(unsigned char aio)
{
  // Use external reference for Analog Input
  analogReference(EXTERNAL);
  // Store keyboard AIO
  aio = aio;
}
    
// Keyboard scan
unsigned char Keyboard::scan()
{

  // Loop until a key is pressed
  for (;;)
  {

    // Analog read keyboard
    unsigned int ar = analogRead(aio);
    if (ar > KEYBOARD_OFF)
    {
        ar = analogRead(aio);
        if (ar > KEYBOARD_OFF)
        {
          // Scan keyboard
          for (unsigned char i = 0; i < KEYBOARD_NUMBER_BUTTONS; i ++)
          {
            // Analog read value between button value delta, return button index
            if ((ar >= buttons[i] - KEYBOARD_DELTA) && (ar <= buttons[i] + KEYBOARD_DELTA)) 
            {
              // Return button id on key up
              while (analogRead(aio) > KEYBOARD_OFF);
              #ifndef DEBUG_KEYBOARD
              delay(200);
              return i + 1;
              #endif
              #ifdef DEBUG_KEYBOARD
              Screen screen;
              screen.print("Pressed Button", 5, 10);
              screen.print(String(i + 1), 5, 20);
              screen.print(String(ar), 5, 30);
              screen.flush();
              #endif          
            }
          }   
        }
    }

  }
  
}        

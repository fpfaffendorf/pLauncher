#ifndef __KEYBOARD__
#define __KEYBOARD__

// Keys
#define KEYBOARD_NONE  0
#define KEYBOARD_7     1
#define KEYBOARD_8     2
#define KEYBOARD_9     3
#define KEYBOARD_MENU  4
#define KEYBOARD_4     5
#define KEYBOARD_5     6
#define KEYBOARD_6     7
#define KEYBOARD_ESC   8
#define KEYBOARD_1     9
#define KEYBOARD_2     10
#define KEYBOARD_3     11
#define KEYBOARD_CLR   12
#define KEYBOARD_0     13
#define KEYBOARD_DOT   14
#define KEYBOARD_SIGN  15
#define KEYBOARD_ENTER 16

// Configuration
#define KEYBOARD_NUMBER_BUTTONS 16
#define KEYBOARD_DELTA          10
#define KEYBOARD_OFF            150

// Debug mode
// #define DEBUG_KEYBOARD

// Keyboard Class 
class Keyboard
{

  private:
  
    // Buttons analog values
    unsigned int buttons[KEYBOARD_NUMBER_BUTTONS] = { 1023, 930, 854, 799, 678, 636, 599, 571, 518, 493, 471, 453, 411, 330, 276, 238 };

    // AIO associated to keyboard
    unsigned char aio;
  
  public:

    // Begin keyboard
    void begin(unsigned char aio);
    
    // Scan button pressed
    unsigned char scan();

};

#endif

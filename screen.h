#ifndef __SCREEN__
#define __SCREEN__

// Screen LCD ICSP PIOs
#define SCREEN_SCK    12
#define SCREEN_MOSI   11
#define SCREEN_CS     10

#define SCREEN_BACKLIGHT_AIO            3
#define SCREEN_DEFAULT_BACKLIGHT_LEVEL  2

// U8glib Header
#include "U8glib.h"

// Line struct
struct Line 
{

  int x;
  int y;
  String line;
  
};

// Screen Class
class Screen
{

  private:

    Line lines[10];

    int current_line = 0;

    unsigned char current_backlight_level = SCREEN_DEFAULT_BACKLIGHT_LEVEL;
    unsigned char last_positive_backlight_level = SCREEN_DEFAULT_BACKLIGHT_LEVEL;
  
  public:

    // Begin screen
    void begin();
    
    // Clear screen
    void clear();

    // Print string on x, y position 
    void print(String string, int x, int y);

    // Loading ...
    void loading();

    // Flush output to screen
    void flush();

    // Screen backlight level [0..9]
    void backlight_level(unsigned char level);

    // Get current screen backlight level
    unsigned char get_backlight_level();

    // Get last positive screen backlight level
    unsigned char get_last_positive_backlight_level();

};

extern Screen screen;

#endif

#ifndef __SCREEN__
#define __SCREEN__

// Screen LCD ICSP PIOs
#define SCREEN_SCK    12
#define SCREEN_MOSI   11
#define SCREEN_CS     10

#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT  64

#define SCREEN_BACKLIGHT_PWM            3
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

// Grid enum
enum Grid
{
  options_11,
  argument,
  list
};

// Screen Class
class Screen
{

  private:

    unsigned char current_backlight_level = SCREEN_DEFAULT_BACKLIGHT_LEVEL;
    unsigned char last_positive_backlight_level = SCREEN_DEFAULT_BACKLIGHT_LEVEL;
  
  public:

    // Begin screen
    void begin();
    
    // Clear screen
    void clear();

    // Print string on x, y position 
    void print(Line* lines, int number_lines, Grid grid);

    // Loading screen ...
    void loading();

    // Renders an xbm bitmap 
    void render(String xbm_command);

    // Screen backlight level [0..9]
    void backlight_level(unsigned char level);

    // Get current screen backlight level
    unsigned char get_backlight_level();

    // Get last positive screen backlight level
    unsigned char get_last_positive_backlight_level();

};

extern Screen screen;

#endif

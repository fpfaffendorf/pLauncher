#ifndef __SCREEN__
#define __SCREEN__

// Screen LCD ICSP PIOs
#define SCREEN_SCK 12
#define SCREEN_MOSI 11
#define SCREEN_CS 10

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

    Line lines[20];
    int currentLine = 0;
  
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
    
};

#endif

#include <Arduino.h>

// Include Application Header
#include "application.h"

// Include Screen Header
#include "screen.h"

// U8GLIB 
U8GLIB_ST7920_128X64_1X u8g(SCREEN_SCK, SCREEN_MOSI, SCREEN_CS);

// Screen begin
void Screen::begin()
{

  u8g.setRot180();
  u8g.setColorIndex(1);
  u8g.setFont(u8g_font_4x6);
  
}

// Screen clear    
void Screen::clear()
{

  u8g.firstPage();  
  do { } while( u8g.nextPage() );

  currentLine = 0;

}

// Screen print
void Screen::print(String string, int x, int y)
{

  lines[currentLine].x = x;
  lines[currentLine].y = y;
  lines[currentLine].line = string;

  currentLine += 1;

}

void Screen::loading()
{
  print("Loading ...", 5, 10);
  print(APPLICATION_INFO, 5, 20);
  flush();  
}

// Screen flush output
void Screen::flush()
{

  u8g.firstPage();  
  do {
    for (int i = 0; i < currentLine; i++)
    {
      int l = lines[i].line.length() + 1;
      char stringArray[l];
      lines[i].line.toCharArray(stringArray, l);
      u8g.drawStr(lines[i].x, lines[i].y, stringArray);  
    }    
  } while( u8g.nextPage() );

  currentLine = 0;
  
}


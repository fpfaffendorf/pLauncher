#include <Arduino.h>

// Include Screen Header
#include "screen.h"

// Include Application Header
#include "application.h"

// U8GLIB 
U8GLIB_ST7920_128X64_1X u8g(SCREEN_SCK, SCREEN_MOSI, SCREEN_CS);

// Screen begin
void Screen::begin()
{

  u8g.setRot180();
  u8g.setColorIndex(1);
  u8g.setFont(u8g_font_4x6);

  pinMode(SCREEN_BACKLIGHT_AIO, OUTPUT);
  backlight_level(SCREEN_DEFAULT_BACKLIGHT_LEVEL);

}

// Screen clear    
void Screen::clear()
{

  u8g.firstPage();  
  do { } while( u8g.nextPage() );

  current_line = 0;

}

// Screen print
void Screen::print(String string, int x, int y)
{

  lines[current_line].x = x;
  lines[current_line].y = y;
  lines[current_line].line = string;

  current_line += 1;

}

void Screen::loading()
{
  print("Loading ...", 5, 10);
  print(APPLICATION_INFO, 5, 20);
  print("Developed by", 5, 30);
  print(" Federico Pfaffendorf", 5, 40);
  flush();  
}

// Screen flush output
void Screen::flush()
{

  u8g.firstPage();  
  do {
    for (int i = 0; i < current_line; i++)
    {
      int l = lines[i].line.length() + 1;
      char stringArray[l];
      lines[i].line.toCharArray(stringArray, l);
      u8g.drawStr(lines[i].x, lines[i].y, stringArray);  
    }    
  } while (u8g.nextPage());

  current_line = 0;
  
}

void Screen::backlight_level(unsigned char level)
{
  if (level > 9) return;
  if (level != 0) {
    last_positive_backlight_level = level;
  }
  analogWrite(SCREEN_BACKLIGHT_AIO, level * 28);
  current_backlight_level = level;
}

unsigned char Screen::get_backlight_level()
{
  return current_backlight_level;
}

unsigned char Screen::get_last_positive_backlight_level()
{
  return last_positive_backlight_level;
}

Screen screen;

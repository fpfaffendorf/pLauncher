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
 
  backlight_level(SCREEN_DEFAULT_BACKLIGHT_LEVEL);

}

// Screen clear    
void Screen::clear()
{

  u8g.firstPage();  
  do { } while( u8g.nextPage() );

}

// Screen print
void Screen::print(Line* lines, int number_lines, Grid grid)
{

  u8g.firstPage();  
  do {
    for (int i = 0; i < number_lines; i++)
    {
      int l = lines[i].line.length() + 1;
      char stringArray[l];
      lines[i].line.toCharArray(stringArray, l);
      u8g.drawStr(lines[i].x, lines[i].y, stringArray);
    }    
    u8g.drawFrame(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    if ((grid == Grid::options_11) || (grid == Grid::argument) || (grid == Grid::list))
    {
      for (int i = 13; i <= 53; i += 10)
      {
        u8g.drawHLine(0, i, SCREEN_WIDTH);
        if (grid == Grid::argument) i = 255;
      } 
      if (grid == Grid::options_11)
      {
        u8g.drawVLine(10, 14, SCREEN_HEIGHT);
        u8g.drawVLine(SCREEN_WIDTH / 2, 14, SCREEN_HEIGHT);
        u8g.drawVLine(SCREEN_WIDTH / 2 + 10, 14, SCREEN_HEIGHT);
      }
    }
  } while (u8g.nextPage());
  
}

void Screen::loading()
{
  u8g.firstPage();  
  do {
    u8g.drawStr(3, 61, "Loading ...");    
  } while (u8g.nextPage());
}

void Screen::render(String xbm_command)
{
  u8g.firstPage();  
  do {
    unsigned char x, y = 0;
    Process process;
    process.runShellCommand(xbm_command);
    while (process.running());
    while (process.available() > 0) {
      unsigned char c = process.read();
      for(unsigned char i = 0; i <= 7; i++)
      {
        if ((c & (1 << i)) > 0) u8g.drawPixel(x, y);         
        x++;
      }
      if (x >= SCREEN_WIDTH) 
      {
        x = 0;
        y++;
      }
    }        
  } while(u8g.nextPage());
}

void Screen::backlight_level(unsigned char level)
{
  if (level > 9) return;
  if (level != 0) {
    last_positive_backlight_level = level;
  }
  analogWrite(SCREEN_BACKLIGHT_PWM, level * 28);
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

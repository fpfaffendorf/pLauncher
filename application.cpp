#include <Arduino.h>

// Include Application Header
#include "application.h"

// Include Keyboard Library
#include "keyboard.h"
// Include Screen Library
#include "screen.h"
// Include Timer Library
#include "timer.h"

// Application Begin
void Application::begin()
{
  // Begin keyboard
  keyboard.begin(keyboard_reset_event, keyboard_time_out_event);
  // Begin screen
  screen.begin();
  // Loading screen 
  screen.loading();
  // Begin bridge connection
  Bridge.begin();
  // Begin serial communication
  // Serial.begin(9600);
  // 1 Second to initialize Bridge and Serial Communication
  delay(1000); 
}

void Application::main()
{
  // If there is a program to excecute, proceed
  if (program_to_execute != "")
  {
    execute();
    programs_page = 1;
    programs_next_page = false;
  }   
  else
  {
    // If program list next page was requested, proceed
    if (programs_next_page) list_programs();   
    // Otherwise, show menu
    else {
      programs_page = 1;
      menu();
    }    
  }
}

void Application::menu()
{

  // Print screen menu options
  Line lines[4];
  lines[0].x = 3; lines[0].y = 9; lines[0].line = "Main Menu";
  lines[1].x = 5; lines[1].y = 21; lines[1].line = "1 Programs";
  lines[2].x = 5; lines[2].y = 31; lines[2].line = "2 Config.";
  lines[3].x = 5; lines[3].y = 41; lines[3].line = "3 Backlight";
  screen.print(lines, 4, Grid::options_11);
   
  // Scan for button pressed
  unsigned char button = keyboard.scan();    
  switch (button)
  {
    // Button "1" pressed
    case KEYBOARD_1:
    {
      // Get program to execute
      current_directory = "programs";
      list_programs();
      break;
    }     
    // Button "2" pressed
    case KEYBOARD_2:
    {
      // Get configuration program to execute
      current_directory = "configuration";
      list_programs();
      break;
    }     
    // Button "3" pressed
    case KEYBOARD_3:
    {
      // Backlight screen configuration
      screen_backlight();
      break;
    }     
  }   
}

void Application::list_programs()
{
  // No next page for now
  programs_next_page = false;

  // Loading Screen
  screen.loading();

  // Lines to display on screen
  Line lines[11];

  // Print title
  String title = current_directory;
  title[0] = title[0] - 32;
  lines[0].x = 3; lines[0].y = 9; lines[0].line = title;
  
  // Run ls command and wait for it to end
  Process process;    
  process.runShellCommand("cd /root/" + current_directory + "; ls -1 *.py | head -n" + (programs_page * 9) + " | tail -n9");
  while (process.running());
  String string_process = process.readString();

  // Local variables necessary to parse and display menu options
  unsigned char option = 1;
  unsigned char x = 5;
  unsigned char y = 21;
  String string_parse = "";
  String programs_array[9];
  
  // Read output, parse, store in the program list and print screen
  for (int i = 0; i <= string_process.length(); i++)
  {
    if (string_process[i] == '\n')
    {
      // Change column and restart row if option is 6
      if (option == 6) { x = 69; y = 21; }
      // Store program full path in programs array
      programs_array[option - 1] = current_directory + "/" + string_parse;
      // Format menu option
      string_parse.replace(".py", "");
      string_parse.replace("-", " ");
      string_parse[0] = string_parse[0] - 32;     
      lines[option].x = x; lines[option].y = y; lines[option].line = String(option) + " " + string_parse;
      // Increment row      
      y += 10;
      // If option number 9 show next page option
      if (option++ == 9) {
        lines[option].x = 69; lines[option].y = 61; lines[option].line = "0 Next Page";
        break;
      }        
      string_parse = "";
    }
    else
    {
      string_parse += string_process[i];    
    }
  }      
  
  // Print screen output
  screen.print(lines, 11, Grid::options_11);

  // Scan for button pressed
  unsigned char button = keyboard.scan();   

  // Return program to be executed based on valid key pressed
  for (unsigned char i = 0; i < option; i++) if (button == keyboard.numeric_buttons[i]) program_to_execute = programs_array[i-1];

  // If button 0 and more than 10 options go to next page
  if ((button == KEYBOARD_0) && (option >= 10)) { 
    programs_page ++; 
    programs_next_page = true;
    program_to_execute = "";  
  } 
       
}

void Application::execute()
{

  // Quit if no program was specified
  if (program_to_execute == "") return;

  // Loading Screen
  screen.loading();

  // Get necessary parameters to execute this program
  Process process;      
  process.runShellCommand("/usr/bin/python /root/" + program_to_execute + " --help");
  while (process.running());
  String string_process = process.readString();
  String string_parse;
  String arguments;
  unsigned char key;
  bool image = false;
  for (int i = 0; i <= string_process.length(); i++)
  {
    if (string_process[i] == '\n')
    {
      if (string_parse == "IMG") image = true;
      else if (string_parse == "TXT") image = false;
      else
      {
        arguments += capture_numeric_argument(string_parse) + " ";      
      }
      string_parse = "";      
    }
    else
    {
      string_parse += string_process[i];    
    }
  }  

  do {

    // Loading Screen
    screen.loading();

    // If result is an image, render
    if (image)
    {
      screen.render("/usr/bin/python /root/" + program_to_execute + " " + arguments);     
    }
    // If result is text, show result as a grid
    else
    {
    
      // Lines
      Line lines[10];
  
      // Result title
      lines[0].x = 3; lines[0].y = 9; lines[0].line = "Result";
  
      // Execute the program with the given arguments
      process.runShellCommand("/usr/bin/python /root/" + program_to_execute + " " + arguments);
      while (process.running());
      String output = process.readString();
      String output_line;
      unsigned char y = 21;
      unsigned char line = 1;
      // Print the output line by line
      for (int i = 0; i <= output.length(); i++)
      {
        if (output[i] == '\n')
        {
          lines[line].x = 3; lines[line].y = y; lines[line].line = output_line;
          y += 10;
          line ++;
          output_line = "";
        }
        else
        {
          output_line += output[i];
        }
      } 
  
      // Print screen output
      screen.print(lines, 10, Grid::list);       

    }

    // Capture Key
    key = keyboard.scan();
  
  // If keypressed is ENTER repeat the execution with same arguments
  } while (key == KEYBOARD_ENTER);

  // If ESC Key was pressed execute same program from zero
  if (key != KEYBOARD_ESC)
  {
    current_directory = "";
    program_to_execute = "";    
  }

}

String Application::capture_numeric_argument(String argument_title)
{

  String argument = "";
  bool dot = false;

  // Lines
  Line lines[2];

  // Title
  lines[0].x = 3; lines[0].y = 9; lines[0].line = argument_title;
  lines[1].x = 3; lines[1].y = 21; 

  screen.print(lines, 2, Grid::argument);       

  // Scan for button pressed
  for(;;)
  {
    unsigned char button = keyboard.scan();    

    for (unsigned char i = 0; i <= 9; i++) if (button == keyboard.numeric_buttons[i]) argument += String(i);   
    if (button == KEYBOARD_DOT) 
    {
      if (!dot) argument += '.';
      dot = true;
    } else if (button == KEYBOARD_CLR) 
    {
      argument = "";
      dot = false;
    }
    else if (button == KEYBOARD_SIGN) {
      if (argument.length() == 0) argument = "-";
      else if (argument[0] == '-') argument = argument.substring(1, argument.length());
           else argument = "-" + argument; 
    }
    else if ((button == KEYBOARD_ENTER) && (argument != "")) return argument;

    lines[1].line = argument;

    screen.print(lines, 2, Grid::argument);       

  }  

}

// Set backlight level screen
void Application::screen_backlight()
{
  String level = capture_numeric_argument("Backlight Level: [0..9]");
  byte byte_level = SCREEN_DEFAULT_BACKLIGHT_LEVEL;
  if (level.length() == 1) byte_level = level[0] - 48;  
  screen.backlight_level(byte_level);
}

// Restore backlight to last positive backlight level on key pressed
static void Application::keyboard_reset_event()
{
  screen.backlight_level(screen.get_last_positive_backlight_level());
}

// Turn off backlight on keyboard timer time out
static void Application::keyboard_time_out_event()
{
  screen.backlight_level(0);
}

Application application;

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

  // 1 Second to initialize Bridge and Serial Communication
  delay(1000);
  
}

static void Application::menu()
{

  // Print screen options
  screen.print("1- Programs", 5, 10);
  screen.print("2- Configuration", 5, 20);
  screen.print("3- Screen backlight", 5, 30);  
  screen.flush();
  
  // Scan for button pressed
  unsigned char button = keyboard.scan();    
  programs_page = 0;
  switch (button)
  {
    // Button "1" pressed
    case KEYBOARD_1:
    {
      list_programs("programs");
      break;
    }     
    // Button "2" pressed
    case KEYBOARD_2:
    {
      list_programs("configuration");
      break;
    }     
    // Button "3" pressed
    case KEYBOARD_3:
    {
      screen_backlight();
      break;
    }     
  }
  
}

static void Application::list_programs(String directory)
{

  // Loading Screen
  screen.loading();

  // Run ls command
  process.runShellCommand("cd /root/" + directory + "; ls -1 *.py");

  // Do nothing until the process finishes
  while (process.running());

  // Read output, parse, store in the program list and print screen
  String string = process.readString();
  String string_parse;
  unsigned char option = 1;
  unsigned char parsed_options = 0;
  unsigned char y = 10;
  String programs_array[5];
  for (int i = 0; i <= string.length(); i++)
  {
    if (string[i] == '\n')
    {
      parsed_options ++;
      if (parsed_options >= programs_page * MAX_NUMBER_PROGRAMS)
      {
        programs_array[option - 1] = directory + "/" + string_parse;
        screen.print(format_program_option(option, string_parse), 5, y);  
        y += 10;
        option++;
        if (option == MAX_NUMBER_PROGRAMS) {
          screen.print(format_program_option(option, "Next Page ..."), 5, y);
          break;
        }        
      }
      string_parse = "";
    }
    else
    {
      string_parse += string[i];    
    }
  }  
  // Flush screen output
  screen.flush();

  // Scan for button pressed
  unsigned char button = keyboard.scan();   

  // Button (Number) pressed
       if ((button == KEYBOARD_1) && (option >= 1)) execute(programs_array[0]);
  else if ((button == KEYBOARD_2) && (option >= 2)) execute(programs_array[1]);
  else if ((button == KEYBOARD_3) && (option >= 3)) execute(programs_array[2]);
  else if ((button == KEYBOARD_4) && (option >= 4)) execute(programs_array[3]);
  else if ((button == KEYBOARD_5) && (option >= 5)) execute(programs_array[4]);
  else if ((button == KEYBOARD_6) && (option >= 6)) { programs_page ++; list_programs(directory); }
  
}

static String Application::format_program_option(unsigned char option, String title)
{
    String s = "";
    s += ((char)(option + 48));
    s += "- ";
    title.replace(".py", "");
    title.replace("-", " ");
    title[0] = title[0] - 32;
    s += title;
    return  s;
}

static void Application::execute(String program)
{

  if (program == "") return;

  screen.loading();

  // Get necessary parameters to execute this program
  process.runShellCommand("/usr/bin/python /root/" + program + " --help");
  while (process.running());
  String string = process.readString();
  String string_parse;
  String arguments;
  for (int i = 0; i <= string.length(); i++)
  {
    if (string[i] == '\n')
    {
      arguments += capture_argument(string_parse) + " ";      
      string_parse = "";      
    }
    else
    {
      string_parse += string[i];    
    }
  }  

  do {

    // Loading Screen
    screen.loading();
    
    // Execute the program with the given arguments
    process.runShellCommand("/usr/bin/python /root/" + program + " " + arguments);
    while (process.running());
    String output = process.readString();
    unsigned char y = 10;
    String output_line;
    // Print the output line by line
    for (int i = 0; i <= output.length(); i++)
    {
      if (output[i] == '\n')
      {
        screen.print(output_line, 5, y);
        y += 10;
        output_line = "";
      }
      else
      {
        output_line += output[i];
      }
    } 
    screen.flush();       
  
    // If Keypressed is ENTER repeat the execution with same arguments
  } while (keyboard.scan() == KEYBOARD_ENTER);

}

static String Application::capture_argument(String argument_title)
{

  String argument = "";
  bool dot = false;

  screen.print(argument_title, 5, 10);
  screen.flush();       

  // Scan for button pressed
  for(;;)
  {
    unsigned char button = keyboard.scan();    
    if (button == KEYBOARD_1) argument += '1';
    else if (button == KEYBOARD_2) argument += '2';
    else if (button == KEYBOARD_3) argument += '3';
    else if (button == KEYBOARD_4) argument += '4';
    else if (button == KEYBOARD_5) argument += '5';
    else if (button == KEYBOARD_6) argument += '6';
    else if (button == KEYBOARD_7) argument += '7';
    else if (button == KEYBOARD_8) argument += '8';
    else if (button == KEYBOARD_9) argument += '9';
    else if (button == KEYBOARD_0) argument += '0';
    else if (button == KEYBOARD_DOT) 
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
    else if (button == KEYBOARD_ENTER) return argument;
    // Print current value
    screen.print(argument_title, 5, 10);
    screen.print(argument, 5, 20);
    screen.flush();       
  }  

}

static void Application::screen_backlight()
{
  String level = capture_argument("Backlight Level: [0..9]");
  byte byte_level = SCREEN_DEFAULT_BACKLIGHT_LEVEL;
  if (level.length() == 1) byte_level = level[0] - 48;  
  screen.backlight_level(byte_level);
}

static void Application::keyboard_reset_event()
{
  screen.backlight_level(screen.get_last_positive_backlight_level());
}

static void Application::keyboard_time_out_event()
{
  screen.backlight_level(0);
}

Application application;

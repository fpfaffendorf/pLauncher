#include <Arduino.h>

// Include Application Header
#include "application.h"

// Include Keyboard Library
#include "keyboard.h"
// Include Screen Library
#include "screen.h"

void Application::begin()
{

  // Begin keyboard on KEYBOARD_AIO
  keyboard.begin(KEYBOARD_AIO);

  // Begin screen
  screen.begin();
  // Loading screen 
  screen.loading();

  // Begin bridge connection
  Bridge.begin();

  // 1 Second to initialize Bridge and Serial Communication
  delay(1000);
  
}

void Application::menu()
{

  // Print screen options
  screen.print("Menu", 5, 10);
  screen.print("1- Programs", 5, 20);
  screen.print("9- Configuration", 5, 30);
  screen.flush();
  
  // Scan for button pressed
  unsigned char button = keyboard.scan();    
  switch (button)
  {
    // Button "1" pressed
    case KEYBOARD_1:
    {
      programs();
      break;
    }     
    // Button "9" pressed
    case KEYBOARD_9:
    {
      configuration();
      break;
    }     
  }
  
}

void Application::programs()
{

  // Loading Screen
  screen.loading();

  // Run ls command
  process.runShellCommand("cd /root/; ls -1 *.py");

  // Do nothing until the process finishes
  while (process.running());

  // Read output, parse, store in the program list and print screen
  String string = process.readString();
  String stringParse;
  unsigned char option = 1;
  int y = 10;
  String programsArray[5];
  for (int i = 0; i <= string.length(); i++)
  {
    if (string[i] == '\n')
    {
      String stringParseOption = "";
      stringParseOption += ((char)(option + 48));
      stringParseOption += "- ";
      programsArray[option-1] = stringParse;
      screen.print(stringParseOption + stringParse, 5, y);  
      y += 10;
      option++;
      stringParse = "";
    }
    else
    {
      stringParse += string[i];    
    }
  }  
  // Flush screen output
  screen.flush();

  // Scan for button pressed
  unsigned char button = keyboard.scan();    
  // Button (Number) pressed
  switch (button) 
  {
    case KEYBOARD_1:
    {
      execute(programsArray[0]);    
    }
    break; 
    case KEYBOARD_2:
    {
      execute(programsArray[1]);    
    }
    break; 
    case KEYBOARD_3:
    {
      execute(programsArray[2]);    
    }
    break; 
    case KEYBOARD_4:
    {
      execute(programsArray[3]);    
    }
    break; 
    case KEYBOARD_5:
    {
      execute(programsArray[4]);    
    }
    break; 
  }
  
}

void Application::configuration()
{

  // Print screen options
  screen.print("Configuration", 5, 10);
  screen.print("1- Date and Time", 5, 20);
  screen.print("2- Read IP", 5, 30);
  screen.flush();
  
  // Scan for button pressed
  unsigned char button = keyboard.scan();    
  switch (button)
  {
    // Button "1" pressed
    case KEYBOARD_1:
    {
      configuration_date_time();
      break;
    }     
    // Button "2" pressed
    case KEYBOARD_2:
    {
      configuration_ip();
      break;
    }     
  }

}

void Application::configuration_date_time()
{
  // Print current Date Time
  execute("sys/dt.py");     
}

void Application::configuration_ip()
{
  // Print current IP
  execute("sys/ip.py");   
}

void Application::execute(String program)
{

  if (program == "") return;

  screen.loading();

  // Get necessary parameters to execute this program
  process.runShellCommand("/usr/bin/python /root/" + program + " --help");
  while (process.running());
  String string = process.readString();
  String stringParse;
  String arguments;
  for (int i = 0; i <= string.length(); i++)
  {
    if (string[i] == '\n')
    {
      screen.print(stringParse, 5, 10);
      screen.flush();       
      arguments += captureArgument(stringParse) + " ";      
      stringParse = "";
    }
    else
    {
      stringParse += string[i];    
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

String Application::captureArgument(String argument_title)
{

  String argument = "";
  bool dot = false;

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

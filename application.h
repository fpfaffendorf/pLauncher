#ifndef __APPLICATION__
#define __APPLICATION__

// Include Process
#include <Process.h>

// Include Keyboard Library
#include "keyboard.h"
// Include Screen Library
#include "screen.h"

// Application name and version
#define APPLICATION_INFO "pLauncher v1.0"

// Keyboard is on AIO0
#define KEYBOARD_AIO 0

// Application Class 
class Application
{

  private:

    // Process instance
    Process process;    

    // Keyboard intance
    Keyboard keyboard;

    // Screen instance
    Screen screen;

    // List programs screen
    void programs();

    // Configuration
    void configuration();

    // Configuration Date and Time
    void configuration_date_time();

    // Configuration IP
    void configuration_ip();

    // Execute program
    void execute(String program);

    // Capture argument
    String captureArgument(String argument_title);
  
  public:

    // Begin application
    void begin();
    
    // Menu screen
    void menu();
        
};

#endif

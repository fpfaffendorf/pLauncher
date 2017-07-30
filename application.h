#ifndef __APPLICATION__
#define __APPLICATION__

// Include Process
#include <Process.h>

// Include Keyboard Library
#include "keyboard.h"
// Include Screen Library
#include "screen.h"
// Include Timer Library
#include "timer.h"

// Application name and version
#define APPLICATION_INFO "pLauncher v1.4"

// Backlight timer time out ticks
#define BACKLIGHT_TIMER_TIME_OUT_TICKS  250000 // (~30 seconds)

// Application Class 
class Application
{

  private:

    // Programs Current Page
    unsigned char programs_page = 1;

    // Next page request flag
    bool programs_next_page = false;

    // Current directory listing
    String current_directory = "";

    // Program to be executed
    String program_to_execute = "";

    // List programs in a given directory
    void menu();
  
    // List programs in a given directory
    void list_programs();
  
    // Execute program
    void execute();

    // Capture numeric argument
    String capture_numeric_argument(String argument_title);

    // Screen Backlight
    void screen_backlight();

  public:

    // Begin application
    void begin();
    
    // Menu screen
    void main();

    // Keyboard reset timer function
    static void keyboard_reset_event();

    // Keyboard time out function
    static void keyboard_time_out_event();
          
};

extern Application application;

#endif

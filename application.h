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
#define APPLICATION_INFO "pLauncher v1.3"

// Max number of programs per page
#define MAX_NUMBER_PROGRAMS 6

// Backlight timer time out ticks
#define BACKLIGHT_TIMER_TIME_OUT_TICKS  250000 // (~30 seconds)

// Application Class 
class Application
{

  private:

    // Process instance
    Process process;    

    // Programs Current Page
    unsigned char programs_page = 0;

    // List programs in a given directory
    void list_programs(String directory);
  
    // Format program option
    String format_program_option(unsigned char option, String title);

    // Execute program
    void execute(String program);

    // Capture argument
    String capture_argument(String argument_title);

    // Screen Backlight
    void screen_backlight();

    // Keyboard reset timer function
    static void keyboard_reset_event();

    // Keyboard time out function
    static void keyboard_time_out_event();
  
  public:

    // Begin application
    void begin();
    
    // Menu screen
    void menu();
        
};

extern Application application;

#endif

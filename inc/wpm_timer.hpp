#ifndef WPM_TIMER_H
#define WPM_TIMER_H

#include <string>
#include <chrono>

class wpm_timer {
public:
  wpm_timer()
    :start_paragraph{std::chrono::system_clock::now()}
  {}

  std::string get_wpm_line(unsigned int transcripted_length);  

  void reset_timer()
  { 
    start_paragraph = std::chrono::system_clock::now();
  }

private:
  std::chrono::system_clock::time_point start_paragraph; 
};

#endif

#include "../inc/wpm_timer.hpp"

std::string wpm_timer::get_wpm_line(unsigned int transcripted_length)
{
  std::string wpm_line;

  wpm_line += "\033[033m";
  wpm_line += "wpm: ";

  const float magic_number = 12.0;
  using std::chrono::seconds;
  using std::chrono::system_clock;
  auto secs =(std::chrono::duration_cast<seconds>(system_clock::now() -start_paragraph)).count();
  unsigned int wpm = (magic_number*(transcripted_length -1))/secs;
  wpm_line += std::to_string(wpm);
  wpm_line += '\n';

  return wpm_line;
}

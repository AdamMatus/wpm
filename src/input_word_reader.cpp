#include "../inc/input_word_reader.hpp"

#include <termios.h>
#include <unistd.h>
#include <stdio.h>

Input_word_reader::Input_word_reader()
  : typed_word{std::string()}
{
  struct termios stdi_conf;
  tcgetattr(STDIN_FILENO, &stdi_conf);
  stdi_conf.c_lflag &= ~(ECHO + ICANON);
  tcsetattr(STDIN_FILENO, TCSANOW, &stdi_conf);
}

Input_word_reader::~Input_word_reader()
{
  struct termios stdi_conf;
  tcgetattr(STDIN_FILENO, &stdi_conf);
  stdi_conf.c_lflag |= (ECHO + ICANON);
  tcsetattr(STDIN_FILENO, TCSANOW, &stdi_conf);
}

void Input_word_reader::wait_for_key()
{
  char c = getchar();
  
  if(c == 127 || c == '\b' )
  {
   typed_word.pop_back(); 
  }
  else
  {
   typed_word.push_back(c);
  }
}

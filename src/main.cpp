#include "../inc/main.hpp"
#include "../inc/paragraph_reader.hpp"
#include "../inc/input_word_reader.hpp"

#include <iostream>
#include <string>
#include <sstream>

#include <termios.h>
#include <unistd.h>
#include <stdio.h>


int main()
{
  Paragraph_reader pr(std::string("./txts/LOTR1"));
  Input_word_reader iwr;

  std::stringstream ss, ss2;
  std::string str1;

  auto par = pr.get_next_paragraph();
  ss << par;
  ss >> str1;
  std::cout << par;

  std::cout << str1 << std::endl << "dummy text to clear";
  std::string str2("");

  while(true)
  {
    iwr.wait_for_key();

    str2 = iwr.get_typed_word();
    std::cout << "\033[2K \r"  <<  str2;

    if(!str1.compare(str2))
    {
      iwr.acknowledge_received_word();
      ss >> str1;
      std::cout << "\033[2K \r" << str1 << std::endl;
    }

    if(!str2.compare("exit"))
    {
      std::cout << "EXIT";
      break;
    }
  }

  return 0;
}

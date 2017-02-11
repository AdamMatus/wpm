#include "../inc/main.hpp"
#include "../inc/paragraph_reader.hpp"

#include <iostream>
#include <string>
#include <sstream>

#include <termios.h>
#include <unistd.h>
#include <stdio.h>


int main()
{
  struct termios stdi_conf;
  tcgetattr(STDIN_FILENO, &stdi_conf);
  stdi_conf.c_lflag &= ~(ECHO + ICANON);
  tcsetattr(STDIN_FILENO, TCSANOW, &stdi_conf);



  Paragraph_reader pr(std::string("./txts/LOTR1"));

  std::stringstream ss, ss2;
  std::string str1;

    auto par = pr.get_next_paragraph();
    ss << par;
    ss >> str1;
    std::cout << par;

  std::cout << str1 << std::endl << "dummy text to clear";
  std::string str2("");

  char c;
  while(true)
  {
    ss2.clear();

    c = getchar();
    if(c == 127 || c == '\b' )
    {
     str2.pop_back(); 
     ss2 << str2;
    }
    else
    {
      ss2 << str2;
      ss2 << c;
    }

    ss2 >> str2;

    std::cout << "\033[2K \r"  <<  str2;

    

    if(ss2.tellg() > -1 )
    {
      if(!str1.compare(str2)){
        ss >>  str1;
        std::cout << "\033[2K \r" << str1 << std::endl;
      }

      if(!str2.compare("exit"))
      {
        std::cout << "EXIT";
        break;
      }

       str2 = "";
    }

  }


  stdi_conf.c_lflag |= (ECHO + ICANON);
  tcsetattr(STDIN_FILENO, TCSANOW, &stdi_conf);

  return 0;
}

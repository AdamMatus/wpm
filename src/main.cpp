#include "../inc/main.hpp"
#include "../inc/paragraph_reader.hpp"
#include "../inc/input_word_reader.hpp"
#include "../inc/paragraph_formatter.hpp"

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
  Paragraph_formatter pf;

  std::stringstream ss, ss2;
  std::string str1;

  std::string par;
  
  while(true)
  {
    while((par = pr.get_next_paragraph()) == "");
    pf.actualize_paragraph(par);
    std::string str2("");

    while(!pf.get_paragraph_state())
    {
      iwr.wait_for_key();
      str2 = iwr.get_typed_word();

      if(!str2.compare("exit"))
      {
        std::cout << "EXIT";
        break;
      }
    
      std::cout << pf.get_formatted_paragraph(str2);

      if(pf.get_word_state())
      {
        iwr.acknowledge_received_word();
        while(std::getchar() != ' ');
      }

    }
  }

  return 0;
}

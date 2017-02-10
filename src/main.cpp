#include "../inc/main.hpp"
#include "../inc/paragraph_reader.hpp"

#include <iostream>
#include <string>


int main()
{
  Paragraph_reader pr(std::string("./txts/LOTR1"));
  int i = 10;
  std::string un;
  while(i--)
  {
    std::getline(std::cin, un);
    std::cout << pr.get_next_paragraph();
  }
  return 0;
}

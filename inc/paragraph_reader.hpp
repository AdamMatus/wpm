#ifndef _PARAGRAPH_READER_HPP_
#define _PARAGRAPH_READER_HPP_

#include <string>
#include <iostream>
#include <fstream>

class Paragraph_reader{
  public:
    Paragraph_reader(const Paragraph_reader&) = delete;
    Paragraph_reader& operator=(const Paragraph_reader) = delete;
    Paragraph_reader(const std::string &textfilename);
    ~Paragraph_reader(void);

    std::string get_next_paragraph();

  private:
    std::ifstream textfile_istream;
    unsigned int current_par_num;
    std::string txtfilename;

};

#endif

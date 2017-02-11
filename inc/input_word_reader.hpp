#ifndef _INPUT_WORD_READER_HPP_
#define _INPUT_WORD_READER_HPP_

#include <string>
#include <sstream>

class Input_word_reader {
  public:
    Input_word_reader();
    ~Input_word_reader();
    void wait_for_key();  //blocking function
    std::string get_typed_word()
    {
      return typed_word;
    }
    void acknowledge_received_word()
    {
      typed_word = "";
    }

  private:
    std::string typed_word;
};

#endif


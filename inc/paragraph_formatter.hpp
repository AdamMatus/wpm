#ifndef _PARAGRAPH_FORMATTER_HPP_
#define _PARAGRAPH_FORMATTER_HPP_ 

#include <string>
#include <sstream>

class Paragraph_formatter {
  public:
    Paragraph_formatter();
    ~Paragraph_formatter() {}
    void actualize_paragraph(std::string new_paragraph);
    std::string get_formatted_paragraph(std::string typed_word); 
    bool get_paragraph_state() { return paragraph_transcripted; }
    bool get_word_state() { return word_transcripted; }
    void flag_word_transcipted() { word_transcripted= true; }
    void reset_word_transcripted_flag() { word_transcripted= false; }
    int get_transripted_text_length() {return transcripted.length();}

  private:
    std::string transcripted;
    std::string actual_word;
    std::stringstream parag_sstream;

    bool paragraph_transcripted;
    bool word_transcripted;

    void flag_paragraph_transcripted() { paragraph_transcripted = true; }
    void reset_paragraph_transcripted_flag() { paragraph_transcripted = false; }

    std::iostream::pos_type buffpos;
};

#endif

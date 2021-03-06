#include "../inc/paragraph_formatter.hpp"

#include <algorithm>

Paragraph_formatter::Paragraph_formatter() : transcripted  { std::string() },
    actual_word { std::string() },
    parag_sstream { std::stringstream() },
    paragraph_transcripted  {false},
    word_transcripted {false}
{
  buffpos = parag_sstream.tellg();
}

void Paragraph_formatter::actualize_paragraph(std::string new_paragraph)
{
  parag_sstream.clear();
  transcripted = "";
  reset_paragraph_transcripted_flag();
  parag_sstream << new_paragraph;
  parag_sstream >> actual_word;
  buffpos = parag_sstream.tellg();
}

std::string Paragraph_formatter::get_formatted_paragraph(std::string typed_word)
{
  parag_sstream.clear();
  parag_sstream.seekg(buffpos);
  //correctly transcripted text
  std::string formatted_paragraph;

  //rest of the paragraph
  if(!get_paragraph_state()) //check if all paragraph has been correctly transcribed
  {
    //match chars in both strings and get correctly transcribed part of the
    //actual word 
    size_t len = std::min(actual_word.size(), typed_word.size());
    size_t i = 0;
    while( i < len)
    {
      if( actual_word[i] != typed_word[i] )
        break;

      ++i;
    }

    //whole word has been typed correctly
    if(i == actual_word.size() )
    {
      flag_word_transcipted();
      transcripted.append(actual_word);

      formatted_paragraph.append("\033[32m");
      formatted_paragraph.append(transcripted);
      formatted_paragraph += ("\033[0m");
      
      if(" " != actual_word)
      {
        actual_word = " ";
        formatted_paragraph.append("\033[43m \033[0m");
      }
      else
      {
        if(!(parag_sstream >> actual_word))
        {
          flag_paragraph_transcripted();
          actual_word = "";
        }
        formatted_paragraph += "\033[43m";
        formatted_paragraph.append(actual_word);
        formatted_paragraph += "\033[0m";
        formatted_paragraph.append(" ");
      }

    }
    // only part of the word has been typed correctly
    else
    {
      reset_word_transcripted_flag();

      formatted_paragraph.append("\033[32m");
      formatted_paragraph.append(transcripted);
      formatted_paragraph.append("\033[0m");

      formatted_paragraph.append("\033[42m");
      formatted_paragraph.append(actual_word.substr(0, i));

      size_t shorter_size = std::min(typed_word.size(), actual_word.size());

      formatted_paragraph += "\033[41m";
      formatted_paragraph += actual_word.substr(i, shorter_size -i);

      //draw yellow only if there is place for it man
      if(shorter_size != actual_word.size())
      {
        formatted_paragraph.append("\033[43m");
        formatted_paragraph.append(actual_word.substr(typed_word.size(), actual_word.size() - typed_word.size()));
      }

      if(actual_word != " ")
        formatted_paragraph.append("\033[0m ");
    }

    formatted_paragraph.append("\033[0m");
    buffpos = parag_sstream.tellg();
    std::string rest_of_paragraph;
    std::getline(parag_sstream, rest_of_paragraph);
    if(!rest_of_paragraph.empty() and std::isspace(rest_of_paragraph.at(0))) 
       rest_of_paragraph.erase(rest_of_paragraph.begin());
    formatted_paragraph.append(rest_of_paragraph); 
  }//~formatting not transcirbed part of the paragraph

  return formatted_paragraph;
}

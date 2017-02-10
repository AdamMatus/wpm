#include "../inc/paragraph_reader.hpp"

Paragraph_reader::Paragraph_reader(const std::string &textfilename)
  : current_par_num(0), txtfilename(textfilename)
{
  textfile_istream.open(textfilename);
  //reading info about position in txt file from .statefile
  std::ifstream statefile;
  statefile.open(std::string(textfilename).append(".state"));
  statefile >> current_par_num;
  textfile_istream.seekg(current_par_num);
  statefile.close();
}
Paragraph_reader::~Paragraph_reader(void)
{
  //creating .state file with position info
  std::ofstream statefile;
  statefile.open(std::string(txtfilename).append(".state"), std::ios_base::out | std::ios_base::trunc);
  statefile << textfile_istream.tellg();
  statefile.close();

  //close text file
  textfile_istream.close();
}
std::string Paragraph_reader::get_next_paragraph()
{
  std::string next_paragraph;
  std::getline(textfile_istream, next_paragraph);
  return next_paragraph;
}

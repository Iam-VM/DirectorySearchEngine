#include <boost/program_options.hpp>
#include "validate_parsed_options.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>


namespace po = boost::program_options;
namespace po_cmd_style = boost::program_options::command_line_style;


po::variables_map options_value_map;



int main(int argc, char* argv[]){
  std::string search_keyword;
  std::vector<std::string> base_directories;
  std::vector<std::string> formats_list;



  std::cout<<"\n\n\t\t\t\t\t----------------------------------------------------------\n\n\t\t\t\t\tdse --help or dse -h for a  brief usage description.\n\n\t\t\t\t\t----------------------------------------------------------\n\n\n\n";


  po::options_description main_description("Usage description ");
  po::positional_options_description positional_description;
  main_description.add_options()
  ("search,s", po::value<std::string>(&search_keyword), "The name to search goes here.\n")
  ("base,b", po::value<std::vector<std::string>>(&base_directories)->multitoken(), "Specify the directories in which the search should confine [Recommended][supports multiple arguments].\n")
  ("substring", "To switch to substring mode. Searches for a substring in filesystem entity names. [When you vaguely remember the name]\n")
  ("dir", "To switch to directory mode. [When you know you are looking for a directory]\n")
  ("file", "To switch to file mode. [When you know you are looking for a file]\n")
  ("format", po::value<std::vector<std::string>>(&formats_list)->multitoken()->zero_tokens(), "To specify format. [When you remember the format of the file you are looking for][supports multiple arguments]\n")
  ("help,h", "For a brief usage description. For further details visit our website.\n");
  // positional_description.add("find", 1);
  int style_set = po_cmd_style::unix_style | po_cmd_style::short_allow_next;
  try{
    po::variables_map option_value_map;
    auto cmd_parser = po::command_line_parser(argc, argv)
    .options(main_description)
    .allow_unregistered()
    // .positional(positional_description)
    .style(style_set)
    .run();
    po::store(cmd_parser, option_value_map);
    po::notify(option_value_map);
    ::options_value_map = option_value_map;
  }
  catch(po::error& options_error){
    std::cerr<<main_description<<std::endl;
    exit(0);
  }

  if (argc<2)
  {
    std::cout<<"dse: No options used."<<std::endl<<std::endl<<std::endl<<main_description<<std::endl;
    exit(0);
  }

  check_options_and_export(::options_value_map, search_keyword, base_directories, formats_list, main_description);
  return 0;
}

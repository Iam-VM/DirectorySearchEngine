#include <iostream>
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <cstdlib>
#include <vector>
#include <string>
#include "search_initiator.h"
#include <map>

namespace po = boost::program_options;
namespace fs = boost::filesystem;


void filter_base_directories(po::variables_map options_value_map, std::vector<std::string> base_directories);
void recheck_base_directory(po::variables_map options_value_map);
std::vector<std::string> filtered_base_directories;

void check_options_and_export(po::variables_map& options_value_map,std::string search_keyword, std::vector<std::string> base_directories, std::vector<std::string> formats_list, po::options_description main_description){


  std::map<std::string, bool> dependent_variables;
  if (options_value_map.count("help")){
    std::cout<<main_description<<std::endl;
    exit(0);
  }


  if (options_value_map.count("format")){

    dependent_variables.insert({"format_specified", true});
    dependent_variables.insert({"file_mode", true});

    if (formats_list.size() == 0){
      std::cout<<"dse: --format used without arguments."<<std::endl<<std::endl<<std::endl<<main_description<<std::endl<<std::endl;
      exit(0);
    }
  }
  else{
    dependent_variables.insert({"format_specified", false});
    if (!options_value_map.count("file")){
      dependent_variables.insert({"file_mode", false});
    }
    else{
      dependent_variables.insert({"file_mode", true});
    }
  }


  if (options_value_map.count("dir")){
    dependent_variables.insert({"dir_mode", true});
  }
  else{
    dependent_variables.insert({"dir_mode", false});
  }

  if (options_value_map.count("substring")){
    dependent_variables.insert({"substring_mode", true});
  }
  else{
    dependent_variables.insert({"substring_mode", false});
  }

  if (options_value_map.count("search")){
    dependent_variables.insert({"keyword_specified", true});
  }
  else{
    dependent_variables.insert({"keyword_specified", false});
  }


 filter_base_directories(options_value_map, base_directories);



  for(auto format = formats_list.begin(); format != formats_list.end(); ++format)
  {
    if ((*format)[0] != '.')
    {
      (*format) = "." +   (*format);
    }
  }






  search_mechanism initiator_object;
  initiator_object.unzip_dependent_variables(dependent_variables);
  initiator_object.load_argument_values(search_keyword, ::filtered_base_directories, formats_list);
  initiator_object.initiate_search();
}

//--------------------------------------------------------------------------------------------------------


void filter_base_directories(po::variables_map options_value_map, std::vector<std::string> base_directories)
{
  ::filtered_base_directories.clear();
  if (!options_value_map.count("base"))
  {
    ::filtered_base_directories.push_back(".");
    std::cout<<"Searching in current directory..."<<std::endl<<std::endl;
  }
  else
  {
    for (auto i : base_directories)
    {
      if (fs::exists(i))
      {
        ::filtered_base_directories.push_back(i);
      }
      else
      {
        std::cout<<"dse: Seems Like "<<i<<" does not exist. Cannot search in "<<i<<std::endl<<std::endl<<std::endl;
      }
    }
    if (::filtered_base_directories.size() == 0)
    {
      recheck_base_directory(options_value_map);
    }
  }
}

//-----------------------------------------------------------------------------------------------------


 void recheck_base_directory(po::variables_map options_value_map)
{
  char choice;
  char* base_dir = new char;
  std::string base_dir_str;
    std::cout<<"\n\n\nNo base directory to proceed.. \n\nWould you like to enter another base directory path  ? (Y/N)  : ";
    std::cin>>choice;
    if (choice == 'Y' || choice == 'y' || choice == '1')
    {
      std::cin.clear();
      std::cout<<"\n\nEnter base directory path  :  ";
      scanf("%s", base_dir);
      std::cout<<std::endl<<std::endl;
      base_dir_str = base_dir;
      ::filtered_base_directories.push_back(base_dir_str);
      delete base_dir;
    }
    else
    {
      std::cout<<"\n\n\ndse: User chose to terminate. Terminating DSE. \n\n";
      exit(0);
    }
    filter_base_directories(options_value_map, ::filtered_base_directories);
}

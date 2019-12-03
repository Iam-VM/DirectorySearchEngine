#include <string>
#include <cstdlib>
#include <vector>
#include "search_algorithms.h"
#include <map>


struct search_engine {
  search_engine(searching_algorithm& algorithm, bool substr_mode){
    if (substr_mode){
      algorithm.search_substr();
      algorithm.return_status();
    }
    else{
      algorithm.search();
      algorithm.return_status();
    }
  }
};


struct search_mechanism {
public:

    void unzip_dependent_variables(std::map<std::string, bool> dependent_variables){
      file_mode = dependent_variables["file_mode"];
      format_specified = dependent_variables["format_specified"];
      substring_mode = dependent_variables["substring_mode"];
      dir_mode = dependent_variables["dir_mode"];
      keyword_specified = dependent_variables["keyword_specified"];
    }

    void load_argument_values(std::string& new_search_keyword, std::vector<std::string>& new_base_directories, std::vector<std::string>& new_formats_list){
      base_directories = new_base_directories;
      if (keyword_specified){
        search_keyword = new_search_keyword;
      }
      if (format_specified){
        formats_list = new_formats_list;
      }
    }

    void initiate_search (){
      if (keyword_specified && !file_mode && !dir_mode && !format_specified){
        key_file_dir_nofor algorithm;
        algorithm.set_arguments(search_keyword, base_directories);
        search_engine engine(algorithm, substring_mode);
      }
      if (keyword_specified && file_mode && !dir_mode && format_specified){
        key_file_nodir_for algorithm;
        algorithm.set_arguments(search_keyword, base_directories, formats_list);
        search_engine engine(algorithm, substring_mode);
      }
      if (keyword_specified && file_mode && !dir_mode && !format_specified){
        key_file_nodir_nofor algorithm;
        algorithm.set_arguments(search_keyword, base_directories);
        search_engine engine(algorithm, substring_mode);
      }
      if (keyword_specified && file_mode && dir_mode && !format_specified){
        key_file_dir_nofor algorithm;
        algorithm.set_arguments(search_keyword, base_directories);
        search_engine engine(algorithm, substring_mode);
      }
      if (keyword_specified && file_mode && dir_mode && format_specified){
        key_file_dir_for algorithm;
        algorithm.set_arguments(search_keyword, base_directories, formats_list);
        search_engine engine(algorithm, substring_mode);
      }
      if (keyword_specified && !file_mode && dir_mode && !format_specified){
        key_nofile_dir_nofor algorithm;
        algorithm.set_arguments(search_keyword, base_directories);
        search_engine engine(algorithm, substring_mode);
      }
      if (!keyword_specified && !file_mode && dir_mode && !format_specified){
        nokey_nofile_dir_nofor algorithm;
        algorithm.set_arguments(base_directories);
        search_engine engine(algorithm, substring_mode);
      }
      if (!keyword_specified && file_mode && dir_mode && !format_specified){
        nokey_file_dir_nofor algorithm;
        algorithm.set_arguments(base_directories);
        search_engine engine(algorithm, substring_mode);
      }
      if (!keyword_specified && file_mode && dir_mode && format_specified){
        nokey_file_dir_for algorithm;
        algorithm.set_arguments(base_directories, formats_list);
        search_engine engine(algorithm, substring_mode);
      }
      if (!keyword_specified && file_mode && !dir_mode && !format_specified){
        nokey_file_nodir_nofor algorithm;
        algorithm.set_arguments(base_directories);
        search_engine engine(algorithm, substring_mode);
      }
    }





  private:
    bool file_mode = false;
    bool format_specified = false;
    bool substring_mode = false;
    bool dir_mode = false;
    bool keyword_specified = false;
    std::string search_keyword;
    std::vector<std::string> base_directories;
    std::vector<std::string> formats_list;

};

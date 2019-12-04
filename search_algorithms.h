#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <boost/filesystem.hpp>
#include <boost/system/error_code.hpp>
#include <boost/algorithm/string.hpp>

namespace fs = boost::filesystem;


//parent class

struct searching_algorithm
{
  virtual void search() = 0;
  virtual void search_substr() = 0;
  std::string to_print;
  boost::system::error_code ec;
  bool first_time = false;
  bool found = false;

  void return_status()
  {
      if (!first_time)
      {
        std::cout<<"\n\nDidn't find anything....\n\n";
        exit(0);
      }
  }
};




struct key_file_dir_for : searching_algorithm
{
  void search() override
  {
    for (auto base_path_str : base_directories)
    {
      fs::path base_path = base_path_str;
      try
      {
        if (fs::exists(base_path))
        {
          fs::recursive_directory_iterator it(base_path), end;
          while(it != end)
          {
            try
            {
              if ((fs::is_regular_file(it->path()) || fs::is_directory(it->path())) && !is_symlink(it->path()))
              {
                if (it->path().stem().string() == search_keyword)
                {
                  if (first_time == false)
                  {
                    system("printf '\e[38;2;232;234;246m Name\e[0m, \e[38;2;159;168;218m Path\e[0m, \e[38;2;92;107;192m Type\e[0m  \n\n'");
                    first_time = true;
                  }
                  if (is_directory(it->path()))
                  {
                    to_print = "printf '\e[38;2;232;234;246m " + it->path().stem().string() + "\e[0m, " + "\e[38;2;159;168;218m " + it->path().string() + "\e[0m, " + "\e[38;2;92;107;192m " +  "Directory" + "\e[0m" + "\n\n'";
                    system(to_print.c_str());
                  }
                  else if(std::find(formats_list.begin(), formats_list.end(), it->path().extension().string()) != formats_list.end())
                  {
                    to_print = "printf '\e[38;2;232;234;246m " + it->path().stem().string() + "\e[0m, " + "\e[38;2;159;168;218m " + it->path().string() + "\e[0m, " + "\e[38;2;92;107;192m " +  it->path().extension().string() + "\e[0m" + "\n\n'";
                    system(to_print.c_str());
                  }
                }
              }
              it.increment(ec);
            }
            catch(std::exception& e){}
          }
        }
        else
        {
          std::cout<<"some problem with "<<base_path_str<<std::endl;
        }
      }
      catch (fs::filesystem_error& fs_error){std::cerr<<fs_error.what()<<std::endl;}
    }
  }


  void search_substr() override
  {
    for (auto base_path_str : base_directories)
    {
      fs::path base_path = base_path_str;
      fs::recursive_directory_iterator it(base_path), end;
      while(it != end)
      {
        try
        {
          if ((std::find(formats_list.begin(), formats_list.end(), it->path().extension().string()) != formats_list.end()) || is_directory(it->path()) && !is_symlink(it->path()))
          {
            std::string filename_str = it->path().stem().string();
            boost::to_lower(filename_str);
            boost::to_lower(search_keyword);
            auto matching_range = boost::find_first(filename_str, search_keyword);
            if(matching_range.begin() != matching_range.end())
            {
              boost::to_upper(matching_range);
              if (first_time == false)
              {
                system("printf '\e[38;2;232;234;246m Name\e[0m, \e[38;2;159;168;218m Path\e[0m, \e[38;2;92;107;192m Type\e[0m  \n\n'");
                first_time = true;
              }
              if (is_directory(it->path()))
              {
                to_print = "printf '\e[38;2;232;234;246m " + filename_str + "\e[0m, " + "\e[38;2;159;168;218m " + it->path().string() + "\e[0m, " + "\e[38;2;92;107;192m " +  "Directory" + "\e[0m" + "\n\n'";
                system(to_print.c_str());
              }
              else if(is_regular_file(it->path()))
              {
                to_print = "printf '\e[38;2;232;234;246m " + filename_str + "\e[0m, " + "\e[38;2;159;168;218m " + it->path().string() + "\e[0m, " + "\e[38;2;92;107;192m " +  it->path().extension().string() + "\e[0m" + "\n\n'";
                system(to_print.c_str());
              }
            }
        }
        it.increment(ec);
      }
      catch(std::exception& e){}
    }
  }
}


  void set_arguments(std::string new_search_keyword, std::vector<std::string> new_base_directories, std::vector<std::string> new_formats_list)
  {
    search_keyword = new_search_keyword;
    base_directories = new_base_directories;
    formats_list = new_formats_list;
  }


private:
  std::string search_keyword;
  std::vector<std::string> base_directories;
  std::vector<std::string> formats_list;
};




struct key_file_dir_nofor : searching_algorithm
{
  void search() override
  {
    for (auto base_path_str : base_directories)
    {
      fs::path base_path = base_path_str;
      fs::recursive_directory_iterator it(base_path), end;
      while(it != end)
      {
        try
        {
          if ((is_regular_file(it->path()) || is_directory(it->path())) && !is_symlink(it->path()))
          {
            if (it->path().stem().string() == search_keyword)
            {
              if (first_time == false)
              {
                system("printf '\e[38;2;232;234;246m Name\e[0m, \e[38;2;159;168;218m Path\e[0m, \e[38;2;92;107;192m Type\e[0m  \n\n'");
                first_time = true;
              }
              if (is_directory(it->path()))
              {
                to_print = "printf '\e[38;2;232;234;246m " + it->path().stem().string() + "\e[0m, " + "\e[38;2;159;168;218m " + it->path().string() + "\e[0m, " + "\e[38;2;92;107;192m " +  "Directory" + "\e[0m" + "\n\n'";
                system(to_print.c_str());
              }
              else if(is_regular_file(it->path()))
              {
                to_print = "printf '\e[38;2;232;234;246m " + it->path().stem().string() + "\e[0m, " + "\e[38;2;159;168;218m " + it->path().string() + "\e[0m, " + "\e[38;2;92;107;192m " +  it->path().extension().string() + "\e[0m" + "\n\n'";
                system(to_print.c_str());
              }
            }
          }
          it.increment(ec);
        }
        catch(std::exception& e){}
      }
    }
  }



  void search_substr() override
  {
    for (auto base_path_str : base_directories)
    {
      fs::path base_path = base_path_str;
      fs::recursive_directory_iterator it(base_path), end;
      while(it != end)
      {
        try
        {
          if (is_regular_file(it->path()) || is_directory(it->path()) && !is_symlink(it->path()))
          {
            std::string filename_str = it->path().stem().string();
            boost::to_lower(filename_str);
            boost::to_lower(search_keyword);
            auto matching_range = boost::find_first(filename_str, search_keyword);
            if(matching_range.begin() != matching_range.end())
            {
              boost::to_upper(matching_range);
              if (first_time == false)
              {
                system("printf '\e[38;2;232;234;246m Name\e[0m, \e[38;2;159;168;218m Path\e[0m, \e[38;2;92;107;192m Type\e[0m  \n\n'");
                first_time = true;
              }
              if (is_directory(it->path()))
              {
                to_print = "printf '\e[38;2;232;234;246m " + filename_str + "\e[0m, " + "\e[38;2;159;168;218m " + it->path().string() + "\e[0m, " + "\e[38;2;92;107;192m " +  "Directory" + "\e[0m" + "\n\n'";
                system(to_print.c_str());
              }
              else if(is_regular_file(it->path()))
              {
                to_print = "printf '\e[38;2;232;234;246m " + filename_str + "\e[0m, " + "\e[38;2;159;168;218m " + it->path().string() + "\e[0m, " + "\e[38;2;92;107;192m " +  it->path().extension().string() + "\e[0m" + "\n\n'";
                system(to_print.c_str());
              }
            }
        }
        it.increment(ec);
      }
      catch(std::exception& e){}
    }
  }
}



  void set_arguments(std::string new_search_keyword, std::vector<std::string> new_base_directories)
  {
    search_keyword = new_search_keyword;
    base_directories = new_base_directories;
  }


private:
  std::string search_keyword;
  std::vector<std::string> base_directories;
};



struct key_file_nodir_for : searching_algorithm
{
  void search() override
  {
    for (auto base_path_str : base_directories)
    {
      fs::path base_path = base_path_str;
      fs::recursive_directory_iterator it(base_path), end;
      while(it != end)
      {
        try
        {
          if (is_regular_file(it->path()) && !is_directory(it->path()) && !is_symlink(it->path()))
          {
            if (std::find(formats_list.begin(), formats_list.end(), it->path().extension().string()) != formats_list.end())
            {
              if(it->path().stem().string() == search_keyword)
              {
                if (first_time == false)
                {
                  system("printf '\e[38;2;232;234;246m Name\e[0m, \e[38;2;159;168;218m Path\e[0m, \e[38;2;92;107;192m Type\e[0m  \n\n'");
                  first_time = true;
                }
                to_print = "printf '\e[38;2;232;234;246m " + it->path().stem().string() + "\e[0m, " + "\e[38;2;159;168;218m " + it->path().string() + "\e[0m, " + "\e[38;2;92;107;192m " +  it->path().extension().string() + "\e[0m" + "\n\n'";
                system(to_print.c_str());
              }
            }
          }
          it.increment(ec);
        }
        catch(std::exception& e){}
      }
    }
  }


  void search_substr() override
  {
    for (auto base_path_str : base_directories)
    {
      fs::path base_path = base_path_str;
      fs::recursive_directory_iterator it(base_path), end;
      while(it != end)
      {
        try
        {
          if ((std::find(formats_list.begin(), formats_list.end(), it->path().extension().string()) != formats_list.end()) && !is_directory(it->path()) && !is_symlink(it->path()))
          {
            std::string filename_str = it->path().stem().string();
            boost::to_lower(filename_str);
            boost::to_lower(search_keyword);
            auto matching_range = boost::find_first(filename_str, search_keyword);
            if(matching_range.begin() != matching_range.end())
            {
              boost::to_upper(matching_range);
              if (first_time == false)
              {
                system("printf '\e[38;2;232;234;246m Name\e[0m, \e[38;2;159;168;218m Path\e[0m, \e[38;2;92;107;192m Type\e[0m  \n\n'");
                first_time = true;
              }
              else if(is_regular_file(it->path()))
              {
                to_print = "printf '\e[38;2;232;234;246m " + filename_str + "\e[0m, " + "\e[38;2;159;168;218m " + it->path().string() + "\e[0m, " + "\e[38;2;92;107;192m " +  it->path().extension().string() + "\e[0m" + "\n\n'";
                system(to_print.c_str());
              }
            }
        }
        it.increment(ec);
      }
      catch(std::exception& e){}
    }
  }
}


  void set_arguments(std::string new_search_keyword, std::vector<std::string> new_base_directories, std::vector<std::string> new_formats_list)
  {
    search_keyword = new_search_keyword;
    base_directories = new_base_directories;
    formats_list = new_formats_list;
  }

private:
  std::string search_keyword;
  std::vector<std::string> base_directories;
  std::vector<std::string> formats_list;
};





struct key_file_nodir_nofor : searching_algorithm
{
  void search() override
  {
    for (auto base_path_str : base_directories)
    {
      fs::path base_path = base_path_str;
      fs::recursive_directory_iterator it(base_path), end;
      while(it != end)
      {
        try
        {
          if (is_regular_file(it->path())  && !is_symlink(it->path()))
          {
            if (it->path().stem().string() == search_keyword)
            {
              if (first_time == false)
              {
                system("printf '\e[38;2;232;234;246m Name\e[0m, \e[38;2;159;168;218m Path\e[0m, \e[38;2;92;107;192m Type\e[0m  \n\n'");
                first_time = true;
              }
              to_print = "printf '\e[38;2;232;234;246m " + it->path().stem().string() + "\e[0m, " + "\e[38;2;159;168;218m " + it->path().string() + "\e[0m, " + "\e[38;2;92;107;192m " +  it->path().extension().string() + "\e[0m" + "\n\n'";
              system(to_print.c_str());
            }
          }
          it.increment(ec);
        }
        catch(std::exception& e){}
      }
    }
  }


  void search_substr() override
  {
    for (auto base_path_str : base_directories)
    {
      fs::path base_path = base_path_str;
      fs::recursive_directory_iterator it(base_path), end;
      while(it != end)
      {
        try
        {
          if (is_regular_file(it->path()) && !is_symlink(it->path()))
          {
            std::string filename_str = it->path().stem().string();
            boost::to_lower(filename_str);
            boost::to_lower(search_keyword);
            auto matching_range = boost::find_first(filename_str, search_keyword);
            if(matching_range.begin() != matching_range.end())
            {
              boost::to_upper(matching_range);
              if (first_time == false)
              {
                system("printf '\e[38;2;232;234;246m Name\e[0m, \e[38;2;159;168;218m Path\e[0m, \e[38;2;92;107;192m Type\e[0m  \n\n'");
                first_time = true;
              }
              to_print = "printf '\e[38;2;232;234;246m " + filename_str + "\e[0m, " + "\e[38;2;159;168;218m " + it->path().string() + "\e[0m, " + "\e[38;2;92;107;192m " +  it->path().extension().string() + "\e[0m" + "\n\n'";
              system(to_print.c_str());
            }
        }
        it.increment(ec);
      }
      catch(std::exception& e){}
    }
  }
}


  void set_arguments(std::string new_search_keyword, std::vector<std::string> new_base_directories){
    search_keyword = new_search_keyword;
    base_directories = new_base_directories;
  }

private:
  std::string search_keyword;
  std::vector<std::string> base_directories;
};



struct key_nofile_dir_nofor : searching_algorithm
{

  void search() override
  {
    for (auto base_path_str : base_directories)
    {
      fs::path base_path = base_path_str;
      fs::recursive_directory_iterator it(base_path), end;
      while(it != end)
      {
        try
        {
          if (is_directory(it->path()) && !is_symlink(it->path()))
          {
            if (it->path().stem().string() == search_keyword)
            {
              if (first_time == false)
              {
                system("printf '\e[38;2;232;234;246m Name\e[0m, \e[38;2;159;168;218m Path\e[0m, \e[38;2;92;107;192m Type\e[0m  \n\n'");
                first_time = true;
              }
              to_print = "printf '\e[38;2;232;234;246m " + it->path().stem().string() + "\e[0m, " + "\e[38;2;159;168;218m " + it->path().string() + "\e[0m, " + "\e[38;2;92;107;192m " +  "Directory" + "\e[0m" + "\n\n'";
              system(to_print.c_str());
            }
          }
          it.increment(ec);
        }
        catch(std::exception& e){}
      }
    }
  }


  void search_substr() override
  {
    for (auto base_path_str : base_directories)
    {
      fs::path base_path = base_path_str;
      fs::recursive_directory_iterator it(base_path), end;
      while(it != end)
      {
        try
        {
          if (is_directory(it->path()) && !is_symlink(it->path()))
          {
            std::string filename_str = it->path().stem().string();
            boost::to_lower(filename_str);
            boost::to_lower(search_keyword);
            auto matching_range = boost::find_first(filename_str, search_keyword);
            if(matching_range.begin() != matching_range.end())
            {
              boost::to_upper(matching_range);
              if (first_time == false)
              {
                system("printf '\e[38;2;232;234;246m Name\e[0m, \e[38;2;159;168;218m Path\e[0m, \e[38;2;92;107;192m Type\e[0m  \n\n'");
                first_time = true;
              }
              to_print = "printf '\e[38;2;232;234;246m " + filename_str + "\e[0m, " + "\e[38;2;159;168;218m " + it->path().string() + "\e[0m, " + "\e[38;2;92;107;192m " +  "Directory" + "\e[0m" + "\n\n'";
              system(to_print.c_str());
            }
        }
        it.increment(ec);
      }
      catch(std::exception& e){}
    }
  }
}


  void set_arguments(std::string new_search_keyword, std::vector<std::string> new_base_directories)
  {
    search_keyword = new_search_keyword;
    base_directories = new_base_directories;
  }

private:
  std::string search_keyword;
  std::vector<std::string> base_directories;
};



struct nokey_file_dir_for : searching_algorithm
{

  void search() override
  {
    for (auto base_path_str : base_directories)
    {
      fs::path base_path = base_path_str;
      fs::recursive_directory_iterator it(base_path), end;
      while(it != end)
      {
        try
        {
          if ((is_regular_file(it->path()) || is_directory(it->path())) && !is_symlink(it->path()))
          {
            if (first_time == false)
            {
              system("printf '\e[38;2;232;234;246m Name\e[0m, \e[38;2;159;168;218m Path\e[0m, \e[38;2;92;107;192m Type\e[0m  \n\n'");
              first_time = true;
            }
            if (is_directory(it->path()))
            {
              to_print = "printf '\e[38;2;232;234;246m " + it->path().stem().string() + "\e[0m, " + "\e[38;2;159;168;218m " + it->path().string() + "\e[0m, " + "\e[38;2;92;107;192m " +  "Directory" + "\e[0m" + "\n\n'";
              system(to_print.c_str());
            }
            if (std::find(formats_list.begin(), formats_list.end(), it->path().extension().string()) != formats_list.end())
            {
              to_print = "printf '\e[38;2;232;234;246m " + it->path().stem().string() + "\e[0m, " + "\e[38;2;159;168;218m " + it->path().string() + "\e[0m, " + "\e[38;2;92;107;192m " +  it->path().extension().string() + "\e[0m" + "\n\n'";
              system(to_print.c_str());
            }
            it.increment(ec);
          }
          it.increment(ec);
        }
        catch(std::exception& e){}
      }
    }
  }

  void search_substr() override
  {
    for (auto base_path_str : base_directories)
    {
      fs::path base_path = base_path_str;
      fs::recursive_directory_iterator it(base_path), end;
      while(it != end)
      {
        try
        {
          if ((is_regular_file(it->path()) || is_directory(it->path())) && !is_symlink(it->path()))
          {
            if (first_time == false)
            {
              system("printf '\e[38;2;232;234;246m Name\e[0m, \e[38;2;159;168;218m Path\e[0m, \e[38;2;92;107;192m Type\e[0m  \n\n'");
              first_time = true;
            }
            if (is_directory(it->path()))
            {
              to_print = "printf '\e[38;2;232;234;246m " + it->path().stem().string() + "\e[0m, " + "\e[38;2;159;168;218m " + it->path().string() + "\e[0m, " + "\e[38;2;92;107;192m " +  "Directory" + "\e[0m" + "\n\n'";
              system(to_print.c_str());
            }
            if (std::find(formats_list.begin(), formats_list.end(), it->path().extension().string()) != formats_list.end())
            {
              to_print = "printf '\e[38;2;232;234;246m " + it->path().stem().string() + "\e[0m, " + "\e[38;2;159;168;218m " + it->path().string() + "\e[0m, " + "\e[38;2;92;107;192m " +  it->path().extension().string() + "\e[0m" + "\n\n'";
              system(to_print.c_str());
            }
            it.increment(ec);
          }
          it.increment(ec);
        }
        catch(std::exception& e){}
      }
    }
  }

  void set_arguments(std::vector<std::string> new_base_directories, std::vector<std::string> new_formats_list)
  {
    base_directories = new_base_directories;
    formats_list = new_formats_list;
  }

private:
  std::vector<std::string> base_directories;
  std::vector<std::string> formats_list;
};



struct nokey_file_dir_nofor : searching_algorithm
{

  void search() override
  {
    for (auto base_path_str : base_directories)
    {
      fs::path base_path = base_path_str;
      fs::recursive_directory_iterator it(base_path), end;
      while(it != end)
      {
        try
        {
          if ((is_regular_file(it->path()) || is_directory(it->path())) && !is_symlink(it->path()))
          {
            if (first_time == false)
            {
              system("printf '\e[38;2;232;234;246m Name\e[0m, \e[38;2;159;168;218m Path\e[0m, \e[38;2;92;107;192m Type\e[0m  \n\n'");
              first_time = true;
            }
            if (is_directory(it->path()))
            {
              to_print = "printf '\e[38;2;232;234;246m " + it->path().stem().string() + "\e[0m, " + "\e[38;2;159;168;218m " + it->path().string() + "\e[0m, " + "\e[38;2;92;107;192m " +  "Directory" + "\e[0m" + "\n\n'";
              system(to_print.c_str());
            }
            if (is_regular_file(it->path()))
            {
              to_print = "printf '\e[38;2;232;234;246m " + it->path().stem().string() + "\e[0m, " + "\e[38;2;159;168;218m " + it->path().string() + "\e[0m, " + "\e[38;2;92;107;192m " +  it->path().extension().string() + "\e[0m" + "\n\n'";
              system(to_print.c_str());
            }
            it.increment(ec);
          }
          it.increment(ec);
        }
        catch(std::exception& e){}
      }
    }
  }

  void search_substr() override
  {
    for (auto base_path_str : base_directories)
    {
      fs::path base_path = base_path_str;
      fs::recursive_directory_iterator it(base_path), end;
      while(it != end)
      {
        try
        {
          if ((is_regular_file(it->path()) || is_directory(it->path())) && !is_symlink(it->path()))
          {
            if (first_time == false)
            {
              system("printf '\e[38;2;232;234;246m Name\e[0m, \e[38;2;159;168;218m Path\e[0m, \e[38;2;92;107;192m Type\e[0m  \n\n'");
              first_time = true;
            }
            if (is_directory(it->path()))
            {
              to_print = "printf '\e[38;2;232;234;246m " + it->path().stem().string() + "\e[0m, " + "\e[38;2;159;168;218m " + it->path().string() + "\e[0m, " + "\e[38;2;92;107;192m " +  "Directory" + "\e[0m" + "\n\n'";
              system(to_print.c_str());
            }
            if (is_regular_file(it->path()))
            {
              to_print = "printf '\e[38;2;232;234;246m " + it->path().stem().string() + "\e[0m, " + "\e[38;2;159;168;218m " + it->path().string() + "\e[0m, " + "\e[38;2;92;107;192m " +  it->path().extension().string() + "\e[0m" + "\n\n'";
              system(to_print.c_str());
            }
            it.increment(ec);
          }
          it.increment(ec);
        }
        catch(std::exception& e){}
      }
    }
  }


  void set_arguments(std::vector<std::string> new_base_directories)
  {
    base_directories = new_base_directories;
  }

private:
  std::vector<std::string> base_directories;
};



struct nokey_file_nodir_nofor : searching_algorithm
{

  void search() override
  {
    for (auto base_path_str : base_directories)
    {
      fs::path base_path = base_path_str;
      fs::recursive_directory_iterator it(base_path), end;
      while(it != end)
      {
        try
        {
          if (is_regular_file(it->path()) && !is_symlink(it->path()))
          {
            if (first_time == false)
            {
              system("printf '\e[38;2;232;234;246m Name\e[0m, \e[38;2;159;168;218m Path\e[0m, \e[38;2;92;107;192m Type\e[0m  \n\n'");
              first_time = true;
            }
            if (is_regular_file(it->path()))
            {
              to_print = "printf '\e[38;2;232;234;246m " + it->path().stem().string() + "\e[0m, " + "\e[38;2;159;168;218m " + it->path().string() + "\e[0m, " + "\e[38;2;92;107;192m " +  it->path().extension().string() + "\e[0m" + "\n\n'";
              system(to_print.c_str());
            }
            it.increment(ec);
          }
          it.increment(ec);
        }
        catch(std::exception& e){}
      }
    }
  }

  void search_substr() override
  {
    for (auto base_path_str : base_directories)
    {
      fs::path base_path = base_path_str;
      fs::recursive_directory_iterator it(base_path), end;
      while(it != end)
      {
        try
        {
          if (is_regular_file(it->path()) && !is_symlink(it->path()))
          {
            if (first_time == false)
            {
              system("printf '\e[38;2;232;234;246m Name\e[0m, \e[38;2;159;168;218m Path\e[0m, \e[38;2;92;107;192m Type\e[0m  \n\n'");
              first_time = true;
            }
            if (is_regular_file(it->path()))
            {
              to_print = "printf '\e[38;2;232;234;246m " + it->path().stem().string() + "\e[0m, " + "\e[38;2;159;168;218m " + it->path().string() + "\e[0m, " + "\e[38;2;92;107;192m " +  it->path().extension().string() + "\e[0m" + "\n\n'";
              system(to_print.c_str());
            }
            it.increment(ec);
          }
          it.increment(ec);
        }
        catch(std::exception& e){}
      }
    }
  }


  void set_arguments(std::vector<std::string> new_base_directories)
  {
    base_directories = new_base_directories;
  }

private:
  std::vector<std::string> base_directories;
};



struct nokey_nofile_dir_nofor : searching_algorithm
{

  void search() override
  {
    for (auto base_path_str : base_directories)
    {
      fs::path base_path = base_path_str;
      fs::recursive_directory_iterator it(base_path), end;
      while(it != end)
      {
        try
        {
          if (is_directory(it->path()) && !is_symlink(it->path()))
          {
            if (first_time == false)
            {
              system("printf '\e[38;2;232;234;246m Name\e[0m, \e[38;2;159;168;218m Path\e[0m, \e[38;2;92;107;192m Type\e[0m  \n\n'");
              first_time = true;
            }
            if (is_directory(it->path()))
            {
              to_print = "printf '\e[38;2;232;234;246m " + it->path().stem().string() + "\e[0m, " + "\e[38;2;159;168;218m " + it->path().string() + "\e[0m, " + "\e[38;2;92;107;192m " +  "Directory" + "\e[0m" + "\n\n'";
              system(to_print.c_str());
            }
            it.increment(ec);
          }
          it.increment(ec);
        }
        catch(std::exception& e){}
      }
    }
  }


  void search_substr() override
  {
    for (auto base_path_str : base_directories)
    {
      fs::path base_path = base_path_str;
      fs::recursive_directory_iterator it(base_path), end;
      while(it != end)
      {
        try
        {
          if (is_directory(it->path()) && !is_symlink(it->path()))
          {
            if (first_time == false)
            {
              system("printf '\e[38;2;232;234;246m Name\e[0m, \e[38;2;159;168;218m Path\e[0m, \e[38;2;92;107;192m Type\e[0m  \n\n'");
              first_time = true;
            }
            if (is_directory(it->path()))
            {
              to_print = "printf '\e[38;2;232;234;246m " + it->path().stem().string() + "\e[0m, " + "\e[38;2;159;168;218m " + it->path().string() + "\e[0m, " + "\e[38;2;92;107;192m " +  "Directory" + "\e[0m" + "\n\n'";
              system(to_print.c_str());
            }
            it.increment(ec);
          }
          it.increment(ec);
        }
        catch(std::exception& e){}
      }
    }
  }


  void set_arguments(std::vector<std::string> new_base_directories)
  {
    base_directories = new_base_directories;
  }


private:
  std::vector<std::string> base_directories;
};

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "zip.h"

#ifdef _WIN32

  #define _CD_ "cd "
  #define _PATH_INPUT_ "..\\..\\data\\input\\"
  #define _INPUT_PATH_INTO_FILE_ "get-childItem | foreach-object { $_.name } | out-file -filepath .\\.paths.txt"
  #define _PATHS_ ".paths.txt"

#endif

#ifdef __linux__

  #define _CD_ "cd "
  #define _PATH_INPUT_ "../../data/input/"
  #define _INPUT_PATH_INTO_FILE_ ";ls | tee >.paths.txt"
  #define _PATHS_ ".paths.txt"

#endif

#ifdef __APPLE__

  #define _CD_ "cd "
  #define _PATH_INPUT_ "../../data/input/"
  #define _INPUT_PATH_INTO_FILE_ ";ls | tee >.paths.txt"
  #define _PATHS_ ".paths.txt"

#endif

int main(int argc, const char* argv[]){

  std::vector<std::string> paths;
  if (argc > 1)
    for (int i = 1; i < argc; ++i)
      paths.push_back(argv[i]);
  else
  {
    int i = system(_CD_ _PATH_INPUT_ _INPUT_PATH_INTO_FILE_);

    std::ifstream file(_PATH_INPUT_ _PATHS_);

    if(!file.is_open())
      std::cout << "not open!";
    else
    {
      std::string path;
      while(!file.eof())
      {
        std::getline(file, path);
        paths.push_back(path);
      }
      paths.pop_back();

      file.close();
    }
  }

  zip::Zip point(paths);
  point.startCompress();

  return 0;
}
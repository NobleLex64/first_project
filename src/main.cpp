#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "directives.h"
#include "zip.h"

int main(int argc, const char* argv[]){

  __LOCALE__

  std::vector<std::string> paths;

  if (argc > 1)
    for (int i = 1; i < argc; ++i)
      paths.push_back(argv[i]);
  else
  {
    int i = system("cd " _PATH_TO_PROJECT_ _PATH_DATA_ _PATH_INPUT_ _CREATE_PATHS_);

    std::ifstream file(_PATH_TO_PROJECT_ _PATH_DATA_ _PATH_INPUT_ ".paths.txt");

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

  point.startProgramm();

  return 0;
}
#include "zip.h"

/* STL libraries */
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

/* my compression libs*/
#include "rle.h"
#include "bwt.h"
#include "mtf.h"
#include "lz77.h"
#include "haffman.h"

void zip::Zip::startCompress()
{
  Menu compressing_alg;

  compressing_alg.commWelcome();

  while(true)
  {
    std::cout << "Testing starts: " << std::endl << std::endl;

    int number_of_error = compressing_alg.commCheckProblems();
    std::cout << "info: ";
    switch(number_of_error)
    {
      case 0:
        std::cout << "\"All is OK!, you can continue.\"" << std::endl;
        break;
      case 1:
        std::cout << "\"/project02/data/input/ -> is empty!\"" << std::endl;
        std::cout << "info : \"Check this dir and add file's for compression!\"" << std::endl;
        break;
      case 2:
        std::cout << "\"algoritm RLE, has errors in its decoding!\"" << std::endl;
        break;
      case 3:
        std::cout << "\"algoritm 'BWT', has errors in its decoding!\"" << std::endl;
        break;
      case 4:
        std::cout << "\"algoritm 'MTF', has errors in its decoding!\"" << std::endl;
        break;
      case 5:
        std::cout << "\"algoritm 'LZ77', has errors in its decoding!\"" << std::endl;
        break;
      case 6:
        std::cout << "\"algoritm 'Haffmana', has errors in its decoding!\"" << std::endl;
        break;
      case 7:
        std::cout << "\"Tests were turned off\"" << std::endl;
        break;
      default:
        std::cout << "\"Unidentified behavior!\"" << std::endl;
        break;
    }

    std::cout << std::endl << "What do you want to do? Enter( <1> , <2> , <3> )" << std::endl;
    std::cout << "1) Continue. (recommended if 'all is ok')" << std::endl;
    std::cout << "2) Restart check." << std::endl;
    std::cout << "3) Exit. " << std::endl << std::endl;
    
    char command = '3';
    while(true)
    {
      std::cout << ">>> ";
      std::cin  >> command;
      std::cin.clear();

      if(command > '3' || command < '1')
        std::cout << "info: \"You pressed the wrong button, please try again!\"" << std::endl;
      else  
        break;
    }

    if(command == '3')
    {
      system("clear");
      Menu::commExit();
      return;
    }
    else if(command == '1')
      break;
    
    system("clear");
  }

  system("clear");

  Menu::commMode();

  system("clear");

  Menu::commExit();
}

void zip::Zip::Menu::commWelcome()
{
  system("clear");
  std::cout << "created 'Noble_lex_64', 05.2024" << std::endl << "Version 1.0.0" << std::endl;
  std::cout << "Hello, this program is made for the purpose of data compression, " << "Good luck!" << std::endl << std::endl;
  std::cin.get();
  std::cin.clear();
}

void zip::Zip::Menu::commMode()
{
  std::cout << "You can choose the operating mode ( <1>, <2>, <3> ): " << std::endl;
  std::cout << "1) Auto mode (the program itself will find the optimal algorithm)" << std::endl;
  std::cout << "2) Creative mode (you decide in what order the algorithms will be developed)" << std::endl;
  std::cout << "3) Exit. " << std::endl << std::endl;

  while(true)
  {
    char command = '4';
    std::cout << ">>> ";
    std::cin  >> command;
    std::cin.clear();

    if(command == '1')
    {
      system("clear");
      usualMode();
      break;
    }
    else if(command == '2')
    {
      system("clear");
      //creativeMode();
      break;
    }
    else if(command == '3')
    {
      commExit();
      return;
    }

    std::cout << "info : \"You pressed the wrong button, please try again!\"" << std::endl;
  }
}

double zip::Zip::Menu::commK(const double data_size, std::wstring_view shifr)
{
  double shifr_size = static_cast<double>(commSize(shifr));

  return data_size / shifr_size;
}

int zip::Zip::Menu::commCheckProblems()
{
  if(paths.empty())
    return 1;

  char answer = 'Y';
  std::cout << "You would like to run tests? (Y / y)" << std::endl << ">>> ";

  std::cin >> answer;
  std::cin.clear();

  if(answer != 'Y' && answer != 'y')
    return 7;

  std::vector<std::string> file_names{
    "test00",
    "test01",
    "test02",
    "test03",
    "test04",
    "test05",
    "test06(WarANDPiece 'Ru')",
    "test07(WarANDPiece 'En')",
    "test08",
    "test09",
    "test10",
  };

  for(const auto &name : file_names)
  {
    std::wstring data{};

    if(openFile(path_to_test + name + ".txt", data, 'w'))
      std::cout << name << " is open!" << std::endl;
    else
    {
      std::cout << name << " doesn't exist!" << std::endl;
      continue;
    }

    std::wstring shifr{};

    shifr = rle::compression(data);

    if(data != rle::decompression(shifr))
    {
      std::wstring result = rle::decompression(shifr);
      openFile("../../data/.test_result/" + name + ".txt", result, 'r');

      return 2; 
    }
    
    shifr = brrw::compression(data);

    if(data != brrw::decompression(shifr))
    {
      std::wstring result = brrw::decompression(shifr);
      openFile("../../data/.test_result/" + name + ".txt", result, 'r');

      return 3; 
    }

    shifr = mtf::compression(data);

    if(data != mtf::decompression(shifr))
    {
      std::wstring result = mtf::decompression(shifr);
      openFile("../../data/.test_result/" + name + ".txt", result, 'r');

      return 4; 
    }
    
    shifr = lz77::compression(data);

    if(data != lz77::decompression(shifr))
    {
      std::wstring result = lz77::decompression(shifr);
      openFile("../../data/.test_result/" + name + ".txt", result, 'r');

      return 5; 
    }
    
    shifr = haff::compression(data);

    if(data != haff::decompression(shifr))
    {
      std::wstring result = haff::decompression(shifr);
      openFile("../../data/.test_result/" + name + ".txt", result, 'r');

      return 6; 
    }
  }

  std::cout << std::endl;
  
  return 0;
}

void zip::Zip::Menu::commExit()
{
  std::cout << std::endl << "You have completed your work, Bye!" << std::endl;
}

void zip::Zip::Menu::usualMode()
{
  int i = 1;
  for(const auto &name : paths)
  {
    /* 
      1) rle
      2) bwt
      3) mtf
      4) lz77
      5) haff
    */
    std::vector<std::vector<int>> command 
    {
      {5},
      {4},
      {4, 5},
      {2, 3, 1, 4},
      {2, 3, 1, 4, 5},
      {2, 3, 1, 5},
      {2, 1, 5},
      {2, 1, 4},
      {2, 3, 5},
      {2, 3, 4},
      {2, 1, 3, 4},
      {2, 1, 3, 5},
    };

    std::wstring data;

    if(openFile(path_to_data + name, data, 'w'))
      std::cerr << "<< " << name << " is open!" << " >>"<<std::endl << std::endl;
    else
    {
      std::cerr << name << " doesn't exist!" << std::endl << std::endl;
      continue;
    }

    double data_bit_size = static_cast<double>(commSize(data));
    double best_k{};

    int need_alg{};

    for(int i{}, n = command.size(); i < n; ++i)
    { 
      std::cout << i + 1 << ") ";
      std::wstring shifr = data;

      for(int j{}, m = command[i].size(); j < m; ++j)
        shifr = typeOfCompression(command[i][j], shifr);

      double curr_k{commK(data_bit_size, shifr)};

      std::cout << "SUCCESSFULLY!\n.......................\nResult K: " << curr_k << std::endl;
      std::cout << "K(size): " << static_cast<double>(data.size())/ shifr.size() << std::endl << std::endl;

      if(curr_k > best_k)
      {
        best_k   = curr_k;
        need_alg = i;
      }
    }
    
    data = std::to_wstring(need_alg) + data;

    std::cout << "The order is what selected: ";

    for(auto it: command[need_alg])
      data = typeOfCompression(it, data);

    std::cout << " is compliteted!" << std::endl << std::endl;

    char commanda = 'N';
    std::cout << std::endl << "You want the write shifr in file? (Y / y)" << std::endl << ">>> ";
    std::cin >> commanda;
    std::cin.clear();

    if(commanda == 'Y' || commanda == 'y')
      if(openFile("../../data/output/convert" + std::to_string(i++), data, 'r'))
        std::cout << "The shifr was writed in file '" << name << "'" << std::endl;
      else
        std::cout << "Oops! Error write shifr in file!" << std::endl;
  }

}

std::wstring zip::Zip::Menu::typeOfCompression(int number, const std::wstring &data){

  switch(number)
  {
    case 1:
      std::cout << "RLE->";
      return rle::compression(data);
      break;
    case 2:
      std::cout << "BRW->";
      return brrw::compression(data);
      break;
    case 3:
      std::cout << "MTF->";
      return mtf::compression(data);
      break;
    case 4:
      std::cout << "LZ77->";
      return lz77::compression(data);
      break;
    case 5:
      std::cout << "HAFF->";
      return haff::compression(data);
      break;
  }

  return std::wstring();  
}

void zip::Zip::Menu::creativeMode()
{
}

bool zip::Zip::Menu::openFile(const std::string name, std::wstring &data, const char mode)
{
  if(mode == 'w')
    return writeFile(name, data);
  else if(mode == 'r')
    return readFile(name, data);

  return false;
}

bool zip::Zip::Menu::readFile(const std::string &name, std::wstring &data)
{
  std::wofstream file(name, std::ios::binary);

    if(file.is_open()){ 

      file << data;

      file.close();
    }
    else 
      return false;

  return true;
}

bool zip::Zip::Menu::writeFile(const std::string &name, std::wstring &data)
{

#ifdef _WIN32
    try {
      std::locale::global(std::locale("en_US"));
  } catch (const std::runtime_error& e) {
      std::cerr << "Locale error: " << e.what() << std::endl;
      return 1;
  }
#endif

#ifdef __linux__ 
  try {
      std::locale::global(std::locale("en_US.UTF-8"));
  } catch (const std::runtime_error& e) {
      std::cerr << "Locale error: " << e.what() << std::endl;
      return 1;
  }
#endif

#ifdef __APPLE__ 
  try {
      std::locale::global(std::locale("en_US.UTF-8"));
  } catch (const std::runtime_error& e) {
      std::cerr << "Locale error: " << e.what() << std::endl;
      return 1;
  }
#endif

  std::wifstream file(name, std::ios::binary);
  if(file.is_open()){

    wchar_t byte;

    while(file.get(byte))
      data += byte;
    
    file.close();
  }
  else 
    return false;

  return true;
}

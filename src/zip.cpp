#include "zip.h"

/* STL libraries */
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>

/* my compression libs*/
#include "rle.h"
#include "bwt.h"
#include "mtf.h"
#include "lz77.h"
#include "haffman.h"
#include "directives.h"

// START PROGRAMM

void zip::Zip::startProgramm()
{
  system(__CLEAR__);

  Menu work;

  work.commWelcome();

  std::string command = "3";
  std::cout << "What do you need? \n 1) Compressing data \n 2) Decompressing data \n";
  std::cout << ">>> ";
  std::cin  >> command;
  std::cin.clear();

  command == "1" ? startCompress(work) : startDecompress(work);
}

void zip::Zip::startCompress(Menu &name)
{
  system(__CLEAR__);

  std::cout << "Data compression module launched!" << std::endl << std::endl;

  while(true)
  {
    name.msgError(name.commCheckProblems());

    std::cout << std::endl << "What do you want to do? Enter( <1> , <2> , <3> )" << std::endl;
    std::cout << "1) Continue. (recommended if 'all is ok')" << std::endl;
    std::cout << "2) Restart check." << std::endl;
    std::cout << "3) Exit. " << std::endl << std::endl;
    
    std::string command = "3";

    while(true)
    {
      std::cout << ">>> ";
      std::cin  >> command;
      std::cin.clear();

      if(command > "3" || command < "1")
        std::cout << "info: \"You pressed the wrong button, please try again!\"" << std::endl;
      else  
        break;
    }

    if(command == "3")
    {
      Menu::commExit();
      return;
    }
    else if(command == "1")
      break;
    
    system(__CLEAR__);
  }

  system(__CLEAR__);

  Menu::commChooseALgoritm();
  Menu::commExit();
}

void zip::Zip::startDecompress(Menu &name)
{
  system(__CLEAR__);

  std::cout << "Data decompression module launched!" << std::endl << std::endl;

  while(true)
  {
    name.msgError(name.commCheckProblems());

    std::cout << std::endl << "What do you want to do? Enter( <1> , <2> , <3> )" << std::endl;
    std::cout << "1) Continue. (recommended if 'all is ok')" << std::endl;
    std::cout << "2) Restart check." << std::endl;
    std::cout << "3) Exit. " << std::endl << std::endl;

    std::string command = "3";

    while(true)
    {
      std::cout << ">>> ";
      std::cin  >> command;
      std::cin.clear();

      if(command < "1" && command > "3")
        std::cout << "info: \"You pressed the wrong button, please try again!\"" << std::endl;
      else  
        break;
    }

    if(command == "3")
    {
      Menu::commExit();
      return;
    }
    else if(command == "1")
      break;
    
    system(__CLEAR__);
  }

  system(__CLEAR__);
  Menu::commDecompression();
  Menu::commExit();
}


// HELPER FOR START

void zip::Zip::Menu::commChooseALgoritm()
{
  std::cout << "You can choose the operating mode ( <1>, <2>, <3> ): " << std::endl;
  std::cout << "1) Auto mode (the program itself will find the optimal algorithm)" << std::endl;
  std::cout << "2) Creative mode (you decide in what order the algorithms will be developed)" << std::endl;
  std::cout << "3) Exit. " << std::endl << std::endl;

  while(true)
  {
    std::string command = "4";
    std::cout << ">>> ";
    std::cin  >> command;
    std::cin.clear();

    if(command == "1")
    {
      system(__CLEAR__);
      usualMode();
      break;
    }
    else if(command == "2")
    {
      system(__CLEAR__);
      creativeMode();
      break;
    }
    else if(command == "3")
      return;

    std::cout << "info : \"You pressed the wrong button, please try again!\"" << std::endl;
  }
}

int zip::Zip::Menu::commCheckProblems()
{
  std::cout << "Testing starts: " << std::endl << std::endl;

  if(paths.empty())
    return 1;

  std::string answer = "y";
  std::cout << "You would like to run tests? (Y / any)" << std::endl << ">>> ";

  std::cin >> answer;
  std::cin.clear();

  if(answer != "Y" && answer != "y")
    return 7;

  const std::vector<std::string> file_names{
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

    if(openFile(_PATH_TO_PROJECT_ _PATH_DATA_ _PATH_TEST_ + name + ".txt", data, 'w'))
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
      openFile(_PATH_TO_PROJECT_ _PATH_DATA_ _PATH_TESTRESULT_ + name + ".txt", result, 'r');

      return 2; 
    }
    
    shifr = brrw::compression(data);

    if(data != brrw::decompression(shifr))
    {
      std::wstring result = brrw::decompression(shifr);
      openFile(_PATH_TO_PROJECT_ _PATH_DATA_ _PATH_TESTRESULT_ + name + ".txt", result, 'r');

      return 3; 
    }

    shifr = mtf::compression(data);

    if(data != mtf::decompression(shifr))
    {
      std::wstring result = mtf::decompression(shifr);
      openFile(_PATH_TO_PROJECT_ _PATH_DATA_ _PATH_TESTRESULT_ + name + ".txt", result, 'r');

      return 4; 
    }
    
    shifr = lz77::compression(data);

    if(data != lz77::decompression(shifr))
    {
      std::wstring result = lz77::decompression(shifr);
      openFile(_PATH_TO_PROJECT_ _PATH_DATA_ _PATH_TESTRESULT_ + name + ".txt", result, 'r');

      return 5; 
    }
    
    shifr = haff::compression(data);

    if(data != haff::decompression(shifr))
    {
      std::wstring result = haff::decompression(shifr);
      openFile(_PATH_TO_PROJECT_ _PATH_DATA_ _PATH_TESTRESULT_ + name + ".txt", result, 'r');

      return 6; 
    }
  }

  std::cout << std::endl;
  
  return 0;
}

void zip::Zip::Menu::commDecompression(){

  std::cout << "You can choose the operating mode ( <1>, <2>, <3> ): " << std::endl;
  std::cout << "1) ALL mode (decompression all file)" << std::endl;
  std::cout << "2) Selection mode (decompression selected files)" << std::endl;
  std::cout << "3) Exit. " << std::endl << std::endl;

  while(true)
  {
    std::string command = "4";
    std::cout << ">>> ";
    std::cin  >> command;
    std::cin.clear();

    if(command == "1")
    {
      system(__CLEAR__);
      allMode();
      break;
    }
    else if(command == "2")
    {
      system(__CLEAR__);
      selectedMode();
      break;
    }
    else if(command == "3")
      return;

    std::cout << "info : \"You pressed the wrong button, please try again!\"" << std::endl;
  }
}


// MSG

void zip::Zip::Menu::commWelcome()
{
  system(__CLEAR__);

  std::cout << "created 'Noble_lex_64', 05.2024" << std::endl << "Version 1.0.0" << std::endl;
  std::cout << "Hello, this program is made for the purpose of data compression, " << "Good luck!" << std::endl << std::endl;
  std::cout << "Continue? (enter any key)";
  std::cin.get();
  std::cin.clear();

  system(__CLEAR__);
}

void zip::Zip::Menu::commExit()
{
  std::cout << std::endl << "You have completed your work, Bye!" << std::endl;
}

void zip::Zip::Menu::msgError(int num)
{
  system(__CLEAR__);

  std::cout << "info: ";

  switch(num)
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
}


// COMPRESSION MODES

void zip::Zip::Menu::usualMode()
{
  std::cout << "You can start Auto mode!" << std::endl;
  std::cout << "In this mode, the program will automatically go through some sequences of algorithms!" << std::endl;
  std::cout << "Lets goo! (enter any key)" << std::endl;
  std::cin.get();
  std::cin.clear();

  clock_t TIME = 0;
  clock_t start = 0, end = 0;

  const std::vector<std::vector<int>> types
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

  for(int i = 0; i < paths.size(); ++i)
  {
    std::string name = paths[i];
  
    if(name[0] == '.')
      continue;
    
    if(name.find(".comp") != std::string::npos)
      continue;

    std::wstring data{};
    std::string coomand;

    if(openFile(_PATH_TO_PROJECT_ _PATH_DATA_  _PATH_INPUT_ + name, data, 'w'))
      std::cout << "<< " << name << " is open!" << " >>" << std::endl << std::endl;
    else
    {
      std::cerr << name << " doesn't exist!" << std::endl << std::endl;
      continue;
    }

    {
      std::wstring type(5, '\0');
      const double data_bit_size = commSize(data);
      double best_k{};

      for(int i = 0, n = types.size(); i < n; ++i)
      { 
        std::cout << i + 1 << ") ";

        std::wstring shifr = data;
        std::wstring type_of_shifr = compressionAlgoritm(types[i], shifr);

        double curr_k = commK(data_bit_size, shifr);

        std::cout << "SUCCESSFULLY!\nResult K: " << curr_k << std::endl << ".......................\n";
        if(curr_k > best_k)
        {
          best_k = curr_k;
          type = type_of_shifr;
        }
      }

      std::cout <<"\nThe order is what selected: ";

      for(auto it: type)
      {
        start = std::clock();
        data = typeOfCompression(it, data, it);
        end = std::clock();
        TIME = TIME + (end - start);
      }
      
      data.insert(0, type);

      std::cout << " is compliteted!\nResult K:" << best_k << "\nTIME: " << static_cast<double>(TIME) / CLOCKS_PER_SEC << " [sec]"<< std::endl << ".......................\n";
      type.clear();
      if(openFile(_PATH_TO_PROJECT_ _PATH_DATA_ _PATH_INPUT_ + name, type, 'r'))
        std::cout << "The file '" << name << "' was clear!" << std::endl;
      else
        std::cerr << "The file '" << name << "' wasn't clear!" << std::endl;
    }

    for(int i = name.size() - 1; i >= 0; --i)
      if(name[i] == '.')
      {
        name.replace(i, name.size() - i, ".comp");
        break;
      }

    if(openFile(_PATH_TO_PROJECT_ _PATH_DATA_ _PATH_INPUT_  + name, data, 'r'))
      std::cout << "The shifr was writed in file '" << name  <<"'!" << std::endl;
    else
      std::cerr << "Oops! Error write shifr in file!" << std::endl;
  }
}

void zip::Zip::Menu::creativeMode()
{
  std::cout << "You can start Creative mode!" << std::endl;
  std::cout << "In this mode, you can choose in what order the compression will occur!" << std::endl;
  std::cout << "Lets goo! (enter any key)" << std::endl;
  std::cin.get();
  std::cin.clear();

  clock_t TIME = 0;
  clock_t start = 0, end = 0;

  for(int i = 0, n = paths.size(); i < n; ++i)
  {
    std::string name = paths[i];

    if(name[0] == '.')
      continue;

    if(name.find(".comp") != std::string::npos)
      continue;

    std::string  coomand = "Y";
    std::wstring data{};

    std::cout << "You need to compress this file -> '" << name << "'? (Y / any)" << std::endl;
    std::cout << ">>> ";
    std::cin  >> coomand;
    std::cin.clear();

    if(coomand != "Y" && coomand != "y")
      continue;

    if(openFile(_PATH_TO_PROJECT_ _PATH_DATA_  _PATH_INPUT_ + name, data, 'w'))
      std::cout << "<< " << name << " is open!" << " >>"<<std::endl << std::endl;
    else
    {
      std::cerr << name << " doesn't exist!" << std::endl << std::endl;
      continue;
    }

    std::vector<int>  coomb(5, 0);
    std::vector<bool> exist(5, 0);

    std::wstring type_of_comb(5, L'\0');

    const double data_bit_size = commSize(data);
    double       cur_K = 0;

    int k = 0;
    while(k < 5)
    {
      system(__CLEAR__);
      if(k != 0)
      {
        cur_K = commK(data_bit_size, data);
        std::cout << "K : " << cur_K << std::endl;
        std::cout << "Want to go back a step? (Y / any)" << std::endl;
        std::cout << ">>> ";
        std::cin >> coomand;
        std::cin.clear();

        if(coomand == "Y" || coomand == "y")
        {
          int num = coomb[k - 1];
          coomb[--k] = 0;
          exist[num] = 0;

          data = typeOfDecompression(num + 1, data);
          std::cout.clear();
          continue;
        }
      }
      system(__CLEAR__);
      std::cout << "Select algoritm:\n";

      for(int j = 0; j < 5; ++j)
        if(!exist[j])
          switch(j)
          {
            case 0:
              std::cout << "1) RLE \n";
              break;
            case 1:
              std::cout << "2) BRW \n";
              break;
            case 2:
              std::cout << "3) MTF \n";
              break;
            case 3:
              std::cout << "4) LZ77 \n";
              break;
            case 4:
              std::cout << "5) HAFF \n";
              break;
          }

      while(true)
      {
        std::cout << ">>> ";
        std::cin >> coomand;
        std::cin.clear();

        if(coomand < "0" || coomand > "5" || exist[std::stoi(coomand) - 1])
        {
          std::cout<< "Wrong key! Try once more!" << std::endl;
          continue;
        }
        else
          break;
      }

      int val = std::stoi(coomand) - 1;

      exist[val] = true;
      coomb[k] = val;

      start = clock();
      data  = typeOfCompression(val + 1, data, type_of_comb[k]);
      end   = clock();
      TIME  = TIME + (end - start);

      cur_K = commK(data_bit_size, data);
      std::cout << "K: " << cur_K << std::endl;
      std::cout << "TIME: " << (static_cast<double>(end) - start) / CLOCKS_PER_SEC << " [sec]" << std::endl << std::endl;
      std::cout << std::endl << "You continue? (Y / any)" << std::endl;
      std::cout << ">>> ";
      std::cin >> coomand;
      std::cin.clear();

      if(coomand == "Y" || coomand == "y")
        ++k;
      else
        break;
    }
    
    data.insert(0, type_of_comb);
    type_of_comb.clear();
    if(openFile(_PATH_TO_PROJECT_ _PATH_DATA_ _PATH_INPUT_ + name, type_of_comb, 'r'))
      std::cout << "The file '" << name << "' was clear!" << std::endl;
    else
      std::cerr << "The file '" << name << "' wasn't clear!" << std::endl;

    for(int i = name.size() - 1; i >= 0; --i)
      if(name[i] == '.')
      {
        name.replace(i, name.size() - i, ".comp");
        break;
      }

    if(openFile(_PATH_TO_PROJECT_ _PATH_DATA_ _PATH_INPUT_  + name, data, 'r'))
      std::cout << "The shifr was writed in file '" << name  <<"'!" << std::endl;
    else
      std::cerr << "Oops! Error write shifr in file!" << std::endl;
  }
}

std::wstring zip::Zip::Menu::compressionAlgoritm(const std::vector<int> &coomb, std::wstring &data)
{
  if(coomb.empty())
    return std::wstring();

  std::wstring type_of_coomb(5, L'\0');

  for(int i = 0, n = coomb.size(); i < n; ++i)
    data = typeOfCompression(coomb[i], data, type_of_coomb[i]);
  
  return type_of_coomb;
}


// DECOMPRESSION MODE

void zip::Zip::Menu::allMode()
{
  std::cout << "You can start ALL mode!" << std::endl;
  std::cout << "In this mode, all files format '.comp' in the data/input folder will be decompressed!" << std::endl;
  std::cout << "Lets goo! (enter any key)" << std::endl;
  std::cin.get();
  std::cin.clear();
  std::cout << std::endl;

  for(int i = 0; i < paths.size(); ++i)
  {
    std::string name = paths[i];
  
    if(name[0] == '.')
      continue;

    if(name.find(".comp") == std::string::npos)
      continue;

    std::wstring data{};

    if(openFile(_PATH_TO_PROJECT_ _PATH_DATA_  _PATH_INPUT_ + name, data, 'w'))
      std::cout << "<< " << name << " is open!" << " >>" << std::endl << std::endl;
    else
    {
      std::cerr << name << " doesn't exist!" << std::endl << std::endl;
      continue;
    }

    std::wstring type_of_comp = data.substr(0, 5);
    data.erase(0, 5);

    for(int i = 4; i >= 0; --i)
      data = typeOfDecompression(type_of_comp[i], data);

    type_of_comp.clear();
    if(openFile(_PATH_TO_PROJECT_ _PATH_DATA_ _PATH_INPUT_ + name, type_of_comp, 'r'))
      std::cout << "The file '" << name << "' was clear!" << std::endl;
    else
      std::cerr << "The file '" << name << "' wasn't clear!" << std::endl;

    for(int i = name.size() - 1; i >= 0; --i)
      if(name[i] == '.')
      {
        name.replace(i, name.size() - i, ".txt");
        break;
      }

    std::cout << std::endl;
    if(openFile(_PATH_TO_PROJECT_ _PATH_DATA_ _PATH_INPUT_ + name, data, 'r'))
    {
      std::cout << "The data was writed in file '"<< name << "'!" << std::endl;
    }
    else
      std::cerr << "Oops! Error write data in file!" << std::endl;
    std::cout <<std::endl;
  }
}

void zip::Zip::Menu::selectedMode()
{
  std::cout << "You can start Selected mode!" << std::endl;
  std::cout << "In this mode, you will be offered files, select the ones you need!" << std::endl;
  std::cout << "Lets goo! (enter any key)" << std::endl;
  std::cin.get();
  std::cin.clear();
  std::cout << std::endl;

  for(int i = 0; i < paths.size(); ++i)
  {
    std::string name = paths[i];

    if(name[0] == '.')
      continue;

    if(name.find(".comp") == std::string::npos)
      continue;

    std::string coomand = "Y";

    std::cout << "You need to decompress this file -> '" << name << "'? (Y / any)" << std::endl;
    std::cout << ">>> ";
    std::cin  >> coomand;
    std::cin.clear();

    if(coomand != "Y" && coomand != "y")
      continue;

    std::wstring data{};

    if(openFile(_PATH_TO_PROJECT_ _PATH_DATA_  _PATH_INPUT_ + name, data, 'w'))
      std::cout << "<< " << name << " is open!" << " >>" << std::endl << std::endl;
    else
    {
      std::cerr << name << " doesn't exist!" << std::endl << std::endl;
      continue;
    }

    std::wstring type_of_comp = data.substr(0, 5);
    data.erase(0, 5);

    for(int i = 4; i >= 0; --i)
      data = typeOfDecompression(type_of_comp[i], data);

    type_of_comp.clear();
    if(openFile(_PATH_TO_PROJECT_ _PATH_DATA_ _PATH_INPUT_ + name, type_of_comp, 'r'))
      std::cout << "The file '" << name << "' was clear!" << std::endl;
    else
      std::cerr << "The file '" << name << "' wasn't clear!" << std::endl;

    for(int i = name.size() - 1; i >= 0; --i)
      if(name[i] == '.')
      {
        name.replace(i, name.size() - i, ".txt");
        break;
      }

    std::cout << std::endl;
    if(openFile(_PATH_TO_PROJECT_ _PATH_DATA_ _PATH_INPUT_ + name, data, 'r'))
    {
      std::cout << "The data was writed in file '"<< name << "'!" << std::endl;
    }
    else
      std::cerr << "Oops! Error write data in file!" << std::endl;
    std::cout <<std::endl;
  }

}


// secondary functions

std::wstring zip::Zip::Menu::typeOfDecompression(int type, const std::wstring &data){

  switch(type)
  {
    case 0:
      return data;
    case 1:
      std::cout << "<-RLE";
      return rle::decompression(data);
    case 2:
      std::cout << "<-BRW";
      return brrw::decompression(data);
    case 3:
      std::cout << "<-MTF";
      return mtf::decompression(data);
    case 4:
      std::cout << "<-LZ77";
      return lz77::decompression(data);
    case 5:
      std::cout << "<-HAFF";
      return haff::decompression(data);
    default:
      break;
  }
  return std::wstring();  
}

std::wstring zip::Zip::Menu::typeOfCompression(int type, const std::wstring &data, wchar_t &num){

  switch (type)
  {
    case 0:
      return data;
    case 1:
      std::cout << "RLE->";
      num = L'\1';
      return rle::compression(data);
    case 2:
      std::cout << "BRW->";
      num = L'\2';
      return brrw::compression(data);
    case 3:
      std::cout << "MTF->";
      num = L'\3';
      return mtf::compression(data);
    case 4:
      std::cout << "LZ77->";
      num = L'\4';
      return lz77::compression(data);
    case 5:
      std::cout << "HAFF->";
      num = L'\5';
      return haff::compression(data);
    default:
      num = L'\0';
      break;
  }

  return std::wstring();  
}

double zip::Zip::Menu::commK(const double data_size, std::wstring_view shifr)
{
  double shifr_size = static_cast<double>(commSize(shifr));

  return data_size / shifr_size;
}



// READ AND WRITE FILE.

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
  std::wifstream file(name, std::ios::binary);
  if(file.is_open()){

    wchar_t byte;

    while(file.get(byte) && data.size() < 100'486'760)
    {
      if(data.size() % 10'486'760 == 0)
        std::cout << "Read: " << data.size() << std::endl;

      data += byte;
    }

    std::cout << "Read: " << data.size() << std::endl;

    file.close();
  }
  else 
    return false;

  return true;
}

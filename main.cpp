#include "lz77.h"

#include <iostream>
#include <fstream>

int main(){

  std::vector<std::string> data;
  std::fstream file;
  {
    file.open("../data/input/test_for_lz77.txt");
    std::string str;
    while(!file.eof())
    {
      str = "";
      std::getline(file, str);
      data.push_back(str);
    }
    file.close();
    file.open("../data/input/text.txt");
    std::string res = "";
    while(!file.eof())
    {
      str = "";
      std::getline(file, str);
      res += str + '\n';
    }
    data.push_back(res);
    file.close();
  }

  {
    file.open("../data/output/LZ77.TXT"); 
    for(int i = 0; i < data.size(); ++i){
      size_t size = data[i].size();
      std::string shifr = lz77::compression(data[i]);
      if(size < 200)
      {
        file << "Entered data(" << size << ") : " << data[i] << std::endl;
        file << "Result shifr     : " << shifr << std::endl;
      }

      file << "data / shifr     : " << size / static_cast<double>(shifr.size()) << std::endl;
      std::string decomp = lz77::decompression(shifr);
      size = decomp.size();
      file << "Result decomp("<< size <<"): "<< decomp << std::endl;
      decomp == data[i]? file << "algoritm works! :)" << std::endl << std::endl: file << "algoritm doesn't works! :(" << std::endl << std::endl;
    }
    file.close();
  }

  return 0;
}
#include "lz77.h"
#include "bwt.h"
#include "treap.h"
#include "mtf.h"
#include "haffman.h"

#include <iostream>
#include <fstream>

size_t getBitSize(std::wstring_view data)
{
  size_t counts_bit = 0;
  for(auto it = data.begin(); it < data.end(); ++it)
  {
    if(*it < 255)
      counts_bit += 8;
    else if(*it < 4096)
      counts_bit += 12;
    else if(*it < 65536)
      counts_bit += 16;
    else if(*it < 1'048'576)
      counts_bit += 20;
    else if(*it < 16'777'216)
      counts_bit += 24;
    else if(*it < 268'435'345)
      counts_bit += 28;
    else if(*it < 4'294'967'296)
      counts_bit += 32;
  }

  return counts_bit;
}

int main(){

  setlocale(LC_ALL, "ru");

  std::FILE *input = std::freopen("../data/input/text.txt", "r", stdin);
  std::FILE *output = std::freopen("../data/output/text.txt", "w", stdout);
  
  std::wstring data;

  for(int i = 0; i < 207; ++i)
  {
    std::wstring tmp;
    std::getline(std::wcin, tmp);
    data += tmp + L'\n';
  }

  std::wcout << data.size() << std::endl;

  std::wcout << data << std::endl; 

  std::wstring shifr = haff::compression(data);
/* 
  std::freopen("../data/input/data.txt", "rb", stdin);
  std::freopen("../data/output/result.txt", "wb", stdout);

  for(int i = 0; i < 10; i++){

    std::getline(std::wcin, data);

    std::wcout << L"DATA: " << data << L", size:" << data.size() << L", bit_size:" << getBitSize(data) << L", bit_per_char:" << static_cast<double>(getBitSize(data))/ data.size() << std::endl;

    shifr = brrw::compression(data + L'$');

    std::wcout << L"BRW: " << shifr << L", size:" << shifr.size() << L", bit_size:" << getBitSize(shifr) << std::endl;

    shifr = mtf::compression(shifr);

    std::wcout << L"MTF: " << shifr << L", size:" << shifr.size() << L", bit_size:" << getBitSize(shifr) << std::endl;

    shifr = mtf::decompression(shifr);

    std::wcout << L"MTF decomp: " << shifr << L", size:" << shifr.size() << L", bit_size:" << getBitSize(shifr) << std::endl;

    shifr = brrw::decompression(shifr);
    shifr.pop_back();

    std::wcout << L"BRW decomp: " << shifr << L", size:" << shifr.size() << L", bit_size:" << getBitSize(shifr) << std::endl << std::endl;
  } */

  //std::wcout << shifr << std::endl;

  std::wcout << "K: " << static_cast<double>(data.size()) / shifr.size()<< std::endl;

  std::wstring decomp = haff::decompression(shifr);

  std::wcout << decomp.size() << std::endl;

  std::wcout << "K: " << static_cast<double>(data.size()) / decomp.size()<< std::endl;
  
  std::wcout << decomp;

  return 0;
}
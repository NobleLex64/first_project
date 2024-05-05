#include "lz77.h"
#include "bwt.h"
#include "treap.h"
#include "mtf.h"

#include <iostream>
#include <fstream>


int main(){

 /*  std::wcout << ">>> ";
  std::getline(std::wcin, data);
  std::wstring shifr = brrw::compression(data + L'$');
  std::wcout << "Shifr: " << shifr << std::endl;
  std::wstring decomp = brrw::decompression(shifr);
  decomp.pop_back();
  std::wcout << "Decomp: " << decomp << std::endl; */

  std::wstring data;
  std::wstring shifr;

  std::freopen("../data/input/data.txt", "r", stdin);
  std::freopen("../data/output/result.txt", "w", stdout);

  for(int i = 0; i < 10; i++){

    std::getline(std::wcin, data, L'\n');

    std::wcout << "BRW: " << data << ", size:" << data.size()<<std::endl;

    shifr = brrw::compression(data + L'$');

    std::wcout << "BRW: " << shifr << ", size:" << shifr.size()<<std::endl;

    shifr = mtf::compression(shifr);

    std::wcout << "MTF: " << shifr << ", size:" << shifr.size() <<std::endl;


    shifr = mtf::decompression(shifr);

    std::wcout << "MTF decomp: " << shifr << ", size:" << shifr.size() << std::endl << std::endl;
  }

  return 0;
}
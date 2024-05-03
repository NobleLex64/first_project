#include "lz77.h"
#include "bwt.h"

#include <iostream>
#include <fstream>


int main(){

  std::string data;
  std::cout << ">>> ";
  std::getline(std::cin, data);
  std::string shifr = brrw::compression(data + '$');
  std::cout << "Shifr: " << shifr << std::endl;
  std::string decomp = brrw::decompression(shifr);
  decomp.pop_back();
  std::cout << "Decomp: " << decomp << std::endl;

  return 0;
}
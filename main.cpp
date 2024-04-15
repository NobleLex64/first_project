#include "rle.h"

#include <iostream>
#include <fstream>

int main(){

  std::string text = "The google funs, kills many many people!/n\n";
  std::string decomp = "";
  std::string comp = "";

  rle::compressionString(text, comp);
  decomp = rle::decompressionString(comp);

  std::cout << "Prime  TEXT: " << text << std::endl;
  std::cout << "Comp   TEXT: " << comp << std::endl;
  std::cout << "K:           " << static_cast<double>(text.size()) / static_cast<double>(comp.size()) << std::endl;
  std::cout << "Decomp TEXT: " << decomp << std::endl;
  std::cout << "K idle(1):   " << static_cast<double>(text.size()) / static_cast<double>(decomp.size()) << std::endl;

  return 0;
}
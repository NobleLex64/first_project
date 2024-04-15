#include "test.h"
#include "rowGenerator.h"
#include "rle.h"

#include<fstream>

void tst::testRle(){

  size_t n = 0;
  size_t s_max = 0;
  size_t s_min = 0;

  std::cout << "Enter, how many rows you need          : ";
  std::cin >> n;

  std::cout << "Enter, maximum possible size of strings: ";
  std::cin >> s_max;

  std::cout << "Enter, minimum possible size of strings:  ";
  std::cin >> s_min;

  std::string comp;
  std::string decomp;
  std::vector<std::string> text = gnr::generator(n, s_max, s_min);

  std::ofstream file;
  try
  {
    file.open("../data/output.txt");

    for(size_t i = 0; i < n; ++i)
    {
      rle::compressionString(text[i], comp);
      decomp = rle::decompressionString(comp);

      file << "Prime  TEXT: " << text[i] << std::endl;

      file << "Comp   TEXT: " << comp << std::endl;

      file << "Decomp TEXT: " << decomp << std::endl;

      file << "K:           " << static_cast<double>(text.size()) / static_cast<double>(comp.size()) << std::endl;
    
      if(decomp == text[i])
        file << "No Error!" << std::endl;
      else 
        file << "Error!" << std::endl;
    }
    file.close();
  }
  catch(const std::exception& err){
    std::cerr << err.what();
  }
}


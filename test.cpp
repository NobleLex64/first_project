#include "test.h"
#include "rowGenerator.h"
#include "rle.h"

#include<fstream>

std::pair<std::string, size_t> checkDecomp(std::string_view text, std::string_view decomp){
  
  std::string not_match(decomp.size(), ' ');
  size_t count = 0;

  auto it_t = text.begin();
  auto it_d = decomp.begin();

  while(it_t < text.end() && it_d < decomp.end()){

    if(*it_t != *it_d)
    {
      ++count;
      not_match[(it_d - decomp.begin())] = '^';
    }else if(*it_t == '\n')
      not_match[(it_d - decomp.begin())] = *it_t;

    ++it_t;
    ++it_d;
  }

  return make_pair(not_match, count);
}

void tst::testRle(){
  try
  {
    size_t n = 0;
    size_t s_max = 0;
    size_t s_min = 0;

    std::cout << "Enter, how many rows you need          : ";
    std::cin >> n;

    std::cout << "Enter, maximum possible size of strings: ";
    std::cin >> s_max;

    std::cout << "Enter, minimum possible size of strings: ";
    std::cin >> s_min;

    std::string comp;
    std::string decomp;

    clock_t start_t = clock();
    std::vector<std::string> text = gnr::generator(n, s_min, s_max);
    clock_t end_t = clock();

    std::cout << "Generator rows time: (" << static_cast<double>(end_t - start_t) / CLOCKS_PER_SEC << ").s" << std::endl;

    std::ofstream file;

    n = 0;

    file.open("../data/output.txt");
    
    for(auto it = text.begin(), end = text.end(); it < end; ++it)
    {
      file << "---------START--------"<< std::endl;
      start_t = clock();
      rle::compressionString(*it, comp);
      end_t = clock();

      file << "*Compression time  : (" << static_cast<double>(end_t - start_t) / CLOCKS_PER_SEC << ").s" << std::endl;
    
      start_t = clock();
      decomp = rle::decompressionString(comp);
      end_t = clock();

      file << "*Decompression time: (" << static_cast<double>(end_t - start_t) / CLOCKS_PER_SEC << ").s" << std::endl;
      file << "1) Line size        : " << (*it).size() << std::endl;
      file << "2) Compression ratio: " << static_cast<double>((*it).size()) / static_cast<double>(comp.size()) << std::endl;
      file << "3) Didn't match (";

      if(decomp == *it)
        file << "0) : All is OK!" << std::endl;
      else
      {
        ++n;
        std::pair<std::string, size_t> check = checkDecomp(*it, decomp);
        file << check.second << ") : " << std::endl << decomp << std::endl << check.first << std::endl;
      }
      file << "~End of line (" << (it - text.begin()) << ");" << std::endl << std::endl;
    }
    file << "#(" << n <<"), Errors!" << std::endl;
    file << "----------END---------"<< std::endl;

    file.close();
  }
  catch(const std::exception& err){

    std::cerr << "testRLE: " << std::endl;
    std::cerr << err.what()  << std::endl;
  }
}


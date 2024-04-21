#include "test.h"
#include "rle.h"

std::pair<std::string, size_t> checkDecomp(std::string_view text, std::string_view decomp){
  
  std::string not_match = static_cast<std::string>(text);
  size_t count = 0;

  auto it_t = not_match.begin();
  auto it_d = decomp.begin();

  while(it_t < not_match.end() && it_d < decomp.end()){

    if(*it_t != *it_d)
    {
      while(it_t < not_match.end() && *it_t != *it_d){
        ++count;
        *it_t -= 32;
        ++it_t;
      }
    }

    ++it_t;
    ++it_d;
  }

  return make_pair(not_match, count);
}

void tst::testRle(const std::vector<std::string>& text, const std::string& path){
  try
  {
    clock_t start_t;
    clock_t end_t;

    std::string comp;
    std::string decomp;

    std::ofstream file;

    int n = 0;

    file.open(path);
    
    for(auto it = text.begin(), end = text.end(); it < end; ++it)
    {
      file << "---------START--------"<< std::endl;
      start_t = clock();
      comp = rle::compression(*it);
      end_t = clock();

      file << "*Compression time  : (" << static_cast<double>(end_t - start_t) / CLOCKS_PER_SEC << ").s" << std::endl;
    
      start_t = clock();
      decomp = rle::decompression(comp);
      end_t = clock();

      file << "*Decompression time : (" << static_cast<double>(end_t - start_t) / CLOCKS_PER_SEC << ").s" << std::endl;
      file << "0) Type of decoding :";

      if(comp[0] == '\0')
        file << "Text" << std::endl;
      else
        file << "Image" << std::endl;

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

void tst::testRle(std::string_view data, const std::string& path){
  try
  {
    clock_t start_t;
    clock_t end_t;

    std::ofstream file;

    int n = 0;

    file.open(path);
  
    file << "---------START--------"<< std::endl;
    start_t = clock();
    std::string comp = rle::compression(data);
    end_t = clock();

    file << "*Compression time  : (" << static_cast<double>(end_t - start_t) / CLOCKS_PER_SEC << ").s" << std::endl;
  
    start_t = clock();
    std::string decomp = rle::decompression(comp);
    end_t = clock();

    file << "*Decompression time : (" << static_cast<double>(end_t - start_t) / CLOCKS_PER_SEC << ").s" << std::endl;
    file << "0) Type of decoding :";

    if(comp[0] == '\0')
      file << "Text" << std::endl;
    else
      file << "Image" << std::endl;

    file << "1) Line size        : " << (data).size() << std::endl;
    file << "2) Compression ratio: " << static_cast<double>((data).size()) / static_cast<double>(comp.size()) << std::endl;
    file << "3) Didn't match (";

    if(decomp == data)
      file << "0) : All is OK!" << std::endl;
    else
    {
      ++n;
      std::pair<std::string, size_t> check = checkDecomp(data, decomp);
      file << check.second << ") : " << std::endl << decomp << std::endl << check.first << std::endl;
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


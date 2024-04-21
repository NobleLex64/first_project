#include "test.h"
#include "rowGenerator.h"

int main(){

  // Path from catolog with input file
  std::string path_input = "../data/input/";

  // Random string generator
  std::cout << "You need random generator string? (y/n)" << std::endl;
  if(std::cin.get() == 'y')
  {
    size_t n = 0;
    size_t s_max = 0;
    size_t s_min = 0;
    std::cin.ignore();

    std::cout << "Enter, how many rows you need          : ";
    std::cin >> n;

    std::cout << "Enter, maximum possible size of strings: ";
    std::cin >> s_max;

    std::cout << "Enter, minimum possible size of strings: ";
    std::cin >> s_min;

    std::vector<std::string> vec1 = gnr::generator(n, s_min, s_max);
    tst::testRle(vec1, "../data/output/randomGeneratorlines.txt");
  }

  try{
    std::ifstream input;

    // open text input file
    input.open(path_input + "text.txt");  

    std::string str;
    std::string ifstr;

    while(!input.eof())
    {
      ifstr = "";
      std::getline(input, ifstr);
      str += ifstr;
    }

    // close text input file
    input.close();

    // write result in text output file
    tst::testRle(str, "../data/output/textResult.txt");

    // Open the file in binary mode
    input.open(path_input + "pngwing.png");
    str = "";

    while(!input.eof())
    {
      ifstr = "";
      std::getline(input, ifstr);
      str += ifstr;
    }
    // close image input file
    input.close();

    // write result in image output file
    tst::testRle(str, "../data/output/imageResult.txt");

  }catch(...)
  {
    std::cerr << "ERROR with reading file!" << std::endl;
  }
  return 0;
}
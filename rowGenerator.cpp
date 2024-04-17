#include "rowGenerator.h"

// return array of string, on the input takes the number of lines, the maximum and the minimum size of the rows 
std::vector<std::string> gnr::generator(const size_t _N, const size_t _Min = 1, const size_t _Max = MAX_GENERATOR_SIZE){

  srand(time(0));

  size_t N = 0;
  std::vector<std::string> result(_N);

  for(auto it = result.begin(), end = result.end(); it < end; ++it)
  {
    N = rand() % _Max;
    
    if(N < _Min)
      N = _Min;

    std::string str(N, '\0');

    for(auto its = str.begin(), ends = str.end(); its < ends; ++its)
    {
      if((its - str.begin()) % 2 == 0 || (its - str.begin()) % 3 == 0)
        *its = rand() % 58 + 64;
      else
        *its = rand() % 127;
    }
    
    *it = str;
  }
  return result;
}


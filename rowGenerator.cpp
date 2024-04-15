#include "rowGenerator.h"

// return array of string, on the input takes the number of lines, the maximum and the minimum size of the rows 
std::vector<std::string> gnr::generator(const size_t _N, const size_t _Min = 0, const size_t _Max = MAX_GENERATOR_SIZE){

  srand(time(0));

  size_t rand_str_size = 0;
  std::vector<std::string> result(_N);

  for(size_t i = 0; i < _N; ++i)
  {
    rand_str_size = rand() % _Max + _Min;
    std::string str(rand_str_size, '\0');

    for(auto& ch: str)
      ch = rand()% 127;
    
    result[i] = str;
  }

  return result;
}


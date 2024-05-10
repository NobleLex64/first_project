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
  return 0;
}
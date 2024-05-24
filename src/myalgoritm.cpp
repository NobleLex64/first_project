#include "myalgoritm.h"

/* STL libraries */
#include <string>
#include <vector>

wchar_t alg::getCountsK(std::wstring_view text, const wchar_t k){

  wchar_t res = 0;

  for(auto it = text.cbegin(), end = text.cend(); it < end; ++it)
    if(*it == k)
      ++res;

  return res;
}

wchar_t alg::getOneBySize(std::wstring_view text){

  wchar_t count = 0;
  int cur_v = 0x1;

  for(auto it = text.crbegin(), end = text.crend(); it != end; ++it, cur_v <<= 1)
    count += (*it == L'1') ? cur_v : 0;
  
  return count;
}

std::wstring alg::getByteByBit(const wchar_t bit_mask, const unsigned char size){

  std::wstring res(size, '0');
  wchar_t bit = 1 << (size - 1);

  for(unsigned short i = 0; i < size; ++i)
  {
    if(bit & bit_mask)
      *(res.begin() + i) = L'1';
    
    bit >>= 1;
  }

  return res; 
};

void alg::eightXcompression(std::wstring_view text, std::wstring& result){

  for(size_t i = 0; i < text.size(); i += 8)
    result.push_back(alg::getOneBySize(text.substr(i, 8)));
}

std::pair<unsigned char, wchar_t> alg::getSizeAndValue(const wchar_t number)
{
  unsigned char size = 27;
  wchar_t value = L'\0';
  wchar_t bit = 0x800'0000;

  for(unsigned char i = 0; bit > 0; bit >>= 1, ++i)
    if(bit & number)
    {
      size -= i;
      break;
    }
  
  value = number - bit;

  return {size, value};
}

unsigned char alg::ln_2(unsigned long long num){

  unsigned char last = 1;
  unsigned char pre_last = 1;
  unsigned char i = 0;

  while(num)
  {
    if((num & 1) == 1)
    {
      pre_last = last;
      last = i;
    }

    ++i;
    num >>= 1;
  }

  return last = pre_last == last - 1? last + 1: last;
}

std::vector<size_t> alg::suffixArray(std::wstring_view data, const size_t N) 
{
  std::vector<int> rank(N), tmp_rank(N);
  std::vector<size_t> suffixArray(N);

  for(size_t i = 0; i < N; ++i)
    suffixArray[i] = i;
  
  for(size_t i = 0; i < N; ++i)
    rank[i] = data[i];
  
  for(size_t k = 0; k < N; k == 0 ? k = 1 : k <<= 1)
  {
    auto compare = [&](const size_t &A, const size_t &B)
    {
      if(rank[A] != rank[B]) return rank[A] < rank[B];

      int rA = rank[(A + k) % N];
      int rB = rank[(B + k) % N];

      return rA < rB;
    };

    std::sort(suffixArray.begin(), suffixArray.end(), compare);

    tmp_rank[suffixArray[0]] = 0;
    for(int i = 1; i < N; ++i)
      tmp_rank[suffixArray[i]] = tmp_rank[suffixArray[i - 1]] + compare(suffixArray[i - 1], suffixArray[i]);
    
    rank = tmp_rank;
  }

  return suffixArray;
}
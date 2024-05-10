#include "myalgoritm.h"

wchar_t alg::getMaxVal(std::wstring_view::iterator start, const std::wstring_view::iterator &end){
  wchar_t min_indx = WCHAR_MAX;

  while(start < end){

    if(*start < min_indx)
      min_indx = *start;
    
    ++start;
  }

  return min_indx;
}

wchar_t alg::getMinVal(std::wstring_view::iterator start, const std::wstring_view::iterator &end){
  wchar_t max_indx = WCHAR_MIN;

  while(start < end){

    if(*start > max_indx)
      max_indx = *start;
    
    ++start;
  }

  return max_indx;
}

wchar_t alg::getCountsK(std::wstring_view text, const wchar_t k){

  wchar_t res = 0;

  for(auto it = text.cbegin(), end = text.cend(); it < end; ++it)
    if(*it == k)
      ++res;

  return res;
}

wchar_t alg::getOneBySize(std::wstring_view text){

  wchar_t count = 0;
  int32_t cur_v = 0x1;

  for(auto it = text.crbegin(), end = text.crend(); it != end; ++it, cur_v <<= 1)
    count += (*it == L'1') ? cur_v : 0;
  
  return count;
}

std::wstring alg::getByteByBit(const wchar_t bit_mask, const uint8_t size){

  std::wstring res(size, '0');
  wchar_t bit = 1 << (size - 1);

  for(uint16_t i = 0; i < size; ++i)
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

std::pair<uint8_t, wchar_t> alg::getSizeAndValue(const wchar_t number)
{
  uint8_t size = 27;
  wchar_t value = L'\0';
  wchar_t bit = 0x800'0000;

  for(uint8_t i = 0; bit > 0; bit >>= 1, ++i)
    if(bit & number)
    {
      size -= i;
      break;
    }
  
  value = number - bit;

  return {size, value};
}

uint8_t alg::ln_2(unsigned long long num){

  uint8_t last = 1;
  uint8_t pre_last = 1;
  uint8_t i = 0;

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
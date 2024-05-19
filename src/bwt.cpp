#include "bwt.h"

/* My libs */
#include "myalgoritm.h"

/* 
  1) compression(...) -> return compression data, used suffix array
    Speed: O(N*logN), Memmory: O(N), where N - data.size(), SuffixArray - the space it occupies

  2) decompression(...) -> return decomression shifr, used many space
    Speed: O(N), Memmory: O(M.max - M.min), where N - shifr.size(), M.max, M.min - max, min value of alphabet
*/

std::wstring brrw::compression(std::wstring_view data)
{
  if(data.empty())
    return std::wstring();

  std::wstring shifr;
  shifr.reserve(data.size() + 1);

  wchar_t number = 0;

  std::vector<size_t> suffix_array = alg::suffixArray(data, data.size());

  for(auto it = suffix_array.cbegin(), end = suffix_array.cend(); it < end; ++it)
    if(*it != 0)
      shifr.push_back(data[*it - 1]);
    else  
    {
      number = static_cast<wchar_t>(std::distance(suffix_array.cbegin(), it));
      shifr.push_back(data.back());
    }
  
  size_t size = shifr.size();
  shifr.push_back(number);
  size = shifr.size();

  return shifr;
}

std::wstring brrw::decompression(std::wstring_view shifr)
{
  if(shifr.empty())
    return std::wstring();

  const size_t  Size = shifr.size();
  const wchar_t Min  = alg::getMinVal(shifr.begin(), shifr.end() - 1);

  std::wstring data{};
  data.reserve(Size - 1);

  std::vector<size_t> indces(Size - 1);
  {
    std::vector<size_t> rle(alg::getMaxVal(shifr.begin(), shifr.end() - 1) - Min + 1);

    for(auto it = shifr.begin(), end = shifr.end() - 1; it < end; ++it)
      ++rle[*it - Min];
    
    size_t index = 0;
    for(auto it = rle.begin(), end = rle.end(); it < end; ++it) {
      index += *it;
      *it = index - *it;
    }

    for(auto it = shifr.begin(), end = shifr.end() - 1; it < end; ++it)
    {
      index = rle[*it - Min]++;
      indces[index] = std::distance(shifr.begin(), it);
    }
  }

  for(size_t i = indces[shifr.back()]; data.size() != Size - 1; i = indces[i])
    data.push_back(shifr[i]);
  
  return data;
}
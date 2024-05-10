#include "mtf.h"

/* My libs */
#include "myalgoritm.h"

/*  STL libs */
#include <list>

/*  
  1) compression(...) -> return data after compresion
     Speed: O(N*(M.max - M.min)), Space: O(M.max - M.min), where N - data.size(), M.max, M.min - max, min alphabet value

  2) decompression(...) -> return data before compression
     Speed: O(N*(M.max - M.min)), Space: O(M.max - M.min), where N - shifr.size(), M.max, M.min - max, min alphabet value
*/

std::wstring mtf::compression(std::wstring_view data)
{
  if(data.empty())
    return std::wstring();

  std::wstring shifr;
  shifr.reserve(data.size() + 2);


  std::list<wchar_t> dict;
  {
    wchar_t min_val  = alg::getMinVal(data.begin(), data.end());
    wchar_t max_val  = alg::getMaxVal(data.begin(), data.end());

    std::wstring str(((max_val - min_val) + 1), L'\0');
    
    shifr.push_back(min_val);
    shifr.push_back(max_val);

    for(auto it = data.cbegin(); it < data.cend(); ++it)
      str[*it - min_val] = *it;
    
    for(auto it = str.cbegin(); it < str.cend(); ++it)
      dict.push_back(*it);
  }

  auto index = dict.begin();
  for(auto it = data.cbegin(); it < data.cend(); ++it)
  {
    index = std::find(dict.begin(), dict.end(), *it);
    wchar_t val = std::distance(dict.begin(), index);
    dict.erase(index);
    dict.push_front(*it);

    shifr.push_back(val);
  }

  return shifr;
}

std::wstring mtf::decompression(std::wstring_view shifr){

  if(shifr.empty())
    return std::wstring();

  std::wstring data;
  data.reserve(shifr.size() - 2);

  std::list<wchar_t> dict;
  {
    wchar_t min_val = *shifr.begin();
    const wchar_t max_val = *(shifr.begin() + 1);
    while(min_val <= max_val)
      dict.push_back(min_val++);
  }

  for(auto it = shifr.cbegin() + 2; it < shifr.cend(); ++it)
  { 
    wchar_t i = 0;
    for(auto start = dict.begin(); start != dict.end(); ++start, ++i)
      if(i == *it)
      {
        data.push_back(*start);
        dict.erase(start);
        dict.push_front(*start);
        break;
      }
  }

  return data;
} 
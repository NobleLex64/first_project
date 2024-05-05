#include "mtf.h"

inline wchar_t mtf::hlp::getMinVal(std::wstring_view::iterator start, const std::wstring_view::iterator& end){
  wchar_t min_indx = WCHAR_MAX;

  while(start < end){

    if(*start < min_indx)
      min_indx = *start;
    
    ++start;
  }

  return min_indx;
}

inline wchar_t mtf::hlp::getMaxVal(std::wstring_view::iterator start, const std::wstring_view::iterator& end){
  wchar_t max_indx = WCHAR_MIN;

  while(start < end){

    if(*start > max_indx)
      max_indx = *start;
    
    ++start;
  }

  return max_indx;
}

std::wstring mtf::compression(std::wstring_view data)
{
  if(data.empty())
    return std::wstring();

  std::wstring shifr;
  shifr.reserve(data.size() + 2);


  std::list<wchar_t> dict;
  {
    wchar_t min_val  = hlp::getMinVal(data.begin(), data.end());
    wchar_t max_val  = hlp::getMaxVal(data.begin(), data.end());

    std::wstring str(((max_val - min_val) + 1), L'\0');
    
    shifr.push_back(min_val);
    shifr.push_back(max_val);

    for(auto it = data.begin(); it < data.end(); ++it)
      str[*it - min_val] = *it;
    
    for(auto it = str.begin(); it < str.end(); ++it)
      dict.push_back(*it);
  }

  auto index = dict.begin();
  for(auto it = data.begin(); it < data.end(); ++it)
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
    wchar_t max_val = *(shifr.begin() + 1);
    while(min_val <= max_val)
      dict.push_back(min_val++);
  }

  for(auto it = shifr.begin() + 2; it < shifr.end(); ++it)
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
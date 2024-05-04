#include "bwt.h"

struct brrw::hlp::Suffix{
public:
  size_t _indx;
  std::wstring _suffix;
};

std::vector<size_t> brrw::hlp::getSuffixArray(std::wstring_view data, size_t size){

  std::vector<Suffix> arr_suffixs(size);

  for(auto it = arr_suffixs.begin(), end = arr_suffixs.end(); it < end; ++it)
  {
    (*it)._indx = std::distance(arr_suffixs.begin(), it);
    (*it)._suffix = data.substr((*it)._indx);
  }

  std::sort(arr_suffixs.begin(), arr_suffixs.end(), [](const Suffix& a, const Suffix& b){ return a._suffix < b._suffix;});

  std::vector<size_t> suffix_array(size);

  for(size_t i = 0; i < size; ++i)
    suffix_array[i] = arr_suffixs[i]._indx;
  
  return suffix_array;
}

std::wstring brrw::compression(std::wstring_view data)
{
  if(data.empty())
    return std::wstring();

  std::wstring shifr;
  
  size_t size = data.size();
  std::vector<size_t> suffix_array = hlp::getSuffixArray(data, size);

  shifr.reserve(size);

  for(auto it = suffix_array.begin(); it < suffix_array.end(); ++it)
    shifr.push_back(data[(*it + size - 1) % size]);

  return shifr;
}

inline uint16_t brrw::hlp::getMinVal(std::wstring_view::iterator start, const std::wstring_view::iterator& end){
  uint16_t min_indx = UINT16_MAX;

  while(start < end){

    if(*start < min_indx)
      min_indx = *start;
    
    ++start;
  }

  return min_indx;
}

inline uint16_t brrw::hlp::getMaxVal(std::wstring_view::iterator start, const std::wstring_view::iterator& end){
  uint16_t max_indx = 0;

  while(start < end){

    if(*start > max_indx)
      max_indx = *start;
    
    ++start;
  }

  return max_indx;
}

std::wstring brrw::decompression(std::wstring_view shifr){

  if(shifr.empty())
    return std::wstring();

  size_t size = shifr.size();
  std::wstring data;

  data.reserve(shifr.size());

  int16_t min_val = hlp::getMinVal(shifr.begin(), shifr.end());
  std::vector<size_t> rle((hlp::getMaxVal(shifr.begin(), shifr.end()) - min_val) + 1);

  for(auto it = shifr.begin(); it < shifr.end(); ++it)
    ++rle[*it - min_val];

  size_t indx = 0;
  for(auto it = std::begin(rle); it < std::end(rle); ++it)
  {
    indx += *(it);
    *(it) = indx - *(it);
  }
  
  std::vector<size_t> new_vec(shifr.size());
  for(auto it = shifr.begin(); it < shifr.end(); ++it)
  {
    indx = rle[*it - min_val]++;
    new_vec[indx] = std::distance(shifr.begin(), it);
  }

  for(auto it = new_vec.begin() + shifr.find(L'$'); data.size() != shifr.size();)
  {
    data.push_back(shifr[*it]);
    it = new_vec.begin() + *it;
    ++indx;
  }

  return data;
}
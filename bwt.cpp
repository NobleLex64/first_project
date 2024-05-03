#include "bwt.h"

struct brrw::hlp::Suffix{
public:
  size_t _indx;
  std::string _suffix;
};

std::vector<size_t> brrw::hlp::getSuffixArray(std::string_view data, size_t size){

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

std::string brrw::compression(std::string_view data)
{
  if(data.empty())
    return std::string();

  std::string shifr;
  
  size_t size = data.size();
  std::vector<size_t> suffix_array = hlp::getSuffixArray(data, size);

  shifr.reserve(size);

  for(auto it = suffix_array.begin(); it < suffix_array.end(); ++it)
    shifr.push_back(data[(*it + size - 1) % size]);

  return shifr;
}

std::string brrw::decompression(std::string_view shifr){

  std::string data;
  data.reserve(shifr.size());

  size_t rle[256]{}; 
  for(auto it = shifr.begin(); it < shifr.end(); ++it)
    ++rle[*it];

  size_t indx = 0;
  for(auto it = std::begin(rle); it < std::end(rle); ++it)
  {
    indx += *(it);
    *(it) = indx - *(it);
  }
  
  std::vector<size_t> new_vec(shifr.size());
  for(auto it = shifr.begin(); it < shifr.end(); ++it)
  {
    indx = rle[*it]++;
    new_vec[indx] = std::distance(shifr.begin(), it);
  }

  for(auto it = new_vec.begin() + shifr.find('$'); it < new_vec.end();)
  {
    if(data.size() == shifr.size())
      break;

    data.push_back(shifr[*it]);
    it = new_vec.begin() + *it;
    ++indx;
  }

  return data;
}
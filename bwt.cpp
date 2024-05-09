#include "bwt.h"

/* My libs */
#include "myalgoritm.h"


/* Struct for storing one element of a suffix array */

struct brrw::hlp::Suffix{
public:
  size_t _indx;
  std::wstring _suffix;
};

/* 
  1) getSuffixArray(..., ...) -> created suffix array, used vector<Suffix> 
     and sort with compare(a, b) return a.suffix < b.suffix;
     Speed: O(N), Memmory: ((N * (N + 1)) / 2), where  N - data.size().
*/

std::vector<size_t> brrw::hlp::getSuffixArray(std::wstring_view data, const size_t size){

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

/* 
  1) compression(...) -> return compression data, used suffix array
    Speed: O(N), Memmory: O(SuffixArray), where N - data.size(), SuffixArray - the space it occupies

  2) decompression(...) -> return decomression shifr, used many space
    Speed: O(N), Memmory: O(M.max - M.min), where N - shifr.size(), M.max, M.min - max, min value of alphabet
*/

std::wstring brrw::compression(std::wstring_view data)
{
  if(data.empty())
    return std::wstring();

  std::wstring shifr;
  
  size_t size = data.size();
  std::vector<size_t> suffix_array = hlp::getSuffixArray(data, size);

  shifr.reserve(size);

  for(auto it = suffix_array.cbegin(); it < suffix_array.cend(); ++it)
    shifr.push_back(data[(*it + size - 1) % size]);

  return shifr;
}

std::wstring brrw::decompression(std::wstring_view shifr){

  if(shifr.empty())
    return std::wstring();

  size_t size = shifr.size();
  std::wstring data;

  data.reserve(shifr.size());

  wchar_t min_val = alg::getMinVal(shifr.begin(), shifr.end());

  std::vector<size_t> rle((alg::getMaxVal(shifr.begin(), shifr.end()) - min_val) + 1);

  for(auto it = shifr.cbegin(), end = shifr.cend(); it < end; ++it)
    ++rle[*it - min_val];

  size_t indx = 0;
  for(auto it = std::begin(rle), end = std::end(rle); it < end; ++it)
  {
    indx += *(it);
    *(it) = indx - *(it);
  }
  
  std::vector<size_t> new_vec(shifr.size());
  for(auto it = shifr.cbegin(), end = shifr.cend(); it < end; ++it)
  {
    indx = rle[*it - min_val]++;
    new_vec[indx] = std::distance(shifr.cbegin(), it);
  }

  for(auto it = new_vec.begin() + shifr.find(L'$'); data.size() != shifr.size();)
  {
    data.push_back(shifr[*it]);
    it = new_vec.begin() + *it;
    ++indx;
  }

  return data;
}
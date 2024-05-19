#include "lz77.h"

/* STL libraries  */
#include <string>
#include <vector>
#include <list>

/* My libraries */
#include "myalgoritm.h"

inline auto lz77::helper::endSubstr(auto dict_beg, auto buff_beg, const auto buff_end)
{
  while(*dict_beg == *buff_beg && buff_beg < buff_end){
    ++dict_beg;
    ++buff_beg;
  }

  return buff_beg;
}

std::pair<int8_t, int16_t> lz77::helper::maxSubstr(std::list<size_t> &symbol, const auto data_beg, auto &buff_beg, auto buff_end){
  
  buff_end = std::min(buff_end, buff_beg + 15);

  int8_t count = 0;
  int8_t tmp_count;

  int16_t dist = 0;

  auto dist_beg = data_beg;
  auto dist_end = buff_end;

  for(auto start = symbol.begin(), end = symbol.end(); start != end; ++start){

    dist_beg = (data_beg + *start);
    dist_end  = endSubstr(dist_beg, buff_beg, buff_end);
    tmp_count = std::distance(buff_beg, dist_end);

    if(tmp_count > count)
    {
      count = tmp_count;
      dist  = std::distance(dist_beg, buff_beg);;
    }
  }

  buff_beg += count;

  return {count, dist};
}

inline void lz77::helper::addNewIndx(std::vector<std::list<size_t>> &alphavit, const auto data_beg, auto &buff_beg, auto &buff_end, wchar_t min_val){

  size_t dist = std::distance(data_beg, buff_beg);

  while(buff_beg <= buff_end)
    alphavit[*buff_beg++ - min_val].push_back(dist++);
}

std::wstring lz77::compression(std::wstring_view data)
{
  if(data.empty())
    return std::wstring();

  wchar_t min_val = alg::getMinVal(data.begin(), data.end());
  std::wstring shifr;
  std::vector<std::list<size_t>> alphavit(alg::getMaxVal(data.begin(), data.end()) - min_val + 1);

  shifr.reserve(data.size());

  std::pair<int8_t, int16_t> count_dist;

  auto beg = data.begin();

  for(auto it = beg, end = data.end(); it < end; ++it)
  {   
    auto start = it;

    while(!alphavit[*it - min_val].empty() && ((std::distance(beg, it) - alphavit[*it - min_val].front()) > 4080))
      alphavit[*it - min_val].pop_front();

    count_dist = helper::maxSubstr(alphavit[*it - min_val], beg, it, end);

    if(it < end)
      helper::addNewIndx(alphavit, beg, start, it, min_val);

    shifr.push_back((count_dist.second >> 4) & 0xFF);
    shifr.push_back(((count_dist.second << 4) & 0xF0) | (count_dist.first & 0x0F));
    shifr.push_back(*it);
  }

  if(shifr.back() == '\0')
    shifr.pop_back();

  return shifr;
}

std::wstring lz77::decompression(std::wstring_view shifr)
{
  if(shifr.empty())
    return std::wstring();

  std::wstring data;

  data.reserve(shifr.size());

  int8_t count = 0;
  int16_t dist = 0;

  for(auto iter = shifr.begin(); iter < shifr.end(); iter += 3){

    dist  = ((*iter << 4) & 0xFF0) + ((*(iter + 1) >> 4) & 0x0F);
    count = *(iter + 1) & 0x0F;

    if(count == 0)
      data.push_back(*(iter + 2));
    else
    {
      size_t start = data.size() - dist;

      while(count--)
        data.push_back(data[start++]);
      
      if((iter + 2) < shifr.end())
        data.push_back(*(iter + 2));
    }
  }

  return data;
}

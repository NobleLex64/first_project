#include "lz77.h"

/*  */

inline _ITER_S_W lz77::hlp::endSubstr(_ITER_S_W dict_beg, _ITER_S_W buff_beg, const _ITER_S_W buff_end)
{
  while(*dict_beg == *buff_beg && buff_beg < buff_end){
    ++dict_beg;
    ++buff_beg;
  }

  return buff_beg;
}

std::pair<int8_t, int16_t> lz77::hlp::maxSubstr(std::list<size_t> &symbol, const _ITER_S_W data_beg, _ITER_S_W &buff_beg, _ITER_S_W buff_end){
  
  buff_end = std::min(buff_end, buff_beg + 15);

  int8_t count = 0;
  int8_t tmp_count;

  int16_t dist = 0;

  _ITER_S_W dist_beg = data_beg;
  _ITER_S_W dist_end = buff_end;

  for(_ITER_L start = symbol.begin(), end = symbol.end(); start != end; ++start){

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

inline void lz77::hlp::addNewIndx(std::vector<std::list<size_t>> &alphavit, const _ITER_S_W data_beg, _ITER_S_W &buff_beg, _ITER_S_W &buff_end){

  size_t dist = std::distance(data_beg, buff_beg);

  while(buff_beg <= buff_end)
    alphavit[*buff_beg++].push_back(dist++);
}

/*  */

std::wstring lz77::compression(std::wstring_view data)
{
  if(data.empty())
    return std::wstring();

  std::wstring shifr;
  std::vector<std::list<size_t>> alphavit(0xFF);

  shifr.reserve(data.size());

  std::pair<int8_t, int16_t> count_dist;

  _ITER_S_W beg = data.begin();

  for(_ITER_S_W it = beg, end = data.end(); it < end; ++it)
  {   
    _ITER_S_W start = it;

    while(!alphavit[*it].empty() && ((std::distance(beg, it) - alphavit[*it].front()) > 4080))
      alphavit[*it].pop_front();

    count_dist = hlp::maxSubstr(alphavit[*it], beg, it, end);

    if(it < end)
      hlp::addNewIndx(alphavit, beg, start, it);

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

  for(_ITER_S_W iter = shifr.begin(); iter < shifr.end(); iter += 3){

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

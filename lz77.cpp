#include "lz77.h"

inline _ITER_S_W lz77::hlp::endSubstr(_ITER_S_W dict_beg, _ITER_S_W buff_beg, const _ITER_S_W buff_end)
{
  // while equal, move to the right
  while(*dict_beg == *buff_beg && buff_beg < buff_end){
    ++dict_beg;
    ++buff_beg;
  }

  // returns the end of the shift
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

    // select the largest substring
    if(tmp_count > count)
    {
      count = tmp_count;
      dist  = std::distance(dist_beg, buff_beg);;
    }
  }

  buff_beg += count;

  // return count, distance
  return {count, dist};
}

inline void lz77::hlp::addNewIndx(std::vector<std::list<size_t>> &alphavit, const _ITER_S_W data_beg, _ITER_S_W &buff_beg, _ITER_S_W &buff_end){

  size_t dist = std::distance(data_beg, buff_beg);

  while(buff_beg <= buff_end)
    alphavit[*buff_beg++].push_back(dist++);
}

std::string lz77::compression(std::string_view data)
{
  // checking for emptiness
  if(data.empty())
    return std::string();

  // shifr    -> data compression.
  // alphavit -> Stores indices of all symbols for quick access to them.
  std::string shifr;
  std::vector<std::list<size_t>> alphavit(0xFF);

  // Reserving space for O(1) - 'push_back'
  shifr.reserve(data.size());

  // count -> The numbers of characters in substr.
  // dist  -> The distance between the current symbol and the desired substring.
  std::pair<int8_t, int16_t> count_dist;

  // iter of start data
  _ITER_S_W beg = data.begin();

  // Using iterators to iterating through the data
  // it  -> start of sliding window buffer zone
  // end -> end of data
  for(_ITER_S_W it = beg, end = data.end(); it < end; ++it)
  {   
    _ITER_S_W start = it;

    // delete dist > 4080
    while(!alphavit[*it].empty() && ((std::distance(beg, it) - alphavit[*it].front()) > 4080))
      alphavit[*it].pop_front();

    // initializing count and dist with maxsubstr val
    count_dist = hlp::maxSubstr(alphavit[*it], beg, it, end);

    // add new indecises in alphavit
    if(it < end)
      hlp::addNewIndx(alphavit, beg, start, it);

    // <d, l, n> - lz77, 2 bytes added for dist, lenght and 1 byte for next char
    shifr.push_back((count_dist.second >> 4) & 0xFF);
    shifr.push_back(((count_dist.second << 4) & 0xF0) | (count_dist.first & 0x0F));
    shifr.push_back(*it);
  }

  if(shifr.back() == '\0')
    shifr.pop_back();
  // return result of compression
  return shifr;
}

std::string lz77::decompression(std::string_view shifr)
{
  // checking for emptiness
  if(shifr.empty())
    return std::string();

  // data -> shifr decompression.
  std::string data;

  // reserve data for O(1) - 'push_back'
  data.reserve(shifr.size());

  // count -> The numbers of characters in substr.
  // dist  -> The distance between the current symbol and the desired substring.
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

#include "rle.h"

uint8_t rle::hlp::countsComboChar(std::string_view text, std::string_view::iterator& it){

  auto beg = it - 1;
  auto end = text.end() - it > 128 ? it + 128: text.end();

  while(it != end && *it == *(it - 1))
    ++it;

  return static_cast<uint8_t>(it - beg);
}

uint8_t rle::hlp::countsSingleChar(std::string_view text, std::string_view::iterator& it){

  auto beg = it - 1;
  auto end = text.end() - it > 128 ? it + 128: text.end();

  while(it != end && *it != *(it - 1))
    ++it;

  return static_cast<uint8_t>(--it - beg);
}

void rle::compressionString(std::string_view text, std::string& shifr)
{
  if(!shifr.empty())
    shifr.clear();

  shifr.reserve(text.size());

  uint8_t len = 0;

  for(auto it = text.begin() + 1, end = text.end(); it < end; ++it)
  {
    len = hlp::countsComboChar(text, it);
    
    if(len > 1)
    {
      shifr.push_back(len - 2 | OLD_BIT);
      shifr.push_back(*(it - 1));
    }
    else
    {
      auto start = it - 1;
      len = hlp::countsSingleChar(text, it);
      shifr.push_back(len - 1);
      shifr.insert(shifr.size(), text, (start - text.begin()), len);
    }
  }

  if(shifr.back() != text.back())
  {
    shifr.push_back(0);
    shifr.push_back(text.back());
  }
}

std::string rle::decompressionString(std::string_view shifr)
{
  if(shifr.empty())
    return std::string();

  uint8_t count = 0;

  std::string decomp_text;
  decomp_text.reserve(shifr.size());

  for(auto it = shifr.begin(), end = shifr.end() - 1; it < end; ++it){

    count = *it;

    if((count & OLD_BIT) == OLD_BIT)
    {
      count = (count & INT8_MAX) + 2;
      decomp_text.insert(decomp_text.end(), count, *(++it));
    }
    else
    {
      decomp_text.insert(decomp_text.size(), shifr, (it - shifr.begin()) + 1, count + 1);
      it += (count + 1);
    }
  }

  return decomp_text;
}
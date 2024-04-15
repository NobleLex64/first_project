#include "rle.h"

uint8_t rle::hlp::countsComboChar(const std::string& text, size_t& i){

  size_t start = i - 1;

  while(i < text.size() && i - start < 129 && text[i] == text[i - 1])
    ++i;

  return i - start;
}

uint8_t rle::hlp::countsSingleChar(const std::string& text, std::string& shifr, size_t& i){

  size_t start = i;

  while(i < text.size() && i - start < 128 && text[i] != text[i - 1])
  {
    shifr.push_back(text[i - 1]);
    ++i;
  }

  if(i - start < 128 && i == text.size())
  {
    shifr.push_back(text[i - 1]);
    ++i;
  }

  return i - start;
}

void rle::compressionString(const std::string &text, std::string &shifr)
{
  if(!shifr.empty())
    shifr.clear();
  
  uint8_t len = 0;

  for(size_t i = 1, n = text.size(); i < n; len = 0)
  {
    if(text[i] == text[i - 1])
    {
      len = hlp::countsComboChar(text, i);
      shifr.push_back(len - 2 | OLD_BIT);
      shifr.push_back(text[i - 1]);
      ++i;
    }
    else if(text[i] != text[i - 1])
    {
      shifr.push_back(len);
      len = hlp::countsSingleChar(text, shifr, i) + 1;
      shifr[shifr.size() - len] = len - 2;
    }
  }

  if(shifr.back() != text.back())
  {
    shifr.push_back(0);
    shifr.push_back(text.back());
  }
}

std::string rle::decompressionString(std::string &shifr)
{
  if(shifr.empty())
    return std::string();

  uint8_t count = 0;

  std::string decomp_text;

  for(uint64_t i = 0, n = shifr.size(); i < n;){

    count = shifr[i];

    if((count & OLD_BIT) == OLD_BIT)
    {
      count = (count & INT8_MAX) + 2;
      decomp_text.insert(decomp_text.end(), count, shifr[i + 1]);
      i += 2;
    }
    else
    {
      while(count != 255)
      {
        decomp_text.push_back(shifr[++i]);
        --count;
      }
      i += 1;
    }
  }

  return decomp_text;
}
#include "rle.h"

/* STL libraries */
#include <string>

uint16_t rle::helper::countsComboChars(std::wstring_view text, std::wstring_view::iterator &it, const uint16_t max){
  if(it == text.end())
    return 1;

  auto beg = it;
  auto end = std::min(it + max, text.end());

  while(it < end && *it == *(++it));

  return static_cast<uint16_t>(std::distance(beg, it--));
}

uint16_t rle::helper::countsSingleChar(std::wstring_view text, std::wstring_view::iterator &it, const uint16_t max){
  if(it == text.end())
    return 1;

  auto beg = it;
  auto end = std::min(it + max, text.end());

  while(it < end && *it != *(it + 1))
    ++it;

  return static_cast<uint16_t>(std::distance(beg, it--));
}


void rle::helper::compressionTxt(std::wstring_view text, std::wstring &shifr){
  uint8_t len = 0;

  for(auto it = text.begin(), end = text.end(); it < end; ++it)
  {
    len = countsComboChars(text, it, 129);
    
    if(len > 1)
    {
      shifr.push_back((len - 2) | 128);
      shifr.push_back(*it);
    }
    else
    {
      auto start = it;
      len = countsSingleChar(text, it, 128);
      shifr.push_back(len - 1);
      shifr.insert(shifr.size(), text, std::distance(text.begin(), start), len);
    }
  }
}

void rle::helper::compressionImg(std::wstring_view image, std::wstring& shifr){
  uint8_t bit1 = 0;
  uint8_t bit2 = 0;
  uint16_t len = 0;

  for(auto it = image.begin(), end = image.end(); it < end; ++it)
  {
    len = countsComboChars(image, it, 16385);

    if(len > 1)
    { 
      len -= 2;
      if(len > 65)
      {
        bit1 = (len >> 8) | 192;
        bit2 = len & 255;
        shifr.push_back(bit1);
        shifr.push_back(bit2);
      }
      else
      {
        bit1 = len | 128;
        shifr.push_back(bit1);
      }

      shifr.push_back(*it);
    }
    else
    {
      auto start = it;
      len = countsSingleChar(image, it, 16384) - 1;

      if(len > 64)
      {
        bit1 = (len >> 8) | 64;
        bit2 = len & 255;
        shifr.push_back(bit1);
        shifr.push_back(bit2);
      }
      else
        shifr.push_back(static_cast<uint8_t>(len));

      shifr.insert(shifr.size(), image, std::distance(image.begin(), start), len + 1);
    }
  }
}


size_t rle::helper::newSizeTxt(std::wstring_view text){
  uint8_t len = 0;
  size_t size = 0;

  for(auto it = text.begin(), end = text.end(); it < end; ++it)
  {
    len = countsComboChars(text, it, 128);

    if(len > 1)
      size += 2;
    else
    {
      len = countsSingleChar(text, it, 128);
      size += len + 1;
    }
  }
  return size;
}

size_t rle::helper::newSizeImg(std::wstring_view image){
  uint16_t len = 0;
  size_t size  = 0;

  for(auto it = image.begin(), end = image.end(); it < end; ++it)
  {
    len = countsComboChars(image, it, 16384);

    if(len > 1)
    {
      if(len > 65)
        size += 3;
      else
        size += 2;
    }
    else
    {
      len = countsSingleChar(image, it);

      if(len > 64)
        size += len + 2;
      else
        size += len + 1;
    }
  }

  return size;
}


size_t rle::helper::newSizeShifrTxt(std::wstring_view text){
  size_t size = 0;

    for (auto it = text.begin() + 1, end = text.end() - 1; it < end; ++it)
      if ((*it & 128) == 128){
        size += (*it & 127) + 2;
        ++it;
      }
      else{
        size += (*it & 127) + 1;
        it   += size;
      }
    
    return size;
}

size_t rle::helper::newSizeShifrImg(std::wstring_view image){
  size_t size = 0;

  for (auto it = image.begin() + 1, end = image.end() - 1; it < end; ++it)
      if ((*it & 128) == 128){
        if((*it & 64) == 64){
          size += (*it & 63) * 256 + (*(it + 1) & 255) + 2;
          it += 2;
        }
        else
        {
          size += (*it & 63) + 2;
          ++it;
        }
      }
      else{
        if((*it & 64) == 64){
          size += (*it & 63) * 256 + (*(it + 1) & 255) + 1;
          it += *it + 2;
        }
        else
        {
          size += (*it & 63) + 1;
          it += *it + 1;
        }
      }
  return size;
}


void rle::helper::decompressionTxt(std::wstring_view shifr, std::wstring& text){
  uint8_t count = 0;
  for(auto it = shifr.begin() + 1, end = shifr.end() - 1; it < end; ++it)
    if((*it & 128) == 128)
    {
      count = (*it & 127) + 2;
      text.insert(text.end(), count, *(++it));
    }
    else
    {
      count = (*it & 127) + 1;
      text.insert(text.size(), shifr, std::distance(shifr.begin(), it) + 1, count);
      it += count;
    }
}

void rle::helper::decompressionImg(std::wstring_view shifr, std::wstring& image){
  uint16_t count = 0;

  for(auto it = shifr.begin() + 1, end = shifr.end() - 1; it < end; ++it){
    if ((*it & 128) == 128){
      if((*it & 64) == 64)
      {
        count = (*it & 63) * 256 + (*(it + 1) & 255) + 2;
        image.insert(image.end(), count, *(it + 2));
        it += 2;
      }
      else
      {
        count = (*it & 63) + 2;
        image.insert(image.end(), count, *(++it));
      }
    }
    else{
      if((*it & 64) == 64){
        count = (*it & 63) * 256 + (*(it + 1) & 255) + 1;
        image.insert(image.size(), shifr, std::distance(shifr.begin(), it) + 2, count);
        it += count;
      }
      else
      {
        count = (*it & 63) + 1;
        image.insert(image.size(), shifr, std::distance(shifr.begin(), it) + 1, count);
        it += count;
      }
    }
  }
}


std::wstring rle::compression(std::wstring_view data)
{
  if (data.empty())
    return std::wstring();

  std::wstring shifr = L"";
  size_t new_size_text  = helper::newSizeTxt(data);
  size_t new_size_image = helper::newSizeImg(data);

  if (new_size_text <= new_size_image)
  {
    shifr.reserve(new_size_text + 1);
    shifr.push_back(L'\0');
    helper::compressionTxt(data, shifr);
  }
  else
  {
    shifr.reserve(new_size_image + 1);
    shifr.push_back(L'\377');
    helper::compressionImg(data, shifr); 
  }

  return shifr;
}

std::wstring rle::decompression(std::wstring_view shifr)
{
  if(shifr.empty())
    return std::wstring();
  
  std::wstring data = L"";

  if(shifr[0] == L'\0')
  {
    data.reserve(helper::newSizeShifrTxt(shifr));
    helper::decompressionTxt(shifr, data);
  }
  else
  {
    data.reserve(helper::newSizeShifrImg(shifr));
    helper::decompressionImg(shifr, data);
  }

  return data;
}

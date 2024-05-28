#include "rle.h"

/* STL libraries */
#include <string>

unsigned short rle::helper::countsComboChars(std::wstring_view::const_iterator &start, const std::wstring_view::const_iterator &end){
  if(start == end)
    return 1;

  std::wstring_view::const_iterator beggin = start;

  while(start < end && *start == *(start + 1))
    ++start;

  return (static_cast<unsigned short>(std::distance(beggin, start)) + 1);
}

unsigned short rle::helper::countsSingleChar(std::wstring_view::const_iterator &start, const std::wstring_view::const_iterator &end){
  if(start == end)
    return 1;

  std::wstring_view::const_iterator beggin = start;

  while(start < end && *start != *(start + 1))
    ++start;

  if(start != end)
    return static_cast<unsigned short>(std::distance(beggin, start--));
  else
    return (static_cast<unsigned short>(std::distance(beggin, start)) + 1);
}


void rle::helper::compressionTxt(std::wstring_view text, std::wstring &shifr){
  unsigned char len = 0;

  for(auto it = text.begin(), end = (text.end() - 1); it <= end; ++it)
  {
    std::wstring_view::const_iterator curr_end = std::distance(it, end) > 128 ? it + 128 : end;

    len = static_cast<unsigned char>(countsComboChars(it, curr_end));
    
    if(len > 1)
    {
      shifr.push_back((len - 2) | 128);
      shifr.push_back(*it);
    }
    else
    {
      auto start = it;
      len = static_cast<unsigned char>(countsSingleChar(it, curr_end));
      shifr.push_back(len - 1);
      shifr.insert(shifr.size(), text, std::distance(text.begin(), start), len);
    }
  }
}

void rle::helper::compressionImg(std::wstring_view image, std::wstring& shifr){
  unsigned char bit1 = 0;
  unsigned char bit2 = 0;
  unsigned short len = 0;

  for(auto it = image.begin(), end = (image.end() - 1); it <= end; ++it)
  {
    std::wstring_view::const_iterator curr_end = std::distance(it, end) > 16384 ? it + 16384 : end;

    len = countsComboChars(it, curr_end);

    if(len > 1)
    { 
      len -= 2;
      if(len > 63)
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
      len = countsSingleChar(it, curr_end) - 1;

      if(len > 63)
      {
        bit1 = (len >> 8) | 64;
        bit2 = len & 255;
        shifr.push_back(bit1);
        shifr.push_back(bit2);
      }
      else
        shifr.push_back(static_cast<unsigned char>(len));

      size_t s = std::distance(image.begin(), start);
      shifr.insert(shifr.size(), image, std::distance(image.begin(), start), len + 1);
    }
  }
}


unsigned long long rle::helper::newSizeTxt(std::wstring_view text){
  unsigned char len = 0;
  unsigned long long size = 0;

  for(auto it = text.begin(), end = (text.end() - 1); it <= end; ++it)
  {
    std::wstring_view::const_iterator curr_end = std::distance(it, end) > 128 ? it + 128 : end;

    len = static_cast<unsigned char>(countsComboChars(it, curr_end));

    if(len > 1)
      size += 2;
    else
    {
      len = static_cast<unsigned char>(countsSingleChar(it, curr_end));
      size += len + 1;
    }
  }
  return size;
}

unsigned long long rle::helper::newSizeImg(std::wstring_view image){
  unsigned short len = 0;
  unsigned long long size  = 0;

  for(auto it = image.begin(), end = (image.end() - 1); it <= end; ++it)
  {
    std::wstring_view::const_iterator curr_end = std::distance(it, end) > 16384 ? it + 16384 : end;

    len = countsComboChars(it, curr_end);

    if(len > 1)
    {
      len -= 2;
      if(len > 63)
        size += 3;
      else
        size += 2;
    }
    else
    {
      len = countsSingleChar(it, curr_end) - 1;

      if(len > 63)
        size += len + 3;
      else
        size += len + 2;
    }
  }

  return size;
}


unsigned long long rle::helper::newSizeShifrTxt(std::wstring_view text){
  unsigned long long size = 0;

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

unsigned long long rle::helper::newSizeShifrImg(std::wstring_view image){
  unsigned long long size = 0;

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
          it += size + 1;
        }
        else
        {
          size += (*it & 63) + 1;
          it += size;
        }
      }
  return size;
}


void rle::helper::decompressionTxt(std::wstring_view shifr, std::wstring& text){
  unsigned char count = 0;
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
  unsigned short count = 0;

  for(auto it = shifr.begin() + 1, end = shifr.end() - 1; it < end; ++it){
    if ((*it & 128) == 128){
      if((*it & 64) == 64)
      {
        count = (*it & 63) * 256 + (*(it + 1) & 255) + 2;
        it += 2;
        image.insert(image.end(), count, *it);
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
        it += count + 1;
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
  unsigned long long new_size_text  = helper::newSizeTxt(data);
  unsigned long long new_size_image = helper::newSizeImg(data);

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
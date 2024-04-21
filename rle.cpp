#include "rle.h"

// rle::hlp
// 

uint16_t rle::hlp::countsComboChars(std::string_view text, std::string_view::iterator& it, const uint16_t max){
  if(it == text.end())
    return 1;

  auto beg = it;
  auto end = std::min(it + max, text.end());

  while(it < end && *it == *(++it));

  return static_cast<uint16_t>(std::distance(beg, it--));
}

uint16_t rle::hlp::countsSingleChar(std::string_view text, std::string_view::iterator& it, const uint16_t max){

  if(it == text.end())
    return 1;

  auto beg = it;
  auto end = std::min(it + max, text.end());

  // abcdef -> ++it, ++it, ++it, ++it, ++it
  while(it < end && *it != *(it + 1))
    ++it;

  return static_cast<uint16_t>(std::distance(beg, it--));
}


void rle::hlp::compressionTxt(std::string_view text, std::string& shifr){
  uint8_t len = 0;

  for(auto it = text.begin(), end = text.end(); it < end; ++it)
  {
    len = countsComboChars(text, it, 128);
    
    if(len > 1)
    {
      shifr.push_back(len - 2 | 128);
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

void rle::hlp::compressionImg(std::string_view image, std::string& shifr){
  uint8_t bit1 = 0;
  uint8_t bit2 = 0;
  uint16_t len = 0;

  for(auto it = image.begin(), end = image.end(); it < end; ++it)
  {
    len = countsComboChars(image, it, 16384);

    if(len > 1)
    { 
      if(len > 65)
      {
        bit1 = (len >> 8) | 192;
        bit2 = (len - 2) & 255;
        shifr.push_back(bit1);
        shifr.push_back(bit2);
      }
      else
      {
        bit1 = len - 2 | 128;
        shifr.push_back(bit1);
      }

      shifr.push_back(*it);
    }
    else
    {
      auto start = it;
      len = countsSingleChar(image, it, 16384);

      if(len > 64)
      {
        bit1 = (len >> 8) | 64;
        bit2 = (len - 1) & 255;
        shifr.push_back(bit1);
        shifr.push_back(bit2);
      }
      else
      {
        bit1 = len - 1;
        shifr.push_back(bit1);
      }

      shifr.insert(shifr.size(), image, std::distance(image.begin(), start), len);
    }
  }
}


size_t rle::hlp::newSizeTxt(std::string_view text){
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

size_t rle::hlp::newSizeImg(std::string_view image){
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


size_t rle::hlp::newSizeShifrTxt(std::string_view text){
  size_t size = 0;

    for (auto it = text.begin() + 1, end = text.end() - 1; it < end; ++it)
      if ((*it & 128) == 128){
        size += (*it & 127) + 2;
        ++it;
      }
      else{
        size += *it + 1;
        it   += *it + 1;
      }
    
    return size;
}

size_t rle::hlp::newSizeShifrImg(std::string_view image){
  size_t size = 0;

  for (auto it = image.begin() + 1, end = image.end() - 1; it < end; ++it)
      if ((*it & 128) == 128){
        if((*it & 64) == 64){
          size += (*it & 63) * 256 + (*(it + 1) & 127) + 2;
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
          size += (*it & 63) * 256 + (*(it + 1) & 127) + 1;
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


void rle::hlp::decompressionTxt(std::string_view shifr, std::string& text){
  uint8_t count = 0;
  for(auto it = shifr.begin() + 1, end = shifr.end() - 1; it < end; ++it)
    if((*it & 128) == 128)
    {
      count = (*it & 127) + 2;
      text.insert(text.end(), count, *(++it));
    }
    else
    {
      text.insert(text.size(), shifr, std::distance(shifr.begin(), it) + 1, *it + 1);
      it += (*it + 1);
    }
}

void rle::hlp::decompressionImg(std::string_view shifr, std::string& image){
  uint16_t count = 0;

  for(auto it = shifr.begin() + 1, end = shifr.end() - 1; it < end; ++it){
    if ((*it & 128) == 128){
      if((*it & 64) == 64)
      {
        count = (*it & 63) * 256 + *(it + 1) + 2;
        image.insert(image.end(), count, *(it + 2));
        it += 2;
      }
      else
      {
        count = ((*it & 127) + 2);
        image.insert(image.end(), count, *(++it));
      }
    }
    else{
      if((*it & 64) == 64){
        image.insert(image.size(), shifr, std::distance(shifr.begin(), it) + 2, *it + 1);
        it += (*it + 2);
      }
      else
      {
        image.insert(image.size(), shifr, std::distance(shifr.begin(), it) + 1, *it + 1);
        it += (*it + 1);
      }
    }
  }
}

// rle
// 

std::string rle::compression(std::string_view data)
{
  if (data.empty())
    return std::string();

  std::string shifr = "";
  size_t new_size_text  = hlp::newSizeTxt(data);
  size_t new_size_image = hlp::newSizeImg(data);

  if (new_size_text <= new_size_image)
  {
    shifr.reserve(new_size_text + 1);
    shifr.push_back('\0');
    hlp::compressionTxt(data, shifr);
  }
  else
  {
    shifr.reserve(new_size_image + 1);
    shifr.push_back('\377');
    hlp::compressionImg(data, shifr); 
  }

  return shifr;
}

std::string rle::decompression(std::string_view shifr)
{
  if(shifr.empty())
    return std::string();
  
  std::string data = "";

  if(shifr[0] == '\0')
  {
    data.reserve(hlp::newSizeShifrTxt(shifr));
    hlp::decompressionTxt(shifr, data);
  }
  else
  {
    data.reserve(hlp::newSizeShifrImg(shifr));
    hlp::decompressionImg(shifr, data);
  }

  return data;
}

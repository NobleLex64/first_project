#ifndef PROJECT02_SRC_MYALGORITM_H_
#define PROJECT02_SRC_MYALGORITM_H_ 1

/// produced.. Noble_lex 64, 05.2024
/// algoritm 'MTF' - move to front
/// used in my libs "bwt.h", "mtf.h", "haffman.h"

/* STL libraries */
#include <string>
#include <vector>

namespace alg{

/// @brief this function return max charaters val ('a' = 97 ... '\0' = 0)
/// @param start iterator points on start data 
/// @param end iterator points on end of data
/// @return max characters val
template <typename T>
wchar_t getMaxVal(T start, const T &end){
  wchar_t max_indx = WCHAR_MIN;

  while(start < end){

    if(*start > max_indx)
      max_indx = *start;
    
    ++start;
  }

  return max_indx;
}

/// @brief this function return min charaters val ('a' = 97 ... '\0' = 0)
/// @param start iterator points on start data 
/// @param end iterator points on end of data
/// @return min characters val
template <typename T>
wchar_t getMinVal(T start, const T &end){
  wchar_t min_indx = WCHAR_MAX;

  while(start < end){

    if(*start < min_indx)
      min_indx = *start;
    
    ++start;
  }

  return min_indx;
}

/// @brief return counts of k in text
/// @param text data where search and counts k
/// @return count of k
wchar_t getCountsK(std::wstring_view text, const wchar_t k);

/// @brief converts wstring format ('1' or '0') to number
/// @param text wstring format ('1' or '0')
/// @return number in wchar_t
wchar_t getOneBySize(std::wstring_view text);

/// @brief converts number to wstring format ('1' or '0')
/// @param bit_mask number
/// @param size how many bits in number need converts
/// @return number in wstring
std::wstring getByteByBit(const wchar_t bit_mask, const unsigned char size);

/// @brief compress every 8 byte in 1 byte
/// @param text what compressed
/// @param result what will happen
void eightXcompression(std::wstring_view text, std::wstring& result);

/// @brief get size in bits and value after first '1' 
/// @param number number from 0 to 2^27
/// @return pair<size, value>
std::pair<unsigned char, wchar_t> getSizeAndValue(const wchar_t number);

/// @brief integer logarithm to base 2
/// @param num number from 0 to 2^64
/// @return ln(num)
unsigned char ln_2(unsigned long long num);

/// @brief return ln2(num), if num < 2^k return k - 1
/// @param num number for ln2
/// @return power of two
constexpr unsigned char ln_2_hard(unsigned long long num) noexcept
{
  unsigned char count = 0;
  while(num)
  {
    num >>= 1;
    ++count;
  }

  return count;
}

/// @brief suffix array, indices where up < low
/// @param data data what transformed in suffix array
/// @param N size of data
/// @return sufffix array
std::vector<size_t> suffixArray(std::wstring_view data, const size_t N);

} // alg

#endif // PROJECT02_SRC_MYALGORITM_H_
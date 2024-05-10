#ifndef NOBLELEX64_ALGORITMS_FOR_VOMPRESSION
#define NOBLELEX64_ALGORITMS_FOR_VOMPRESSION

/// produced.. Noble_lex 64, 05.2024
/// algoritm 'MTF' - move to front
/// used in my libs "bwt.h", "mtf.h", "haffman.h"

//STL libs
#include <string>

namespace alg{

  /// @brief this function return max charaters val ('a' = 97 ... '\0' = 0)
  /// @param start iterator points on start data 
  /// @param end iterator points on end of data
  /// @return max characters val
  wchar_t getMaxVal(std::wstring_view::iterator start, const std::wstring_view::iterator &end);

  /// @brief this function return min charaters val ('a' = 97 ... '\0' = 0)
  /// @param start iterator points on start data 
  /// @param end iterator points on end of data
  /// @return min characters val
  wchar_t getMinVal(std::wstring_view::iterator start, const std::wstring_view::iterator &end);

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
  std::wstring getByteByBit(const wchar_t bit_mask, const uint8_t size);

  /// @brief compress every 8 byte in 1 byte
  /// @param text what compressed
  /// @param result what will happen
  void eightXcompression(std::wstring_view text, std::wstring& result);

  /// @brief get size in bits and value after first '1' 
  /// @param number number from 0 to 2^27
  /// @return pair<size, value>
  std::pair<uint8_t, wchar_t> getSizeAndValue(const wchar_t number);

  /// @brief integer logarithm to base 2
  /// @param num number from 0 to 2^64
  /// @return ln(num)
  uint8_t ln_2(unsigned long long num);
}

#endif // NOBLELEX64_ALGORITMS_FOR_VOMPRESSION
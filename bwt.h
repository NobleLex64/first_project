#ifndef COMPRESSION_ALGORTIM_BURROWS_WHEELER
#define COMPRESSION_ALGORTIM_BURROWS_WHEELER

#include <string>
#include <vector>
#include <iostream>

namespace brrw{

  namespace hlp{

    /// @brief suffix and it index
    struct Suffix;

    /// @brief return suffix_array
    /// @param data data from which the prefix array is composed
    /// @param size data size
    /// @return resulting suffix array
    std::vector<size_t> getSuffixArray(std::wstring_view data, size_t size);

    /// @brief this function return min charaters val ('a' = 97 ... '\0' = 0)
    /// @param start iterator points on start data 
    /// @param end iterator points on end of data
    /// @return min characters val 
    inline uint16_t getMinVal(std::wstring_view::iterator start, const std::wstring_view::iterator &end);
    
    /// @brief this function return max charaters val ('a' = 97 ... '\0' = 0)
    /// @param start iterator points on start data 
    /// @param end iterator points on end of data
    /// @return max characters val
    inline uint16_t getMaxVal(std::wstring_view::iterator start, const std::wstring_view::iterator &end);
  }
  
  /// @brief this function get data(text or another) and compression it used alg burrows - wheeler
  /// @param data text or another 
  /// @return compression data
  std::wstring compression(std::wstring_view data);

  /// @brief this function get shifr(barrouws_wheeler) and decompression it
  /// @param shifr compression data
  /// @return decompression shifr
  std::wstring decompression(std::wstring_view shifr);

}
#endif // COMPRESSION_ALGORTIM_BURROWS_WHEELER
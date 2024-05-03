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
    std::vector<size_t> getSuffixArray(std::string_view data, size_t size);
  }
  /// @brief this function get data(text or another) and compression it used alg burrows - wheeler
  /// @param data text or another 
  /// @return compression data
  std::string compression(std::string_view data);

  /// @brief this function get shifr(barrouws_wheeler) and decompression it
  /// @param shifr compression data
  /// @return decompression shifr
  std::string decompression(std::string_view shifr);

}
#endif // COMPRESSION_ALGORTIM_BURROWS_WHEELER
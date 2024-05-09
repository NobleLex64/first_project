#ifndef COMPRESSION_ALGORTIM_BURROWS_WHEELER
#define COMPRESSION_ALGORTIM_BURROWS_WHEELER

/// produced.. Noble_lex 64, 05.2024
/// algoritm burrows wheeler
/// used my libs "myAlg.h"

// STL libs
#include <string>
#include <vector>

namespace brrw{

  namespace hlp{

    /// @brief suffix and it index
    struct Suffix;

    /// @brief return suffix_array
    /// @param data data from which the prefix array is composed
    /// @param size data size
    /// @return resulting suffix array
    std::vector<size_t> getSuffixArray(std::wstring_view data, size_t size);
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
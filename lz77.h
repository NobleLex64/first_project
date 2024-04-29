#ifndef NOBLELEX_PROJECT_LZ77
#define NOBLELEX_PROJECT_LZ77

#include <string>
#include <vector>
#include <list>
#include <string_view>

#define _ITER_S_W std::string_view::iterator
#define _ITER_L   std::list<size_t>::iterator 

namespace lz77{

  namespace hlp{

    /// @brief return end of of buff zone 
    /// @param dict_beg points on first elem in sliding window dictionary zone
    /// @param buff_beg points on first elem in sliding window buffer zone
    /// @param buff_end points on buff_beg + 15 or end of data
    /// @return std::string_view::iterator, end of dictionary zone
    inline _ITER_S_W endSubstr(_ITER_S_W dict_beg, _ITER_S_W buff_beg, const _ITER_S_W buff_end);

    /// @brief this function search max substr in the range from data_beg to buff_start
    /// @param symbol   list what can be modificate 
    /// @param data_beg points on first elem in string_view
    /// @param buff_beg points on first elem in sliding window buffer zone
    /// @param buff_end points on last possible elem in sliding window buffer zone
    /// @return std::pair<int8_t, int16_t>, pair.first -> count, pair.second -> distance
    std::pair<int8_t, int16_t> maxSubstr(std::list<size_t> &symbol, const _ITER_S_W data_beg, _ITER_S_W &buff_beg, _ITER_S_W buff_end);

    /// @brief this function modificate vector<list<size_t>>, adds new indices in the range from buff_beg to buff_end
    /// @param alphavit vector list [0..255] -> list {indices}
    /// @param data_beg start of data (this is text or another what compression)
    /// @param buff_beg start of buff zone
    /// @param buff_end end of buff zone
    inline void addNewIndx(std::vector<std::list<size_t>> &alphavit, const _ITER_S_W data_beg, _ITER_S_W &buff_beg, _ITER_S_W &buff_end);
  }

  /// @brief compression data using the lz77 algorithm
  /// @param data this is text or another what compression
  /// @return return compresion data
  std::string compression(std::string_view data);

  /// @brief decompression shifr(LZ77) to an uncompressed state
  /// @param shifr this compression data
  /// @return decompression shifr
  std::string decompression(std::string_view shifr);

}// lz77

#endif // NOBLELEX_PROJECT_LZ77

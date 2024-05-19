#ifndef PROJECT02_SRC_LZ77_H_
#define PROJECT02_SRC_LZ77_H_ 1

/// produced.. Noble_lex_64, 04.2024
/// algoritm LZ77 (compression and decompression)
/// 

/* STL libraries  */
#include <string>
#include <vector>
#include <list>

namespace lz77{

namespace helper{

/// @brief return end of of buff zone 
/// @param dict_beg points on first elem in sliding window dictionary zone
/// @param buff_beg points on first elem in sliding window buffer zone
/// @param buff_end points on buff_beg + 15 or end of data
/// @return std::string_view::iterator, end of dictionary zone
inline auto endSubstr(auto dict_beg, auto buff_beg, const auto buff_end);

/// @brief this function search max substr in the range from data_beg to buff_start
/// @param symbol   list what can be modificate 
/// @param data_beg points on first elem in string_view
/// @param buff_beg points on first elem in sliding window buffer zone
/// @param buff_end points on last possible elem in sliding window buffer zone
/// @return std::pair<int8_t, int16_t>, pair.first -> count, pair.second -> distance
std::pair<int8_t, int16_t> maxSubstr(std::list<size_t> &symbol, const auto data_beg, auto &buff_beg, auto buff_end);

/// @brief this function modificate vector<list<size_t>>, adds new indices in the range from buff_beg to buff_end
/// @param alphavit vector list [0..255] -> list {indices}
/// @param data_beg start of data (this is text or another what compression)
/// @param buff_beg start of buff zone
/// @param buff_end end of buff zone
inline void addNewIndx(std::vector<std::list<size_t>> &alphavit, const auto data_beg, auto &buff_beg, auto &buff_end, wchar_t min_val);

} // helper

/// @brief compression data using the lz77 algorithm
/// @param data this is text or another what compression
/// @return return compresion data
std::wstring compression(std::wstring_view data);

/// @brief decompression shifr(LZ77) to an uncompressed state
/// @param shifr this compression data
/// @return decompression shifr
std::wstring decompression(std::wstring_view shifr);

} // lz77

#endif // PROJECT02_SRC_LZ77_H_

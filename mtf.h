#ifndef COMPRESSION_ALGORTIM_MOVE_TO_FRONT
#define COMPRESSION_ALGORTIM_MOVE_TO_FRONT

#include <string>
#include <iterator>
#include <list>

namespace mtf{

  namespace hlp{
    inline wchar_t getMinVal(std::wstring_view::iterator start, const std::wstring_view::iterator& end);
    inline wchar_t getMaxVal(std::wstring_view::iterator start, const std::wstring_view::iterator& end);
  }

  /// @brief compression algoritm move-to-front
  /// @param data data that will be compressed
  /// @return data after compression
  std::wstring compression(std::wstring_view data);

  /// @brief decompression algoritm move-to-front
  /// @param shifr data that has been compressed
  /// @return data before compression
  std::wstring decompression(std::wstring_view shifr);
}

#endif // COMPRESSION_ALGORTIM_MOVE_TO_FRONT
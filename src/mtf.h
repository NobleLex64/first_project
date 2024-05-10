#ifndef COMPRESSION_ALGORTIM_MOVE_TO_FRONT
#define COMPRESSION_ALGORTIM_MOVE_TO_FRONT

/// produced.. Noble_lex 64, 05.2024
/// algoritm 'MTF' - move to front
/// used my libs "myAlg.h"

/// STL libraries
#include <string>

namespace mtf{

  namespace hlp{
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
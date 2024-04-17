#ifndef RLE_COMPRESSION_DEFENDER
#define RLE_COMPRESSION_DEFENDER

#include <string>
#include <string_view>

namespace rle{

#ifndef OLD_BIT
#define OLD_BIT 128

// function for compression
namespace hlp{
  uint8_t countsComboChar(std::string_view text, std::string_view::iterator& it);
  uint8_t countsSingleChar(std::string_view text, std::string_view::iterator& it);
}
  // RLE algoritm for compression text
  void compressionString(std::string_view text, std::string& shifr);

  // Return decompression RLE shift
  std::string decompressionString(std::string_view shifr);

#endif // OLD BIT
}
#endif // RLE_COMPRESSION_DEFENDER
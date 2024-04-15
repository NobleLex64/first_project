#ifndef RLE_COMPRESSION_DEFENDER
#define RLE_COMPRESSION_DEFENDER

#include <string>

namespace rle{

#ifndef OLD_BIT
#define OLD_BIT 128

// function for compression
namespace hlp{
  uint8_t countsComboChar(const std::string& text, size_t& i);
  uint8_t countsSingleChar(const std::string& text, std::string& shifr, size_t& i);
}
  // RLE algoritm for compression text
  void compressionString(const std::string& text, std::string& shifr);

  // Return decompression RLE shift
  std::string decompressionString(std::string& shifr);

#endif // OLD BIT
}
#endif // RLE_COMPRESSION_DEFENDER
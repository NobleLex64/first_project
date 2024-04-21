#ifndef RLE_COMPRESSION_DEFENDER
#define RLE_COMPRESSION_DEFENDER

#include <string>
#include <string_view>

namespace rle{

// function for compression
namespace hlp{
  // Needed to count repeating characters or doesn't repraring
  uint16_t countsComboChars(std::string_view text, std::string_view::iterator& it, const uint16_t max = 128);
  uint16_t countsSingleChar(std::string_view text, std::string_view::iterator& it, const uint16_t max = 128);
  
  // Needed for compress text or image
  void compressionTxt(std::string_view text,  std::string& shifr);
  void compressionImg(std::string_view image, std::string& shifr);

  // Needed to get size of compressed data
  size_t newSizeTxt(std::string_view text);
  size_t newSizeImg(std::string_view image);

  // Needed to get size of decomprressed data
  size_t newSizeShifrTxt(std::string_view text);
  size_t newSizeShifrImg(std::string_view image);

  // Nedeed for decompress text or image
  void decompressionTxt(std::string_view shifr, std::string& text);
  void decompressionImg(std::string_view shifr, std::string& image);
}
  
  // Return compressed data RLE shifr
  std::string compression(std::string_view image);

  // Return decompression RLE shifr
  std::string decompression(std::string_view shifr);
}
#endif // RLE_COMPRESSION_DEFENDER
#ifndef PROJECT02_SRC_RLE_H_
#define PROJECT02_SRC_RLE_H_ 1

/* STL libraries */
#include <string>

namespace rle{

// function for compression
namespace helper{

// Needed to count repeating characters or doesn't repraring
uint16_t countsComboChars(std::wstring_view text, std::wstring_view::iterator& it, const uint16_t max = 128);
uint16_t countsSingleChar(std::wstring_view text, std::wstring_view::iterator& it, const uint16_t max = 128);

// Needed for compress text or image
void compressionTxt(std::wstring_view text,  std::wstring& shifr);
void compressionImg(std::wstring_view image, std::wstring& shifr);

// Needed to get size of compressed data
size_t newSizeTxt(std::wstring_view text);
size_t newSizeImg(std::wstring_view image);

// Needed to get size of decomprressed data
size_t newSizeShifrTxt(std::wstring_view text);
size_t newSizeShifrImg(std::wstring_view image);

// Nedeed for decompress text or image
void decompressionTxt(std::wstring_view shifr, std::wstring& text);
void decompressionImg(std::wstring_view shifr, std::wstring& image);

} // helper

// Return compressed data RLE shifr
std::wstring compression(std::wstring_view image);

// Return decompression RLE shifr
std::wstring decompression(std::wstring_view shifr);

} // rle

#endif // PROJECT02_SRC_RLE_H_
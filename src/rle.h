#ifndef PROJECT02_SRC_RLE_H_
#define PROJECT02_SRC_RLE_H_ 1

/* STL libraries */
#include <string>

namespace rle{

// function for compression
namespace helper{

// Needed to count repeating characters or doesn't repraring
unsigned short countsComboChars(std::wstring_view::const_iterator &start, const std::wstring_view::const_iterator &end);
unsigned short countsSingleChar(std::wstring_view::const_iterator &start, const std::wstring_view::const_iterator &end);

// Needed for compress text or image
void compressionTxt(std::wstring_view text,  std::wstring& shifr);
void compressionImg(std::wstring_view image, std::wstring& shifr);

// Needed to get size of compressed data
unsigned long long newSizeTxt(std::wstring_view text);
unsigned long long newSizeImg(std::wstring_view image);

// Needed to get size of decomprressed data
unsigned long long newSizeShifrTxt(std::wstring_view text);
unsigned long long newSizeShifrImg(std::wstring_view image);

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
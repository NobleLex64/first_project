#ifndef PROJECT02_SRC_MTF_H_
#define PROJECT02_SRC_MTF_H_ 1

/// produced.. Noble_lex 64, 05.2024
/// algoritm 'MTF' - move to front
/// used my libs "myAlg.h"

/*  STL libraries */
#include <string>
#include <list>

/* My libs */
#include "myalgoritm.h"

namespace mtf{

/// @brief compression algoritm move-to-front
/// @param data data that will be compressed
/// @return data after compression
std::wstring compression(std::wstring_view data);

/// @brief decompression algoritm move-to-front
/// @param shifr data that has been compressed
/// @return data before compression
std::wstring decompression(std::wstring_view shifr);

} // mtf

#endif // PROJECT02_SRC_MTF_H_
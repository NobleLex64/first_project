#ifndef PROJECT02_SRC_BURROWS_WHEELER_H_
#define PROJECT02_SRC_BURROWS_WHEELER_H_ 1

/* 
  produced.. Noble_lex 64, 05.2024
  algoritm burrows wheeler
  used my libs "myAlg.h" 
*/

/* STL libraries  */
#include <string>
#include <vector>

/* My libraries */
#include "myalgoritm.h"

namespace brrw{
  
/// @brief this function get data(text or another) and compression it used alg burrows - wheeler
/// @param data text or another 
/// @return compression data
std::wstring compression(std::wstring_view data);

/// @brief this function get shifr(barrouws_wheeler) and decompression it
/// @param shifr compression data
/// @return decompression shifr
std::wstring decompression(std::wstring_view shifr);

}
#endif // PROJECT02_SRC_BURROWS_WHEELER_H_
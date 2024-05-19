#ifndef PROJECT02_RLE_TEST_
#define PROJECT02_RLE_TEST_ 1

#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>

namespace tst{
  // function testing rle algoritm vector<stirng>.
  void testRle(const std::vector<std::string>& text, const std::string& path);

  // function testing rle algoritm string.
  void testRle(std::string_view data, const std::string& path);
}
#endif
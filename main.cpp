#include "test.h"
#include "rle.h"

int main(){
  tst::testRle();

  std::string comp;
  rle::compressionString("booolingman 1111!!!", comp);
  std::cout << comp << std::endl;
  comp = rle::decompressionString(comp);
  std::cout << comp << std::endl;
  return 0;
}
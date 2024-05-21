#ifndef PROJECT02_SRC_ZIP_H_
#define PROJECT02_SRC_ZIP_H_ 1

/* STL libraries */
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

/* my compression libs*/
#include "rle.h"
#include "bwt.h"
#include "mtf.h"
#include "lz77.h"
#include "haffman.h"

namespace zip{

class Zip{

  class Menu{
    public:
      static void         commWelcome();
      static void         commExit();
      static void         msgError(int num);

      
      static void         commChooseALgoritm();
      static void         commDecompression();
      static int          commCheckProblems();


      static void         usualMode();
      static void         creativeMode();
      static std::wstring compressionAlgoritm(const std::vector<int> &coomb, std::wstring &data);


      static void         allMode();
      static void         selectedMode();


      static std::wstring typeOfDecompression(const int type, const std::wstring &data);
      static std::wstring typeOfCompression(const int type, const std::wstring &data, wchar_t &num);


      template <class T>
      static size_t       commSize(T data)
      {
        size_t counts_bit = 0;
        for(auto it = data.begin(); it < data.end(); ++it)
        {
          if(*it <= 0xff)
            counts_bit += 8;
          else if(*it <= 0xf'ff)
            counts_bit += 12;
          else if(*it <= 0xff'ff)
            counts_bit += 16;
          else if(*it <= 0xf'ff'ff)
            counts_bit += 20;
          else if(*it <= 0xff'ff'ff)
            counts_bit += 24;
          else if(*it <= 0xf'ff'ff'ff)
            counts_bit += 28;
          else if(*it <= 0xff'ff'ff'ff)
            counts_bit += 32;
        }

        return counts_bit;
      }
      static double       commK(const double data_size, std::wstring_view shifr);


      static bool         openFile(const std::string name, std::wstring &data, const char mode);
      static bool         readFile(const std::string &name, std::wstring &data);
      static bool         writeFile(const std::string &name, std::wstring &data);
  };

  static void startCompress(Menu &name);

  static void startDecompress(Menu &name);

  static inline std::vector<std::string> paths;

public:

  Zip(const std::vector<std::string> &paths)
  {
    Zip::paths = paths;
  }

  static void startProgramm();
}; 

} // zip

#endif // PROJECT02_SRC_ZIP_H_
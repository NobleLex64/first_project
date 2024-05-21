#ifndef PROJECT02_SRC_DIRECTIVES_H_
#define PROJECT02_SRC_DIRECTIVES_H_ 1


#ifdef _WIN32

  #define __CLEAR__ "cls"
  #define _CREATE_PATHS_ " & dir /b /a:-h > .paths.txt"
  #define _DELETE_       "del "

  #define _PATH_TO_PROJECT_ "..\\..\\..\\"
  #define _PATH_DATA_       "data\\"
  #define _PATH_TEST_       ".test\\"
  #define _PATH_INPUT_      "input\\"
  #define _PATH_OUTPUT_     "output\\"
  #define _PATH_TESTRESULT_ ".test_result\\"

  #define __LOCALE__ try { std::locale::global(std::locale("en_US"));}\
  catch (const std::runtime_error& e) {std::cerr << "Locale error: " << e.what() << std::endl;return 1;}
#endif

#ifdef __linux__

  #define __CLEAR__ "clear"
  #define _CREATE_PATHS_ ";ls | tee >.paths.txt"
  #define _DELETE_       "rm "

  #define _PATH_TO_PROJECT_ "../../"
  #define _PATH_DATA_       "data/"
  #define _PATH_TEST_       ".test/"
  #define _PATH_INPUT_      "input/"
  #define _PATH_OUTPUT_     "output/"
  #define _PATH_TESTRESULT_ ".test_result/"

  #define __LOCALE__ try { std::locale::global(std::locale("en_US.UTF-8"));}\
  catch (const std::runtime_error& e) {std::cerr << "Locale error: " << e.what() << std::endl;return 1;}

#endif

#ifdef __APPLE__

  #define __CLEAR__ "clear"
  #define _CREATE_PATHS_ ";ls | tee >.paths.txt"
  #define _DELETE_       "rm "

  #define _PATH_TO_PROJECT_ "../../"
  #define _PATH_DATA_       "data/"
  #define _PATH_TEST_       ".test/"
  #define _PATH_INPUT_      "input/"
  #define _PATH_OUTPUT_     "output/"
  #define _PATH_TESTRESULT_ ".test_result/"

  #define __LOCALE__ try { std::locale::global(std::locale("en_US.UTF-8"));}\
  catch (const std::runtime_error& e) {std::cerr << "Locale error: " << e.what() << std::endl;return 1;}

#endif

#endif //PROJECT02_SRC_DIRECTIVES_H_

still in development.


WHAT you needs to be done to launch:
  1) in the src directory mkdir "build"
  2) cd in build
  3) cmake .. and make
  4) run ./start

  in Linux or APPLE -> * cd scr; mkdir build; cmake ..; make; ./start;

if you need test:
  1) in the data directory mkdir ".test"
  2) add test file in format -> "test01", "test02" and etc.
  3) if you need more test, you can modificate array in zip.cpp -> commCheckProblems() -> file_names

Warning!
  1) when working through the terminal for some reason it gives an error writing from a file. (fixed)
  2) does not read characters in other encodings well. (seems to have fixed it)
  3) cannot write a file in a different (non-ASCII) encoding. (fixed -> locale)
  3) I haven’t figured out yet how to delete a file that is already encrypted

What need:
  1) backwards compatible with Windows and APPLE (maybe work, didn't check)

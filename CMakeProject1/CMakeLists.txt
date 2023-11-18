# CMakeList.txt : CMake project for CMakeProject1, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("CMakeProject1")

# Add source to this project's executable.
add_executable (CMakeProject1 "CMakeProject1.c" "CMakeProject1.h")

# TODO: Add tests and install targets if needed.

#if defined(_WIN32) || defined(__MSDOS__) //for unicode definitions. need to test on windows.
#define SPADE   "\x06"
#define CLUB    "\x05"
#define HEART   "\x03"
#define DIAMOND "\x04"
#else
#define SPADE   "\xE2\x99\xA0"
#define CLUB    "\xE2\x99\xA3"
#define HEART   "\xE2\x99\xA5"
#define DIAMOND "\xE2\x99\xA6"
#endif

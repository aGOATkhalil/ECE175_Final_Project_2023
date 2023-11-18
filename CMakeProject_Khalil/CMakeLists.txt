# CMakeList.txt : CMake project for CMakeProject_Khalil, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("CMakeProject_Khalil")

# Add source to this project's executable.
add_executable (CMakeProject_Khalil "CMakeProject_Khalil.c" "CMakeProject_Khalil.h")

# TODO: Add tests and install targets if needed.


if(WIN32 OR __MSDOS__)
    set(SPADE "\\x06")
    set(CLUB "\\x05")
    set(HEART "\\x03")
    set(DIAMOND "\\x04")
else()
    set(SPADE "\\xE2\\x99\\xA0")
    set(CLUB "\\xE2\\x99\\xA3")
    set(HEART "\\xE2\\x99\\xA5")
    set(DIAMOND "\\xE2\\x99\\xA6")
endif()
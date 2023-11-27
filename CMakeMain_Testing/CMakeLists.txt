# CMakeList.txt : CMake project for CMakeMain_Testing, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("CMakeMain_Testing")

# Add source to this project's executable.
add_executable (CMakeMain_Testing "CMakeMain_Testing" "CMakeMain_Testing.h")

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


if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

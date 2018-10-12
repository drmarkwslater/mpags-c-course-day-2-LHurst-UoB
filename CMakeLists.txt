cmake_minimum_required(VERSION 3.2)
project(MPAGSCipher VERSION 0.1.0)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Wfatal-errors -Wshadow -pedantic")

add_executable(mpags-cipher
	mpags-cipher.cpp
	MPAGSCipher/TransformChar.cpp
	MPAGSCipher/TransformChar.hpp
	MPAGSCipher/ProcessCommandLine.cpp
	MPAGSCipher/ProcessCommandLine.hpp
	MPAGSCipher/CaesarCipher.cpp
	MPAGSCipher/CaesarCipher.hpp
)

target_include_directories(mpags-cipher
	PRIVATE MPAGSCipher
)

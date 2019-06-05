cmake_minimum_required(VERSION 3.12)
project(P1)

set(CMAKE_CXX_STANDARD 14)

add_executable(P2 main.cpp scanner.cpp scanner.h testScanner.cpp testScanner.h token.h prefilter.cpp postfilter.cpp prefilter.h postfilter.h)
cmake_minimum_required(VERSION 3.12)
project(P4)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(P4
    main.cpp
    node.h
    parser.cpp
    parser.h
    printTree.cpp
    printTree.h
    scanner.cpp
    scanner.h
    semantics.cpp
    semantics.h
    statSem.cpp
    statSem.h
    token.h)

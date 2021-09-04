cmake_minimum_required(VERSION 3.16.3)
project(CS236Project)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(CS236Project
        Book.cpp
        Book.h
        BookCreator.cpp
        BookCreator.h
        BookListCreator.cpp
        BookListCreator.h
        Info.cpp
        Info.h
        Library.cpp
        Library.h
        main.cpp)

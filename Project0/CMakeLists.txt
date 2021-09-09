cmake_minimum_required(VERSION 3.16.3)
project(CS236Project)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(Lab1)

add_executable(CS236Project
        Lab1/Automaton.h
        Lab1/ColonAutomaton.cpp
        Lab1/ColonAutomaton.h
        Lab1/ColonDashAutomaton.cpp
        Lab1/ColonDashAutomaton.h
        Lab1/Lexer.cpp
        Lab1/Lexer.h
        Lab1/main.cpp
        Lab1/Token.cpp
        Lab1/Token.h)

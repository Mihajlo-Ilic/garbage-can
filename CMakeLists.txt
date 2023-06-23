cmake_minimum_required(VERSION 3.12)

project(garbage-can VERSION 1.0 LANGUAGES CXX)

set(SOURCES sources/main.cpp
        sources/test1.cpp sources/test2.cpp includes/Writer.hpp)

add_executable(gcan ${SOURCES})
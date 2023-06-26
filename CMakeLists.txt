cmake_minimum_required(VERSION 3.12)

project(garbage-can VERSION 1.0 LANGUAGES CXX)

set(SOURCES sources/main.cpp
        tests/ExpectTests.cpp tests/AssertTests.cpp includes/comparer.hpp includes/writer.hpp)

add_executable(gcan ${SOURCES})
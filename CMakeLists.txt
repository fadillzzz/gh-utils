cmake_minimum_required(VERSION 3.20)

project(GHUtils VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_definitions(-DUNICODE)

add_library(GHUtils mem/mem.cpp proc/proc.cpp pch.cpp)
target_precompile_headers(GHUtils PUBLIC pch.h)

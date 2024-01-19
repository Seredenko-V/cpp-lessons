cmake_minimum_required(VERSION 3.5)

project(cpp-lessons LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(cpp-lessons main.cpp list_mod.h list_mod.cpp)

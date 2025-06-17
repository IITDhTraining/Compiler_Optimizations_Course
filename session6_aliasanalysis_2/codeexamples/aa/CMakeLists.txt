cmake_minimum_required(VERSION 3.13)
project(myaapass LANGUAGES CXX)

find_package(LLVM REQUIRED CONFIG)
list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")
include(AddLLVM)
include_directories(${LLVM_INCLUDE_DIRS})

add_llvm_pass_plugin(aa aa.cpp)
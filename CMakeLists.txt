cmake_minimum_required(VERSION 3.21)
project(Diff)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(Diff
        include/Diff.h
        include/Diff_DSL.h
        src/Diff_Dump.cpp
        src/Diff_Main.cpp
        src/Diff_Errors_Func.cpp
        src/Diff_Text_Func.cpp
        src/Diff_Differentiate_Func.cpp
        src/Diff_Tree_Func.cpp)

cmake_minimum_required(VERSION 3.25)
project(Lab2)

set(CMAKE_CXX_STANDARD 23)

add_executable(Lab2 main.cpp
        DynamicArray.h
        LinkedList.h
        Sequence.h
        ArraySequence.h
        ListSequence.h)
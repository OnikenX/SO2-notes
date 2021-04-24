cmake_minimum_required(VERSION 3.17)
project(SO2_notes)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(so2_ficha3_e1-3)

add_executable(SO2_notes
        so2_ficha3_e1-3/SO2_F3_DLL.h
        ficha1.cpp
        ficha1.h
        ficha2.cpp
        ficha2.h
        ficha3.cpp
        ficha3.h
        ficha4.h
        main.cpp
        OWin32Wrapper.h
        Source.cpp ficha4.cpp)

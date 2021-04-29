cmake_minimum_required(VERSION 3.17)
project(SO2_notes)
set(CMAKE_CXX_STANDARD 20)

include_directories(.)
include_directories(src/Global)
include_directories(others/so2_ficha3_e1-3)


add_executable(SO2_notes
    others/so2_ficha3_e1-3/SO2_F3_DLL.h
    src/Global/ficha1.cpp 
    src/Global/ficha1.h
    src/Global/ficha2.cpp
    src/Global/ficha2.h
    src/Global/ficha3.cpp
    src/Global/ficha3.h
    src/Global/ficha4.h
    src/Global/ficha4.cpp
    src/Global/main.cpp
    src/Global/Source.cpp 
    src/Global/OWin32Wrapper.h
    )

add_executable(ficha7_client src/Ficha7/client.cpp)
add_executable(ficha7_server src/Ficha7/server.cpp)

add_executable(ficha6 src/Ficha6/Consumidor/main.cpp)

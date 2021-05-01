cmake_minimum_required(VERSION 3.17)
project(SO2_notes)

# 
set(CMAKE_CXX_STANDARD 20)

# incluir os varios headers
include_directories(src)
include_directories(src/Global)
include_directories(others/so2_ficha3_e1-3)

# activa o unicode para o TCHAR
add_compile_definitions("UNICODE" "_UNICODE")

# faz com que o msvc leia todos os source files como utf-8
add_compile_options("/utf-8")


add_executable(SO2_notes
    others/so2_ficha3_e1-3/SO2_F3_DLL.h
    src/Global/ficha1.cpp 
    src/Global/ficha1.h
    src/Global/ficha2.cpp
    src/Global/ficha2.h
    src/Global/ficha3.cpp
    src/Global/ficha3.h
    src/Global/main.cpp
    )

add_executable(ficha4           src/ficha4/main.cpp)    
add_executable(ficha5           src/ficha5/main.cpp)
add_executable(ficha6           src/Ficha6/Consumidor/main.cpp)
add_executable(ficha7_client    src/Ficha7/client.cpp)
add_executable(ficha7_server    src/Ficha7/server.cpp)



cmake_minimum_required(VERSION 3.0)

project(patisserie)

add_executable(patisserie main.cpp)

install(TARGETS patisserie RUNTIME DESTINATION bin)

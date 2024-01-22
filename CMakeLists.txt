cmake_minimum_required(VERSION 3.0)

project(patisserie CXX)

add_executable(patisserie
  main.cpp
  recette.cpp
  patisserie.cpp
)

install(TARGETS patisserie RUNTIME DESTINATION bin)

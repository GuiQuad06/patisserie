cmake_minimum_required(VERSION 3.0)

project(patisserie CXX)

add_executable(patisserie
  commande.cpp
  main.cpp
  patisserie.cpp
  recette.cpp
)

install(TARGETS patisserie RUNTIME DESTINATION bin)

cmake_minimum_required(VERSION 2.6)
project(lectura_mp3)

add_executable(lectura_mp3 main.cpp)

install(TARGETS lectura_mp3 RUNTIME DESTINATION bin)

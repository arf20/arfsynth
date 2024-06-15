cmake_minimum_required(VERSION 3.10)

project(arfsynth)

file(GLOB SRC "src/*.c")

add_executable(arfsynth ${SRC})

target_link_libraries(arfsynth SDL2)

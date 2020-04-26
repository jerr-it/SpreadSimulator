cmake_minimum_required(VERSION 3.17)
project(SpreadSimulator)

file (GLOB CPP_FILES src/*.c)
file (GLOB H_FILES src/*.h)
set (SOURCE_FILES ${CPP_FILES} ${H_FILES})

add_executable(SpreadSimulator ${SOURCE_FILES} main.c)
target_link_libraries(SpreadSimulator m)

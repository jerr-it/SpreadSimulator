cmake_minimum_required(VERSION 3.15)
project(SpreadSimulation C)

set(CMAKE_C_STANDARD 11)

add_subdirectory(SpreadSimulator)

find_package(Threads REQUIRED)

add_executable(SpreadSimulation main.c)
target_link_libraries(SpreadSimulation Threads::Threads)
target_link_libraries(SpreadSimulation m)
target_link_libraries(SpreadSimulation SpreadSimulator)

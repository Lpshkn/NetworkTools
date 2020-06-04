cmake_minimum_required(VERSION 3.16)
project(Switch)

include_directories(src)

add_executable(Switch src/main.cpp)
target_link_libraries(Switch argparse tins)
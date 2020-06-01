cmake_minimum_required(VERSION 3.16)
project(Sniffer)

add_executable(Sniffer src/main.cpp)
target_link_libraries(Sniffer tins)

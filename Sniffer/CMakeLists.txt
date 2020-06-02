cmake_minimum_required(VERSION 3.16)
project(Sniffer)

add_executable(Sniffer src/main.cpp src/configurator.cpp)
target_link_libraries(Sniffer tins argparse)
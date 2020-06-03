cmake_minimum_required(VERSION 3.16)
project(Sniffer)

include_directories(src)
add_executable(Sniffer src/main.cpp src/configurator.cpp src/sniff.cpp)
add_executable(configurator_test tests/configurator_test.cpp src/configurator.cpp)
target_link_libraries(Sniffer tins argparse)
target_link_libraries(configurator_test gtest)
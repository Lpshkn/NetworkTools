cmake_minimum_required(VERSION 3.16)
project(Sniffer)

include_directories(src)
add_executable(Sniffer src/main.cpp src/sniffer_configurator.cpp src/sniff.cpp src/sniffer_configurator.h src/sniff.h)
add_executable(configurator_test tests/configurator_test.cpp src/sniffer_configurator.cpp)
target_link_libraries(Sniffer tins argparse configurator)
target_link_libraries(configurator_test gtest configurator tins)
cmake_minimum_required(VERSION 3.16)
project(Switch)

include_directories(src)

add_executable(Switch src/main.cpp src/switch_configurator.cpp src/switch_configurator.h)
add_executable(SwitchTest tests/switch_configurator_test.cpp src/switch_configurator.cpp)
target_link_libraries(Switch argparse tins configurator)
target_link_libraries(SwitchTest gtest configurator tins)

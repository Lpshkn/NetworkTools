cmake_minimum_required(VERSION 3.16)
project(TcpChat)

include_directories(src)
add_executable(Tracker src/main.cpp src/tracker_configurator.cpp src/tracker_configurator.h)
target_link_libraries(Tracker tins argparse configurator config++)
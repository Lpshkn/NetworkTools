cmake_minimum_required(VERSION 3.16)
project(EchoServer)

include_directories(src client server)
add_executable(EchoServer server/main.cpp src/echo_configurator.cpp src/echo_configurator.h)
add_executable(EchoClient client/main.cpp src/echo_configurator.cpp src/echo_configurator.h)
target_link_libraries(EchoServer tins argparse configurator)
target_link_libraries(EchoClient tins argparse configurator)
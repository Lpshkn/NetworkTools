cmake_minimum_required(VERSION 3.16)
project(EchoServer)

include_directories(src)
add_executable(EchoServer src/main.cpp)
target_link_libraries(Sniffer tins argparse configurator)
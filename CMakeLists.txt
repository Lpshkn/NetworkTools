cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY arc)
set(CMAKE_BINARY_DIR bin)

set(LIBTINS_BUILD_SHARED 0)
set(LIBTINS_ENABLE_CXX11 1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

include_directories(3dparty/libtins/include 3dparty/argparse/include 3dparty/libconfig/lib 3dparty/libconfig configurator)
add_subdirectory(3dparty/libconfig)
add_subdirectory(3dparty/libtins)
add_subdirectory(3dparty/argparse)
add_subdirectory(configurator)
add_subdirectory(Sniffer)
add_subdirectory(Switch)
add_subdirectory(EchoServer)
add_subdirectory(TcpChat)
add_subdirectory(Tracker)

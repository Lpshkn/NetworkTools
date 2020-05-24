cmake_minimum_required(VERSION 3.15)
project(Sniffer)
set(CMAKE_CXX_STANDARD 20)

add_definitions(-DWPCAP)
add_definitions(-DHAVE_REMOTE)
add_executable(sniffer Sniffer/src/main.cpp)

include_directories(${CMAKE_SOURCE_DIR}/3dparty/WpdPack/Include)
#link_directories(C:/Users/kofff/CLionProjects/NetworkTools/3dparty)
find_library(WS2 ws2_32)
find_library(WPCAP wpcap)

target_link_libraries(sniffer ${WPCAP} ${WS2})

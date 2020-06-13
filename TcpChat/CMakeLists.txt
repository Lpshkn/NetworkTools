cmake_minimum_required(VERSION 3.16)
project(TcpChat)

include_directories(src client server)
add_executable(ChatServer server/main.cpp src/chat_configurator.cpp src/chat_configurator.h server/Server.cpp server/Server.h)
add_executable(ChatClient client/main.cpp src/chat_configurator.cpp src/chat_configurator.h client/Client.cpp client/Client.h)
target_link_libraries(ChatServer tins argparse configurator config++)
target_link_libraries(ChatClient tins argparse configurator config++)
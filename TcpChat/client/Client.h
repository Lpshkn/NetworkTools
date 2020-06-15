#ifndef NETWORKTOOLS_CHAT_CLIENT_H
#define NETWORKTOOLS_CHAT_CLIENT_H

#include "chat_configurator.h"

class Client {
public:
    Client() = delete;
    explicit Client(ChatConfigurator& configurator);

    void sendMessage(const std::string&);
    std::string getInfo();

private:
    void connect();
    Tins::IPv4Address serverAddress_;
    uint16_t serverPort_;
    uint16_t clientPort_;

    int seq_ = 100;
};

#endif
#ifndef NETWORKTOOLS_CLIENT_H
#define NETWORKTOOLS_CLIENT_H

#include "echo_configurator.h"

class Client {
public:
    Client() = delete;
    explicit Client(EchoConfigurator& configurator);

    std::string sendMessage(const std::string&);
    std::string getInfo();

private:
    Tins::IPv4Address serverAddress_;
    uint16_t serverPort_;
    uint16_t clientPort_;
};

#endif

#ifndef NETWORKTOOLS_SERVER_H
#define NETWORKTOOLS_SERVER_H

#include "echo_configurator.h"

class Server {
public:
    Server() = delete;
    explicit Server(EchoConfigurator& configurator);

    void sniff();
    std::string getInfo();

private:
    Tins::IPv4Address serverAddress_;
    uint16_t serverPort_;
};

#endif //NETWORKTOOLS_SERVER_H

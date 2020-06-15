#ifndef NETWORKTOOLS_CHAT_SERVER_H
#define NETWORKTOOLS_CHAT_SERVER_H

#include <tins/tcp_ip/stream_follower.h>
#include "chat_configurator.h"

class Server {
public:
    Server() = delete;
    explicit Server(ChatConfigurator& configurator);

    void sniff();
    std::string getInfo();

private:
    friend void processNewConnection(Tins::TCPIP::Stream& stream, Server* server);
    friend void processClientData(Tins::TCPIP::Stream& stream);


    Tins::IPv4Address serverAddress_;
    uint16_t serverPort_;
};

#endif //NETWORKTOOLS_SERVER_H
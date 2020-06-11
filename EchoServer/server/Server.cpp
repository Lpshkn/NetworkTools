//
// Created by root on 11.06.2020.
//

#include "Server.h"

Server::Server(EchoConfigurator &configurator) {
    serverPort_ = configurator.getServerPort();
    serverAddress_ = configurator.getServerAddress();

    if (!serverPort_) {
        std::cerr << "Error: Incorrect server port" << std::endl;
        exit(-31);
    }

    std::cout << getInfo();
}

void Server::sniff() {
    Tins::NetworkInterface interface(serverAddress_);
    Tins::SnifferConfiguration configuration;
    configuration.set_filter("udp and dst port " + std::to_string(serverPort_));
    Tins::Sniffer sniffer(interface.name(), configuration);

    for (auto &packet : sniffer) {
        auto ip = packet.pdu()->rfind_pdu<Tins::IP>();
        auto udp = packet.pdu()->rfind_pdu<Tins::UDP>();

        auto raw = packet.pdu()->rfind_pdu<Tins::RawPDU>();

        std::cout << "IP client address: " << ip.src_addr() << std::endl
                  << "client port: " << udp.sport() << std::endl
                  << "message: " << raw.payload().data() << std::endl
                  << std::endl;

    }
}

std::string Server::getInfo() {
    std::stringstream info;
    info << "Server address: " << serverAddress_ << std::endl
         << "Server port: " << serverPort_ << std::endl
         << std::endl;

    return info.str();
}


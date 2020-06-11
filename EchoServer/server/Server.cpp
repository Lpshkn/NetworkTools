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
    try {
        Tins::Sniffer sniffer(interface.name(), configuration);
        Tins::PacketSender sender(interface);

        for (auto &packet : sniffer) {
            auto ip = packet.pdu()->rfind_pdu<Tins::IP>();
            auto udp = packet.pdu()->rfind_pdu<Tins::UDP>();

            auto raw = packet.pdu()->rfind_pdu<Tins::RawPDU>();

            std::string message(raw.payload().begin(), raw.payload().end());

            std::cout << "IP client address: " << ip.src_addr() << std::endl
                      << "client port: " << udp.sport() << std::endl
                      << "message: " << message << std::endl
                      << std::endl;

            auto sendPacket = Tins::IP(ip.src_addr(), ip.dst_addr())
                              / Tins::UDP(udp.sport(), udp.dport())
                              / Tins::RawPDU(message);

            sender.send(sendPacket);
        }
    }
    catch (const Tins::pcap_error& err) {
        std::cerr << "Error: You haven't permission for that operation, run as the administrator" << std::endl;
        exit(-49);
    }
    catch (const Tins::socket_open_error& err) {
        std::cerr << "Error: You haven't permission for that operation, run as the administrator" << std::endl;
        exit(-50);
    }
}

std::string Server::getInfo() {
    std::stringstream info;
    info << "Server address: " << serverAddress_ << std::endl
         << "Server port: " << serverPort_ << std::endl
         << std::endl;

    return info.str();
}


#include "Server.h"
#include <tins/tcp_ip/stream_follower.h>

Server::Server(ChatConfigurator &configurator) {
    serverPort_ = configurator.getServerPort();
    serverAddress_ = configurator.getServerAddress();

    if (!serverPort_) {
        std::cerr << "Error: Incorrect server port" << std::endl;
        exit(-31);
    }

    std::cout << getInfo();
}

void processClientData(Tins::TCPIP::Stream& stream) {
    auto payload = stream.client_payload();
    std::string data(payload.begin(), payload.end());
    std::cout << "CLIENT" << " " << data << std::endl;
}


void processNewConnection(Tins::TCPIP::Stream& stream, Server* server) {
    stream.client_data_callback(&processClientData);

    Tins::NetworkInterface interface(Tins::IPv4Address(server->serverAddress_));
    Tins::PacketSender sender(interface);
    Tins::TCP tcp(stream.client_port(), server->serverPort_);
    tcp.set_flag(Tins::TCP::SYN, 1);
    tcp.set_flag(Tins::TCP::ACK, 1);

    auto packet = Tins::EthernetII() / Tins::IP(stream.client_addr_v4(), interface.ipv4_address()) / tcp;
    sender.send(packet);

    stream.auto_cleanup_payloads(true);
}

void Server::sniff() {
    Tins::NetworkInterface interface(serverAddress_);
    Tins::SnifferConfiguration configuration;
    configuration.set_filter("tcp and dst port " + std::to_string(serverPort_));
    try {
        Tins::Sniffer sniffer(interface.name(), configuration);
        Tins::PacketSender sender(interface);

        Tins::TCPIP::StreamFollower follower;
        auto func = std::bind(processNewConnection, std::placeholders::_1, this);
        follower.new_stream_callback(func);

        sniffer.sniff_loop([&](Tins::Packet& packet) {
            follower.process_packet(packet);
            return true;
        });
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


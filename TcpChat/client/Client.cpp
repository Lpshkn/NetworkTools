#include <sstream>
#include "Client.h"

Client::Client(ChatConfigurator &configurator, const std::string& nickname) {
    clientPort_ = configurator.getClientPort();
    serverPort_ = configurator.getServerPort();
    serverAddress_ = configurator.getServerAddress();
    nickname_ = nickname;

    if (!clientPort_) {
        std::cerr << "Error: Incorrect client port" << std::endl;
        exit(-30);
    }
    if (!serverPort_) {
        std::cerr << "Error: Incorrect server port" << std::endl;
        exit(-31);
    }

    std::cout << getInfo();
    connect();
}

void Client::connect() {
    Tins::NetworkInterface interface(serverAddress_);
    Tins::PacketSender sender(interface, 10, 10);

    auto tcp = Tins::TCP(serverPort_, clientPort_);
    tcp.set_flag(Tins::TCP::SYN, 1);
    tcp.seq(seq_);
    auto packet = Tins::EthernetII() / Tins::IP(serverAddress_) / tcp;

    try {
        // This is a mock to check that the user has permission
        Tins::IP ip;
        sender.send(ip);
    }
    catch (const Tins::socket_open_error& err) {
        std::cerr << "Error: You haven't permission for that operation, run as the administrator" << std::endl;
        exit(-50);
    }

    std::unique_ptr<Tins::PDU> response(sender.send_recv(packet, interface));
    seq_++;

    if (!response)
        throw std::logic_error("Error: Failed to connect to the server");
}

void Client::sendMessage(std::string& message) {
    Tins::NetworkInterface interface(serverAddress_);
    Tins::PacketSender sender(interface);
    Tins::TCP tcp(serverPort_, clientPort_);
    tcp.seq(seq_);

    message = nickname_ + ": " + message;
    auto packet = Tins::EthernetII() / Tins::IP(serverAddress_) / tcp / Tins::RawPDU(message);

    sender.send(packet);
    seq_ += message.length();
}

std::string Client::getInfo() {
    std::stringstream info;
    info << "Your port: " << clientPort_ << std::endl
         << "Server port: " << serverPort_ << std::endl
         << "Server address: " << serverAddress_ << std::endl
         << std::endl;

    return info.str();
}

void Client::sniff() const {
    Tins::NetworkInterface interface(Tins::IPv4Address("127.0.0.1"));
    Tins::SnifferConfiguration configuration;
    configuration.set_filter("tcp and dst port " + std::to_string(clientPort_));
    try {
        Tins::Sniffer sniffer(interface.name(), configuration);

        for (auto &packet : sniffer) {
            auto raw = packet.pdu()->find_pdu<Tins::RawPDU>();
            if (raw) {
                std::string data(raw->payload().begin(), raw->payload().end());
                std::cout << data << std::endl;
            }
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
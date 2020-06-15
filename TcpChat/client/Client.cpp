#include <sstream>
#include "Client.h"

Client::Client(ChatConfigurator &configurator) {
    clientPort_ = configurator.getClientPort();
    serverPort_ = configurator.getServerPort();
    serverAddress_ = configurator.getServerAddress();

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

void Client::sendMessage(const std::string& message) {
    Tins::NetworkInterface interface(serverAddress_);
    Tins::PacketSender sender(interface);
    Tins::TCP tcp(serverPort_, clientPort_);
    tcp.seq(seq_);

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
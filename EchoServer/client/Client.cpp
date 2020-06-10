#include <sstream>
#include "Client.h"

Client::Client(EchoConfigurator &configurator) {
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
}

std::string Client::sendMessage(const std::string& message) {
    Tins::PacketSender sender;
    auto packet = Tins::EthernetII() / Tins::IP(serverAddress_) / Tins::UDP(serverPort_, clientPort_) / Tins::RawPDU(message);
    std::unique_ptr<Tins::PDU> response(sender.send_recv(packet));

    if (response)
        auto it = response->rfind_pdu<Tins::RawPDU>().payload();
    else
        return "";
}

std::string Client::getInfo() {
    std::stringstream info;
    info << "Your port: " << clientPort_ << std::endl
         << "Server port: " << serverPort_ << std::endl
         << "Server address: " << serverAddress_ << std::endl
         << std::endl;

    return info.str();
}

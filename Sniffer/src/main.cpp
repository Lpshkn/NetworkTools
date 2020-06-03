#include <iostream>
#include "configurator.h"
#include "sniff.h"


int main(int argc, char* argv[]) {
    auto programName = "Sniffer";
    auto description = "The program to sniff the network traffic and print information about frames, packets etc.";
    auto epilog = "Lpshkn, 2020";
    auto version = "0.1.0";

    auto configurator = Configurator(programName, description,
                                     epilog, version);
    configurator.parseArguments(argc, argv);
    auto sniffer = buildSniffer(configurator);

    int number = 1;
    for (auto &packet : *sniffer) {
        std::cout << "Packet number: " << number << std::endl;

        auto pdu = packet.pdu();
        printPdu(pdu);
        number++;
    }

    return 0;
}
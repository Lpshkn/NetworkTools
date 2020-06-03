#include <iostream>
#include <vector>
#include <tins/tins.h>
#include "configurator.h"


int main(int argc, char* argv[]) {
    auto programName = "Sniffer";
    auto description = "The program to sniff the network traffic and print information about frames, packets etc.";
    auto epilog = "Lpshkn, 2020";
    auto version = "0.1.0";

    auto configurator = Configurator(programName, description,
                                     epilog, version).parseArguments(argc, argv);

    return 0;
}
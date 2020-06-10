#include "echo_configurator.h"

int main(int argc, char* argv[]) {
    auto programName = "EchoClient";
    auto description = "The program send a message to ECHO-server and receive an reply.";
    auto epilog = "Lpshkn, 2020";
    auto version = "0.1.0";

    EchoConfigurator configurator(programName, description, epilog, version);
    configurator.parseArguments(argc, argv);

    auto it = configurator.getServerPort();
    auto it2 = configurator.getClientPort();
    auto it3 = configurator.getServerAddress();

    return 0;
}
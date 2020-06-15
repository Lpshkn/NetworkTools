#include "chat_configurator.h"
#include "Server.h"

int main(int argc, char* argv[]) {
    auto programName = "ChatServer";
    auto description = "The program receives data over TCP protocol from several clients.";
    auto epilog = "Lpshkn, 2020";
    auto version = "0.1.0";

    ChatConfigurator configurator(programName, description, epilog, version);
    configurator.parseArguments(argc, argv);

    Server server(configurator);
    server.sniff();
    return 0;
}
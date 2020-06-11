#include "echo_configurator.h"
#include "Client.h"

int main(int argc, char* argv[]) {
    auto programName = "EchoClient";
    auto description = "The program send a message to ECHO-server and receive an reply.";
    auto epilog = "Lpshkn, 2020";
    auto version = "0.1.0";

    EchoConfigurator configurator(programName, description, epilog, version);
    configurator.parseArguments(argc, argv);

    Client client(configurator);

    std::cout << "If you want to exit, just input: \"exit\"" << std::endl << std::endl;

    while(true) {
        std::string message, response;
        std::cout << "Enter your message: ";
        std::cin >> message;

        if (message == "exit")
            break;

        try {
            response = client.sendMessage(message);
            std::cout << "Response of the server: " << response << std::endl << std::endl;
        }
        catch (const std::logic_error &err) {
            std::cerr << err.what() << std::endl;
            exit(-100);
        }
    }
    return 0;
}
#include "chat_configurator.h"
#include "Client.h"

int main(int argc, char* argv[]) {
    auto programName = "ChatClient";
    auto description = "The program send a message to the server, implements the client for chatting.";
    auto epilog = "Lpshkn, 2020";
    auto version = "0.1.0";

    ChatConfigurator configurator(programName, description, epilog, version);
    configurator.parseArguments(argc, argv);

    std::string nickname;
    std::cout << "Enter your nickname: ";
    std::cin >> nickname;
    std::cout << std::endl;

    Client client(configurator, nickname);

    std::cout << "You connected to the server" << std::endl;
    std::cout << "If you want to exit, just input: \"exit\"" << std::endl << std::endl;
    std::cout << "Now you are in the chat: " << std::endl;

    while(true) {
        std::string message;
        std::cin >> message;

        if (message == "exit")
            break;

        try {
            client.sendMessage(message);
        }
        catch (const std::logic_error &err) {
            std::cerr << err.what() << std::endl;
            exit(-100);
        }
    }

    return 0;
}
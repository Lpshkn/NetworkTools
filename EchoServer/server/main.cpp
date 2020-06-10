#include "echo_configurator.h"

int main(int argc, char* argv[]) {
    auto programName = "EchoClient";
    auto description = "The program receive a message, prints it and send this message back.";
    auto epilog = "Lpshkn, 2020";
    auto version = "0.1.0";

    EchoConfigurator configurator(programName, description, epilog, version);


    return 0;
}
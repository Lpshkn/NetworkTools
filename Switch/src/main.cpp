#include "switch_configurator.h"

int main(int argc, char** argv) {
    auto programName = "Switch";
    auto description = "The program receive and redirect packets to certain ports.";
    auto epilog = "Lpshkn, 2020";
    auto version = "0.1.0";

    auto configurator = SwitchConfigurator(programName, description,
                                            epilog, version);
    configurator.parseArguments(argc, argv);

    return 0;
}
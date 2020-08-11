#include <thread>
#include "tracker_configurator.h"

int main(int argc, char* argv[]) {
    auto programName = "Tracker";
    auto description = "The program monitors and modifies the network traffic.";
    auto epilog = "Lpshkn, 2020";
    auto version = "0.1.0";

    TrackerConfigurator configurator(programName, description, epilog, version);
    configurator.parseArguments(argc, argv);

    return 0;
}
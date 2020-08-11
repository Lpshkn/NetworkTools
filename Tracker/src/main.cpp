#include <thread>
#include "track.h"
#include "tracker_configurator.h"

int main(int argc, char* argv[]) {
    auto programName = "Tracker";
    auto description = "The program monitors and modifies the network traffic.";
    auto epilog = "Lpshkn, 2020";
    auto version = "0.1.0";

    TrackerConfigurator configurator(programName, description, epilog, version);
    configurator.parseArguments(argc, argv);

    std::string iface1, iface2;
    std::cout << "Enter the first interface: "; std::cin >> iface1;
    std::cout << "Enter the second interface: "; std::cin >> iface2;
    track(iface1, iface2, configurator);

    return 0;
}
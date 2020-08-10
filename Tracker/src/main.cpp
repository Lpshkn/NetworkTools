#include <thread>
#include "tracker_configurator.h"

int main(int argc, char* argv[]) {
    auto programName = "Tracker";
    auto description = "The program monitors and modifies the network traffic.";
    auto epilog = "Lpshkn, 2020";
    auto version = "0.1.0";

    TrackerConfigurator configurator(programName, description, epilog, version);
    configurator.parseArguments(argc, argv);

    int maxLength = 0;
    std::string modifiedPcapFile, forbiddenPcapFile;
    std::cout << "Enter the max length of data: "; std::cin >> maxLength;
    std::cout << "Enter the filename of the PCAP file for modified packets: "; std::cin >> modifiedPcapFile;
    std::cout << "Enter the filename of the PCAP file for forbidden packets: "; std::cin >> forbiddenPcapFile;

    return 0;
}
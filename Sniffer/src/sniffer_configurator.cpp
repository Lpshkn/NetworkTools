#include <memory>
#include <utility>
#include <regex>
#include "sniffer_configurator.h"

// Method to creating an instance of ArgumentParser to process arguments by the command line
std::unique_ptr<argparse::ArgumentParser> SnifferConfigurator::buildParser() {
    auto parser = std::make_unique<argparse::ArgumentParser>(programName_, version_);
    parser->add_description(description_);
    parser->add_epilog(epilog_);

    parser->add_argument("interface")
            .help("the network interface which will be sniffed")
            .action([](const std::string& value) { return value; });

    parser->add_argument("-f", "--filter")
            .help("specify a filter of libpcap format to receive packets that you want from the network");

    return parser;
}

SnifferConfigurator::SnifferConfigurator(const std::string& programName, const std::string& description,
                                         const std::string& epilog, const std::string& version) noexcept
        : Configurator(programName, description, epilog, version) {
    initialize();
}

// Method to initialize important values in the constructor
void SnifferConfigurator::initialize() {
    argumentParser_ = std::move(buildParser());
}

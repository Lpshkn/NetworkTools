#include <memory>
#include <utility>
#include <regex>
#include "configurator.h"

Configurator::Configurator(std::string programName, std::string description,
                           std::string epilog, std::string version) noexcept
        : programName_(std::move(programName)), description_(std::move(description)),
          epilog_(std::move(epilog)), version_(std::move(version)) {

    argumentParser_ = buildParser();
}

std::unique_ptr<argparse::ArgumentParser> Configurator::buildParser() noexcept {
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

std::string Configurator::getFilter() {
    try {
        return argumentParser_->get("-f");
    }
    catch (const std::logic_error& err) {
        return {};
    }
}

std::string Configurator::getInterface() {
    try {
        return argumentParser_->get("interface");
    }
    catch (const std::logic_error& err) {
        return {};
    }
}

void Configurator::parseArguments(int argc, char **argv) {
    try {
        argumentParser_->parse_args(argc, argv);
    }
    catch (const std::runtime_error& err) {
        std::string error = err.what();
        error = std::regex_replace(error, std::regex {"^[\\s:]+"}, "");
        std::cerr << "Error: " << error << std::endl;
        std::cerr << *argumentParser_ << std::endl;
        exit(-1);
    }
}

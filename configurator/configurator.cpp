#include <memory>
#include <regex>
#include "configurator.h"

Configurator::Configurator(std::string programName, std::string description,
                                         std::string epilog, std::string version) noexcept
        : programName_(std::move(programName)), description_(std::move(description)),
          epilog_(std::move(epilog)), version_(std::move(version)) {}

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
    catch (const std::logic_error& err) {
        std::string error = err.what();
        if (error == "stoi")
            error = "Incorrect parameter was input";
        else
            error = std::regex_replace(error, std::regex {"^[\\s:]+"}, "");

        std::cerr << "Error: " << error << std::endl;
        std::cerr << argumentParser_->help().str() << std::endl;
        exit(-2);
    }
}

std::unique_ptr<Tins::SnifferConfiguration> Configurator::getSnifferConfig() noexcept {
    auto config = std::make_unique<Tins::SnifferConfiguration>();
    config->set_filter(this->getFilter());
    config->set_promisc_mode(true);
    config->set_immediate_mode(true);

    return config;
}

std::string Configurator::getFilter() {
    try {
        return argumentParser_->get("-f");
    }
    catch (const std::logic_error& err) {
        return {};
    }
}

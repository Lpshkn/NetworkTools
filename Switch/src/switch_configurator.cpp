#include <memory>
#include <utility>
#include <regex>
#include "switch_configurator.h"

// Method to creating an instance of ArgumentParser to process arguments by the command line
std::unique_ptr<argparse::ArgumentParser> SwitchConfigurator::buildParser() {
    auto parser = std::make_unique<argparse::ArgumentParser>(programName_, version_);
    parser->add_description(description_);
    parser->add_epilog(epilog_);

    parser->add_argument("interfaces")
            .help("the network interfaces which will be sniffed and will be involved to process of the switch")
            .remaining();

    parser->add_argument("-t", "--time")
            .help("time of a note life (in seconds) in the commutation table, by default it's 60 seconds")
            .default_value(60)
            .action([](const std::string& value) { return std::stoi(value); });

    return parser;
}

SwitchConfigurator::SwitchConfigurator(const std::string& programName, const std::string& description,
                                         const std::string& epilog, const std::string& version) noexcept
        : Configurator(programName, description, epilog, version) {
    initialize();
}

// Method to initialize important values in the constructor
void SwitchConfigurator::initialize() {
    argumentParser_ = std::move(buildParser());
}

std::unique_ptr<std::vector<std::string>> SwitchConfigurator::getInterfaces() {
    try {
        auto it = argumentParser_->get<std::vector<std::string>>("interfaces");
        return std::make_unique<std::vector<std::string>>(it);
    }
    catch (const std::logic_error& err) {
        return nullptr;
    }
}

void SwitchConfigurator::parseArguments(int argc, char **argv) {
    try {
        argumentParser_->parse_args(argc, argv);
        auto ifaces = argumentParser_->get<std::vector<std::string>>("interfaces");
        if (ifaces.size() < 2) {
            throw std::logic_error("There are less than 2 interfaces were passed");
        }
    }
    catch (const std::runtime_error& err) {
        std::string error = err.what();
        error = std::regex_replace(error, std::regex {"^[\\s:]+"}, "");
        std::cerr << "Error: " << error << std::endl;
        std::cerr << argumentParser_->help().str() << std::endl;
        exit(-1);
    }
    catch (const std::logic_error& err) {
        std::string error = err.what();
        if (error == "stoi")
            error = "Incorrect parameter '-t' was input";
        else
            error = std::regex_replace(error, std::regex {"^[\\s:]+"}, "");

        std::cerr << "Error: " << error << std::endl;
        std::cerr << argumentParser_->help().str() << std::endl;
        exit(-2);
    }
}

int SwitchConfigurator::getLifeTime() noexcept {
    return argumentParser_->get<int>("-t");
}

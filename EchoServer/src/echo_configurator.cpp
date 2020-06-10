#include <fstream>
#include "echo_configurator.h"

EchoConfigurator::EchoConfigurator(const std::string &program_name, const std::string &description,
                                   const std::string &epilog, const std::string &version) noexcept
                                   : Configurator(program_name, description, epilog, version) {
    initialize();
}

std::unique_ptr<argparse::ArgumentParser> EchoConfigurator::buildParser() {
    auto parser = std::make_unique<argparse::ArgumentParser>(programName_, version_);
    parser->add_description(description_);
    parser->add_epilog(epilog_);

    parser->add_argument("-s", "--server_port")
            .help("the port of the server")
            .action([](const std::string& value) { return std::stoi(value); });

    parser->add_argument("-c", "--client_port")
            .help("the port of the client")
            .action([](const std::string& value) { return std::stoi(value); });

    parser->add_argument("-a", "--address")
            .help("the ip address of the server")
            .action([](const std::string& value) { return Tins::IPv4Address(value); });

    parser->add_argument("-f", "--config_file")
            .help("the file containing settings to configure program")
            .action([](const std::string& value) { return value; });

    return parser;
}

void EchoConfigurator::initialize() {
    argumentParser_ = std::move(buildParser());
}

uint16_t EchoConfigurator::getServerPort() {
    return getPort("-s");
}

uint16_t EchoConfigurator::getClientPort() {
    return getPort("-c");
}

Tins::IPv4Address EchoConfigurator::getServerAddress() {
    try {
        return argumentParser_->get<Tins::IPv4Address>("-a");
    }
    catch (const std::logic_error& err) {
        return {};
    }
}

uint16_t EchoConfigurator::getPort(const std::string& argument) {
    try {
        auto port = argumentParser_->get<int>(argument);
        if (port <= 0 || port > 65535) {
            std::cerr << "Error: port is incorrect" << std::endl;
            std::cerr << *argumentParser_ << std::endl;
            exit(-1);
        }
        return port;
    }
    catch (const std::logic_error& err) {
        return {};
    }
}

std::filesystem::path EchoConfigurator::getConfigFile() {
    try {
        auto filename = argumentParser_->get<std::string>("-f");
        auto path = std::filesystem::path(filename);

        if (!std::filesystem::exists(path)) {
            std::cerr << "Error: This file doesn't exist" << std::endl;
            std::cerr << *argumentParser_ << std::endl;
            exit(-15);
        }

        return path;
    }
    catch (const std::logic_error& err) {
        return {};
    }
}


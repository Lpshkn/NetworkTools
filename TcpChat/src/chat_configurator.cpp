#include <fstream>
#include <libconfig.h++>
#include "chat_configurator.h"

ChatConfigurator::ChatConfigurator(const std::string &program_name, const std::string &description,
                                   const std::string &epilog, const std::string &version) noexcept
        : Configurator(program_name, description, epilog, version) {
    serverPort_ = 0;
    clientPort_ = 0;
    serverAddress_ = {};
    configFile_ = "";

    initialize();
}

std::unique_ptr<argparse::ArgumentParser> ChatConfigurator::buildParser() {
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

void ChatConfigurator::initialize() {
    argumentParser_ = std::move(buildParser());
}

uint16_t ChatConfigurator::getServerPort() const {
    return serverPort_;
}

uint16_t ChatConfigurator::getClientPort() const {
    return clientPort_;
}

Tins::IPv4Address ChatConfigurator::getServerAddress() {
    return serverAddress_;
}

uint16_t ChatConfigurator::getPort(const std::string& argument) {
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

std::filesystem::path ChatConfigurator::getConfigFile() {
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

void ChatConfigurator::parseArguments(int argc, char **argv) {
    Configurator::parseArguments(argc, argv);

    serverPort_ = getPort("-s");
    clientPort_ = getPort("-c");
    configFile_ = getConfigFile();
    try {
        serverAddress_ = argumentParser_->get<Tins::IPv4Address>("-a");
    }
    catch (const std::logic_error &err) {
        serverAddress_ = Tins::IPv4Address("127.0.0.1");
    }

    if (configFile_ != "") {
        libconfig::Config cfg;
        try {
            cfg.readFile(configFile_);
        }
        catch (const libconfig::FileIOException&) {
            std::cerr << "Error: I/O error while reading file." << std::endl;
            exit(-21);
        }
        catch (const libconfig::ParseException& err) {
            std::cerr << "Error: Parse error at " << err.getFile() << ":" << err.getLine()
                      << " - " << err.getError() << std::endl;
            exit(-22);
        }

        unsigned int server_port = 0, client_port = 0;
        std::string address;
        if (cfg.lookupValue("server_port", server_port))
            serverPort_ = (uint16_t)server_port;
        if (cfg.lookupValue("client_port", client_port))
            clientPort_ = (uint16_t)client_port;
        if (cfg.lookupValue("server_address", address))
            serverAddress_ = Tins::IPv4Address(address);
    }

    if (!serverPort_ && configFile_ == "") {
        std::cerr << "Error: You must specify a server port or config filename" << std::endl;
        exit(-20);
    }
}


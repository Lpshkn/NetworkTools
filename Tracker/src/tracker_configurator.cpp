#include <fstream>
#include "tracker_configurator.h"

TrackerConfigurator::TrackerConfigurator(const std::string &program_name, const std::string &description,
                                   const std::string &epilog, const std::string &version) noexcept
        : Configurator(program_name, description, epilog, version) {
    trueServerPort_ = 0;
    wrongServerPort_ = 0;
    clientPort_ = 0;
    trueServerAddress_ = {};
    wrongServerAddress_ = {};
    clientAddress_ = {};
    throughput_ = false;

    configFile_ = "";

    initialize();
}

std::unique_ptr<argparse::ArgumentParser> TrackerConfigurator::buildParser() {
    auto parser = std::make_unique<argparse::ArgumentParser>(programName_, version_);
    parser->add_description(description_);
    parser->add_epilog(epilog_);

    parser->add_argument("-f", "--config_file")
            .help("the file containing settings to configure program")
            .action([](const std::string& value) { return value; });

    parser->add_argument("-t", "--throughput")
            .help("to choose the fastest traffic way")
            .default_value(false)
            .implicit_value(true);

    return parser;
}

void TrackerConfigurator::initialize() {
    argumentParser_ = std::move(buildParser());
}

uint16_t TrackerConfigurator::getPort(const std::string& argument, const libconfig::Config& cfg) {
    unsigned int port = 0;
    auto port_ = (uint16_t)cfg.lookupValue(argument, port);
    if (port_ <= 0 || port_ > 65535) {
        std::cerr << "Error: port is incorrect" << std::endl;
        exit(-1);
    }
    return port_;
}

std::filesystem::path TrackerConfigurator::getConfigFile() {
    try {
        auto filename = argumentParser_->get<std::string>("-f");
        auto path = std::filesystem::path(filename);

        if (!std::filesystem::exists(path)) {
            std::cerr << "Error: The configuration file doesn't exist" << std::endl;
            std::cerr << *argumentParser_ << std::endl;
            exit(-15);
        }

        return path;
    }
    catch (const std::logic_error& err) {
        return {};
    }
}

void TrackerConfigurator::parseArguments(int argc, char **argv) {
    Configurator::parseArguments(argc, argv);
    configFile_ = getConfigFile();

    try {
        throughput_ = argumentParser_->get<bool>("-t");
    }
    catch (const std::logic_error &err) {
        std::cerr << "Error: Incorrect Throughput flag" << std::endl;
        exit(-31);
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

        std::string trueServerAddress, wrongServerAddress, clientAddress;

        trueServerPort_ = getPort("true_server_port", cfg);
        wrongServerPort_ = getPort("wrong_server_port", cfg);
        clientPort_ = getPort("client_port", cfg);

        if (cfg.lookupValue("true_server_address", trueServerAddress))
            trueServerAddress_ = Tins::IPv4Address(trueServerAddress);
        if (cfg.lookupValue("wrong_server_address", wrongServerAddress))
            wrongServerAddress_ = Tins::IPv4Address(wrongServerAddress);
        if (cfg.lookupValue("client_address", clientAddress))
            clientAddress_ = Tins::IPv4Address(clientAddress);

        if (!trueServerPort_ || !wrongServerPort_ || !clientPort_ || !trueServerAddress_ || !wrongServerAddress_ || !clientAddress_) {
            std::cerr << "Error: Incorrect parameters in the configuration file" << std::endl;
            exit(-20);
        }
    }
    else {
        std::cerr << "Error: You must specify a configuration file" << std::endl;
        exit(-20);
    }
}

uint16_t TrackerConfigurator::getTrueServerPort() const {
    return trueServerPort_;
}

uint16_t TrackerConfigurator::getWrongServerPort() const {
    return wrongServerPort_;
}

Tins::IPv4Address TrackerConfigurator::getTrueServerAddress() const {
    return trueServerAddress_;
}

Tins::IPv4Address TrackerConfigurator::getWrongServerAddress() const {
    return wrongServerAddress_;
}

Tins::IPv4Address TrackerConfigurator::getClientAddress() const {
    return clientAddress_;
}

uint16_t TrackerConfigurator::getClientPort() const {
    return clientPort_;
}

bool TrackerConfigurator::getThroughput() const {
    return throughput_;
}

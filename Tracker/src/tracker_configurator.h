#ifndef NETWORKTOOLS_TRACKER_CONFIGURATOR_H
#define NETWORKTOOLS_TRACKER_CONFIGURATOR_H

#include <filesystem>
#include <libconfig.h++>
#include "configurator.h"

class TrackerConfigurator : public Configurator {
public:
    explicit TrackerConfigurator() = delete;
    explicit TrackerConfigurator(const std::string& program_name, const std::string& description = {},
                              const std::string& epilog = {}, const std::string& version = {}) noexcept;

    [[nodiscard]] uint16_t getTrueServerPort() const;
    [[nodiscard]] uint16_t getWrongServerPort() const;
    [[nodiscard]] uint16_t getClientPort() const;
    [[nodiscard]] Tins::IPv4Address getTrueServerAddress() const;
    [[nodiscard]] Tins::IPv4Address getWrongServerAddress() const;
    [[nodiscard]] Tins::IPv4Address getClientAddress() const;
    [[nodiscard]] bool getThroughput() const;
    void parseArguments(int argc, char* argv[]) override;

private:
    std::unique_ptr<argparse::ArgumentParser> buildParser() override;
    uint16_t getPort(const std::string& argument, const libconfig::Config& cfg);
    std::filesystem::path getConfigFile();
    void initialize();

    uint16_t trueServerPort_;
    uint16_t wrongServerPort_;
    uint16_t clientPort_;
    Tins::IPv4Address trueServerAddress_;
    Tins::IPv4Address wrongServerAddress_;
    Tins::IPv4Address clientAddress_;
    bool throughput_;

    std::filesystem::path configFile_;
};

#endif
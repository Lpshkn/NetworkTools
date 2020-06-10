#ifndef NETWORKTOOLS_ECHO_CONFIGURATOR_H
#define NETWORKTOOLS_ECHO_CONFIGURATOR_H

#include <filesystem>
#include "configurator.h"

class EchoConfigurator : public Configurator {
public:
    explicit EchoConfigurator() = delete;
    explicit EchoConfigurator(const std::string& program_name, const std::string& description = {},
                              const std::string& epilog = {}, const std::string& version = {}) noexcept;

    uint16_t getServerPort();
    uint16_t getClientPort();
    Tins::IPv4Address getServerAddress();
    std::filesystem::path getConfigFile();

private:
    std::unique_ptr<argparse::ArgumentParser> buildParser() override;
    uint16_t getPort(const std::string& argument);
    void initialize();
};

#endif

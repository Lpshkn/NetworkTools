#ifndef NETWORKTOOLS_CHAT_CONFIGURATOR_H
#define NETWORKTOOLS_CHAT_CONFIGURATOR_H

#include <filesystem>
#include "configurator.h"

class ChatConfigurator : public Configurator {
public:
    explicit ChatConfigurator() = delete;
    explicit ChatConfigurator(const std::string& program_name, const std::string& description = {},
                              const std::string& epilog = {}, const std::string& version = {}) noexcept;

    [[nodiscard]] uint16_t getServerPort() const;
    [[nodiscard]] uint16_t getClientPort() const;
    Tins::IPv4Address getServerAddress();
    void parseArguments(int argc, char* argv[]) override;

private:
    std::unique_ptr<argparse::ArgumentParser> buildParser() override;
    uint16_t getPort(const std::string& argument);
    std::filesystem::path getConfigFile();
    void initialize();

    uint16_t serverPort_;
    uint16_t clientPort_;
    Tins::IPv4Address serverAddress_;
    std::filesystem::path configFile_;
};

#endif

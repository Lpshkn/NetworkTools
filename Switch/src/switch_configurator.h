#ifndef NETWORKTOOLS_SWITCH_CONFIGURATOR_H
#define NETWORKTOOLS_SWITCH_CONFIGURATOR_H

#include <argparse/argparse.hpp>
#include <tins/tins.h>
#include "configurator.h"

class SwitchConfigurator : public Configurator {
public:
    explicit SwitchConfigurator() = delete;
    explicit SwitchConfigurator(const std::string& program_name, const std::string& description = {},
                                 const std::string& epilog = {}, const std::string& version = {}) noexcept;

    int getLifeTime() noexcept;
    std::unique_ptr<std::vector<Tins::NetworkInterface>> getInterfaces();
    void parseArguments(int argc, char** argv) override;

private:
    std::unique_ptr<argparse::ArgumentParser> buildParser() override;
    void initialize();
};

#endif //NETWORKTOOLS_SWITCH_CONFIGURATOR_H

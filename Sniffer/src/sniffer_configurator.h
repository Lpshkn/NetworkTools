#ifndef NETWORKTOOLS_SNIFFER_CONFIGURATOR_H
#define NETWORKTOOLS_SNIFFER_CONFIGURATOR_H

#include <argparse/argparse.hpp>
#include <tins/tins.h>
#include "configurator.h"


class SnifferConfigurator : public Configurator {
public:
    explicit SnifferConfigurator() = delete;
    explicit SnifferConfigurator(const std::string& program_name, const std::string& description = {},
            const std::string& epilog = {}, const std::string& version = {}) noexcept;

    virtual std::string getInterface();

private:
    std::unique_ptr<argparse::ArgumentParser> buildParser() override;
    void initialize();
};

#endif //NETWORKTOOLS_SNIFFER_CONFIGURATOR_H

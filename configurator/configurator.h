/* Configurator is a class implementing parsing of command line arguments and
 * providing methods to work with them. So, this class is abstract and will be used by other program.
 */

#ifndef NETWORKTOOLS_CONFIGURATOR_H
#define NETWORKTOOLS_CONFIGURATOR_H

#include <argparse/argparse.hpp>
#include <tins/tins.h>

class Configurator {
public:
    explicit Configurator() = delete;
    explicit Configurator(Configurator&&) = delete;
    explicit Configurator(std::string  program_name, std::string  description = {},
            std::string  epilog = {}, std::string  version = {}) noexcept;

    virtual void parseArguments(int argc, char* argv[]);
    virtual std::string getFilter();
    virtual std::string getInterface();
    virtual std::unique_ptr<Tins::SnifferConfiguration> getSnifferConfig() noexcept;

protected:
    std::unique_ptr<argparse::ArgumentParser> argumentParser_;
    std::string programName_;
    std::string description_;
    std::string epilog_;
    std::string version_;

    virtual std::unique_ptr<argparse::ArgumentParser> buildParser() = 0;
};

#endif //NETWORKTOOLS_CONFIGURATOR_H

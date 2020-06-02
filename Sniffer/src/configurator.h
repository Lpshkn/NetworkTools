/* Configurator is a class implementing parsing of command line arguments and
 * providing methods to work with them.
 */
#ifndef NETWORKTOOLS_CONFIGURATOR_H
#define NETWORKTOOLS_CONFIGURATOR_H

#include <argparse/argparse.hpp>

class Configurator {
public:
    explicit Configurator() = delete;
    explicit Configurator(std::string  program_name, std::string  description = {},
                          std::string  epilog = {}, std::string  version = {}) noexcept;

    void parseArguments(int argc, char* argv[]);
    std::string getFilter();
    std::string getInterface();
private:
    std::unique_ptr<argparse::ArgumentParser> argumentParser_;
    std::string programName_;
    std::string description_;
    std::string epilog_;
    std::string version_;

    std::unique_ptr<argparse::ArgumentParser> buildParser() noexcept;
};

#endif //NETWORKTOOLS_CONFIGURATOR_H

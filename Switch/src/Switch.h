#ifndef NETWORKTOOLS_SWITCH_H
#define NETWORKTOOLS_SWITCH_H

#include <map>
#include <tins/tins.h>
#include <mutex>
#include <thread>
#include "switch_configurator.h"

extern std::mutex mutex;

class Switch {
public:
    explicit Switch() = delete;
    explicit Switch(SwitchConfigurator& configurator);
    explicit Switch(std::vector<Tins::NetworkInterface>& interfaces);
    explicit Switch(std::vector<Tins::NetworkInterface>& interfaces, int lifeTime = 60);

    void run();

private:
    int lifeTime_;
    std::vector<Tins::NetworkInterface> interfaces_;
    std::map<Tins::HWAddress<6>, Tins::NetworkInterface> commutationTable_;
};

#endif //NETWORKTOOLS_SWITCH_H

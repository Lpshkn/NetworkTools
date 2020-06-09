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
    static void run();

private:
    int lifeTime_;
    static std::vector<Tins::NetworkInterface> interfaces_;
    static std::map<Tins::HWAddress<6>, Tins::NetworkInterface> commutationTable_;

    static void sniffLoop(Tins::NetworkInterface&);
    static void queryTable(Tins::Packet&, Tins::NetworkInterface&);
};

#endif //NETWORKTOOLS_SWITCH_H

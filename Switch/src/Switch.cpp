#include "Switch.h"

std::mutex mutex;

Switch::Switch(SwitchConfigurator &configurator) {
    interfaces_ = *(configurator.getInterfaces());
    lifeTime_ = configurator.getLifeTime();
    commutationTable_ = {};
}

Switch::Switch(std::vector<Tins::NetworkInterface> &interfaces)
    : interfaces_(interfaces), lifeTime_(60), commutationTable_() {}

Switch::Switch(std::vector<Tins::NetworkInterface> &interfaces, int lifeTime)
    : interfaces_(interfaces), lifeTime_(lifeTime), commutationTable_() {}

void Switch::run() {
    for (auto &iface : interfaces_) {
        auto sniffer = Tins::Sniffer(iface.name());

    }
}

#include "Switch.h"

Switch::Switch(SwitchConfigurator &configurator) {

}

Switch::Switch(std::vector<std::string> &interfaces) {

}

Switch::Switch(std::vector<std::string> &interfaces, int lifeTime) {

}

void Switch::run() {
    for (auto &iface : interfaces_) {
        auto sniffer = Tins::Sniffer(iface.name());

    }
}

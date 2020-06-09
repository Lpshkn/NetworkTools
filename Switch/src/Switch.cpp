#include "Switch.h"
#include <thread>

std::mutex mutex;

std::vector<Tins::NetworkInterface> Switch::interfaces_ = {};
std::map<Tins::HWAddress<6>, Tins::NetworkInterface> Switch::commutationTable_ = {};

Switch::Switch(SwitchConfigurator &configurator) {
    interfaces_ = *(configurator.getInterfaces());
    lifeTime_ = configurator.getLifeTime();
}

Switch::Switch(std::vector<Tins::NetworkInterface> &interfaces) {
    interfaces_ = interfaces;
    lifeTime_ = 60;
}

Switch::Switch(std::vector<Tins::NetworkInterface> &interfaces, int lifeTime) {
    interfaces_ = interfaces;
    lifeTime_ = lifeTime;
}

void Switch::run() {
    std::vector<std::thread> threads;

    for (auto &iface : interfaces_) {
        std::thread th(sniffLoop, std::ref(iface));
        threads.push_back(std::move(th));
    }

    for (auto &th : threads)
        if (th.joinable())
            th.join();
}

void Switch::sniffLoop(Tins::NetworkInterface &interface) {
    Tins::Sniffer sniffer(interface.name());

    for (auto &packet : sniffer) {
        queryTable(packet, interface);
    }
}

void Switch::queryTable(Tins::Packet &packet, Tins::NetworkInterface& interface) {
    std::lock_guard<std::mutex> lock(::mutex);
    auto eth = packet.pdu()->find_pdu<Tins::EthernetII>();
    if (commutationTable_.find(eth->src_addr()) == commutationTable_.end())
        commutationTable_[eth->src_addr()] = interface;
    if (commutationTable_.find(eth->dst_addr()) != commutationTable_.end()) {
        Tins::PacketSender sender(commutationTable_[eth->dst_addr()]);
        sender.send(*packet.pdu());
    }
    else
        for (auto &iface : interfaces_)
            if (interface.name() != iface.name()) {
                Tins::PacketSender sender(iface);
                sender.send(*packet.pdu());
            }


    std::cout << packet.pdu()->find_pdu<Tins::EthernetII>()->src_addr() << "   " << interface.name() << std::endl;
    std::cout << packet.pdu()->find_pdu<Tins::EthernetII>()->dst_addr() << "   " << std::endl << std::endl;
}

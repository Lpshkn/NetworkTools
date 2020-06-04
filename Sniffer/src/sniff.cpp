#include <iostream>
#include <iomanip>
#include "sniff.h"

void printPdu(Tins::PDU *pdu) {
    if (auto eth = pdu->find_pdu<Tins::EthernetII>()) {
        std::cout << "Ethernet frame:" << std::endl
                  << "\t\tsrc: " << eth->src_addr() << std::endl
                  << "\t\tdst: " << eth->dst_addr() << std::endl
                  << "\t\tsize: " << eth->size() << std::endl;
    }

    if (auto ip = pdu->find_pdu<Tins::IP>()) {
        std::cout << "IP packet:" << std::endl
                  << "\t\tsrc: " << ip->src_addr() << std::endl
                  << "\t\tdst: " << ip->dst_addr() << std::endl
                  << "\t\tttl: " << (int)ip->ttl() << std::endl
                  << "\t\tsize: " << ip->size() << std::endl;
    }

    if (auto icmp = pdu->find_pdu<Tins::ICMP>()) {
        std::cout << "ICMP packet:" << std::endl
                  << "\t\ttype: " << icmp->type() << std::endl
                  << "\t\tcode: " << (int)icmp->code() << std::endl
                  << "\t\tsize: " << icmp->size() << std::endl;
    }

    if (auto udp = pdu->find_pdu<Tins::UDP>()) {
        std::cout << "UDP datagram:" << std::endl
                  << "\t\tsrc port: " << udp->sport() << std::endl
                  << "\t\tdst port: " << udp->dport() << std::endl
                  << "\t\tsize: " << udp->size() << std::endl;
    }

    if (auto tcp = pdu->find_pdu<Tins::TCP>()) {
        std::cout << "TCP packet: " << std::endl
                  << "\t\tsrc port: " << tcp->sport() << std::endl
                  << "\t\tdst port: " << tcp->dport() << std::endl
                  << "\t\tSN: " << tcp->seq() << std::endl
                  << "\t\tAN: " << tcp->ack_seq() << std::endl
                  << "\t\tsize: " << tcp->size() << std::endl;
    }

    std::cout << std::right << std::setw(50) << std::setfill('-') << '\n';
}

std::unique_ptr<Tins::Sniffer> buildSniffer(SnifferConfigurator &configurator) {
    auto config = std::move(configurator.getSnifferConfig());
    std::unique_ptr<Tins::Sniffer> sniffer;
    try {
        sniffer = std::make_unique<Tins::Sniffer>(configurator.getInterface(), *config);
    }
    catch (const Tins::invalid_pcap_filter &err) {
        std::cerr << "Error: this pcap filter is incorrect" << std::endl;
        exit(-2);
    }
    catch (const Tins::pcap_error &err) {
        std::cerr << "Error: this interface doesn't exist" << std::endl;
        exit(-3);
    }

    return std::move(sniffer);
}
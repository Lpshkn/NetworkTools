#include <pcap.h>
#include <iostream>
#include <cstdlib>
#include <inaddr.h>
#include <string>
#include "packets.h"


int main() {
    pcap_if_t *alldevs, *dev;
    int inum, i = 0, res;

    pcap_t *adhandler;
    char errbuf[256];
    std::string packet_filter = "( ip and udp ) or icmp";
    u_long netmask;
    struct bpf_program fcode {};

    if (pcap_findalldevs_ex((char*)"rpcap://", nullptr, &alldevs, errbuf) == -1) {
        std::cerr << "Error: an error happened on the pcap_findalldevs_ex function" << std::endl;
        exit(1);
    }

    for (dev = alldevs; dev; dev = dev->next, i++) {
        std::cout << i+1 << ". " << dev->name;
        if (dev->description)
            std::cout << dev->description << std::endl;
        else
            std::cout << " (No description available)" << std::endl;
    }

    if (i == 0) {
        std::cerr << "\nError: no interfaces found! Make sure WinPcap is installed" << std::endl;
        exit(2);
    }

    std::cout << "Enter the interface number (1-" << i << "): ";
    std::cin >> inum;

    if (inum < 1 || inum > i) {
        std::cout << "\nInterface number out of range.\n";
        pcap_freealldevs(alldevs);
        return -1;
    }

    for (dev = alldevs, i = 0; i < inum-1; dev = dev->next, i++);

    if (dev->addresses != nullptr)
        netmask = ((struct sockaddr_in *)(dev->addresses->netmask))->sin_addr.S_un.S_addr;
    else
        netmask = 0xffffff;

    if ((adhandler = pcap_open(dev->name, 65536, PCAP_OPENFLAG_PROMISCUOUS, 1000, nullptr, errbuf)) == nullptr) {
        std::cerr << "\nUnable to open the adapter. " << dev->name << " is not supported by WinPcap" << std::endl;
        pcap_freealldevs(alldevs);
        return -1;
    }

    if (pcap_compile(adhandler, &fcode, packet_filter.c_str(), 1, netmask) < 0) {
        std::cerr << "\nUnable to compile the packet filter. Check the syntax." << std::endl;
        pcap_freealldevs(alldevs);
        return -1;
    }

    if (pcap_setfilter(adhandler, &fcode) < 0) {
        std::cerr << "\nError setting the filter." << std::endl;
        pcap_freealldevs(alldevs);
        return -1;
    }

    std::cout << "\nlistening on " << dev->description << "..." << std::endl;
    pcap_freealldevs(alldevs);

    pcap_loop(adhandler, 0, packet_handler, nullptr);
    return 0;
}

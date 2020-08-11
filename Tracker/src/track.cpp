#include <iostream>
#include <thread>
#include "track.h"
#include "tracker_configurator.h"

void track(std::string& iface1, std::string& iface2, TrackerConfigurator& configurator) {
    Tins::NetworkInterface interfaceAB(iface1);
    Tins::NetworkInterface interfaceCD(iface2);
    try {
        Tins::Sniffer snifferAB(interfaceAB.name());
        Tins::Sniffer snifferCD(interfaceCD.name());
        Tins::PacketSender senderAB(interfaceAB);
        Tins::PacketSender senderCD(interfaceCD);

        std::thread thread1(sniffAB, std::ref(snifferAB), std::ref(senderAB), std::ref(configurator));
        std::thread thread2(sniffCD, std::ref(snifferCD), std::ref(senderCD), std::ref(configurator));

        thread1.join();
        thread2.join();
    }
    catch (const Tins::pcap_error& err) {
        std::cerr << "Error: You haven't permission for that operation, run as the administrator" << std::endl;
        exit(-49);
    }
    catch (const Tins::socket_open_error& err) {
        std::cerr << "Error: You haven't permission for that operation, run as the administrator" << std::endl;
        exit(-50);
    }

}

void sniffAB(Tins::Sniffer& sniffer, Tins::PacketSender& sender, TrackerConfigurator& configurator) {
    for (auto &packet : sniffer) {
        auto ip = packet.pdu()->find_pdu<Tins::IP>();
        auto udp = packet.pdu()->find_pdu<Tins::UDP>();
        auto tcp = packet.pdu()->find_pdu<Tins::TCP>();
        auto raw = packet.pdu()->find_pdu<Tins::RawPDU>();

        if (ip) {
            if (udp && raw) {
                if (raw->payload_size() <= configurator.getMaxLengthPacket()) {
                    if (ip->src_addr() == configurator.getClientAddress() &&
                        udp->sport() == configurator.getClientPort()
                        && udp->dport() == configurator.getTrueServerPort() &&
                        ip->dst_addr() == configurator.getTrueServerAddress()) {
                        auto sendPacket = Tins::IP(configurator.getWrongServerAddress(), ip->src_addr())
                                          / Tins::UDP(configurator.getWrongServerPort(), udp->sport())
                                          / Tins::RawPDU(*raw);
                        sender.send(sendPacket);

                        Tins::PacketWriter writer(configurator.getModifiedPcapFile().string(),
                                                  Tins::DataLinkType<Tins::EthernetII>());
                        writer.write(sendPacket);
                    }
                    else if (ip->src_addr() == configurator.getWrongServerAddress() &&
                             udp->sport() == configurator.getWrongServerPort()
                             && udp->dport() == configurator.getClientPort() &&
                             ip->dst_addr() == configurator.getClientAddress()) {
                        auto sendPacket = Tins::IP(configurator.getClientAddress(), configurator.getTrueServerAddress())
                                          / Tins::UDP(configurator.getClientPort(), configurator.getTrueServerPort())
                                          / Tins::RawPDU(*raw);
                        sender.send(sendPacket);
                    }
                }
                else {
                    Tins::PacketWriter writer(configurator.getModifiedPcapFile().string(),
                                              Tins::DataLinkType<Tins::EthernetII>());
                    writer.write(packet);
                }
            }
            else if (tcp && configurator.getThroughput()) {
                //
            }
        }
    }
}
void sniffCD(Tins::Sniffer& sniffer, Tins::PacketSender& sender, TrackerConfigurator& configurator) {
    for (auto &packet : sniffer) {
        auto ip = packet.pdu()->find_pdu<Tins::IP>();
        auto udp = packet.pdu()->find_pdu<Tins::UDP>();
        auto tcp = packet.pdu()->find_pdu<Tins::TCP>();
        auto raw = packet.pdu()->find_pdu<Tins::RawPDU>();

        if (ip) {
            if (udp && raw) {
                if (ip->src_addr() == configurator.getWrongServerAddress() &&
                    udp->sport() == configurator.getWrongServerPort()
                    && udp->dport() == configurator.getClientPort() &&
                    ip->dst_addr() == configurator.getClientAddress()) {
                    auto sendPacket = Tins::IP(configurator.getClientAddress(), configurator.getTrueServerAddress())
                                      / Tins::UDP(configurator.getClientPort(), configurator.getTrueServerPort())
                                      / Tins::RawPDU(*raw);
                    sender.send(sendPacket);
                    Tins::PacketWriter writer(configurator.getModifiedPcapFile().string(),
                                              Tins::DataLinkType<Tins::EthernetII>());
                    writer.write(sendPacket);
                }
            }
        }
    }
}

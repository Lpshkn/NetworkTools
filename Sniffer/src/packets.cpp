#include "packets.h"
#include <pcap.h>
#include <string>


void packet_handler(unsigned char *param, const struct pcap_pkthdr* header, const unsigned char *pkt_data) {
    static int number_of_frame = 0;
    ether_header *etherHeader;
    ip_header *ipHeader;
    udp_header *udpHeader;
    icmp_header *icmpHeader;
    unsigned int ip_len;
    unsigned short sport, dport;

    etherHeader = (ether_header*)pkt_data;
    ipHeader = (ip_header*) (pkt_data + 14);
    ip_len = (ipHeader->ver_ihl & 0xf) * 4;

    std::string proto_ether;
    switch (ntohs(etherHeader->type)) {
        case IPv4: proto_ether = "IPv4"; break;
        case ARP: proto_ether = "ARP"; break;
    }

    std::string proto_ip;
    switch (ipHeader->proto) {
        case 1: proto_ip = "ICMP"; break;
        case 2: proto_ip = "IGMP"; break;
        case 4: proto_ip = "IPv4"; break;
        case 6: proto_ip = "TCP"; break;
        case 17: proto_ip = "UDP"; break;
    }
    printf("%d. ether_len:%d mac_src:%02x.%02x.%02x.%02x.%02x.%02x mac_dst:%02x.%02x.%02x.%02x.%02x.%02x proto:%s \n",  ++number_of_frame, header->len,
           etherHeader->mac_destination[0], etherHeader->mac_destination[1], etherHeader->mac_destination[2],
           etherHeader->mac_destination[3], etherHeader->mac_destination[4], etherHeader->mac_destination[5],
           etherHeader->mac_source[0], etherHeader->mac_source[1], etherHeader->mac_source[2],
           etherHeader->mac_source[3], etherHeader->mac_source[4], etherHeader->mac_source[5],
           proto_ether.c_str());

    printf("ip_len:%d ip_src:%d.%d.%d.%d ip_dst:%d.%d.%d.%d ttl:%d proto:%s\n",
           ntohs(ipHeader->tlen),
           ipHeader->saddr.byte1, ipHeader->saddr.byte2, ipHeader->saddr.byte3, ipHeader->saddr.byte4,
           ipHeader->daddr.byte1, ipHeader->daddr.byte2, ipHeader->daddr.byte3, ipHeader->daddr.byte4,
           ipHeader->ttl, proto_ip.c_str());

    if (ipHeader->proto == 17) {
        udpHeader = (udp_header*) ((u_char*)ipHeader + ip_len);
        printf("udp_len:%d data_len:%d port_src:%d port_dst:%d\n\n", ntohs(udpHeader->len), ntohs(udpHeader->len) - 8,
               ntohs(udpHeader->sport), ntohs(udpHeader->dport));
    }
    else if (ipHeader->proto == 1) {
        icmpHeader = (icmp_header*) ((u_char*)ipHeader + ip_len);
        printf("type_icmp:%d code:%d data_len:%lld\n\n", icmpHeader->type, icmpHeader->code, header->len - (((u_char*)icmpHeader + 8) - pkt_data));
    }


}

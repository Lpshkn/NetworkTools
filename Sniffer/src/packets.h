#ifndef SNIFFER_PACKETS_H
#define SNIFFER_PACKETS_H

// Type of the packet in the ethernet
const int ARP = 0x0806;
const int IPv4 = 0x0800;

// Ethernet packet
typedef struct ether_header {
   unsigned char mac_destination[6];
   unsigned char mac_source[6];
   unsigned short type;
} ether_header;


typedef struct ip_address {
    unsigned char byte1, byte2, byte3, byte4;
} ip_address;

typedef struct ip_header {
    unsigned char ver_ihl;
    unsigned char tos;
    unsigned short tlen;
    unsigned short identification;
    unsigned short flags_fo;
    unsigned char ttl;
    unsigned char proto;
    unsigned short crc;
    ip_address saddr;
    ip_address daddr;
    unsigned int op_pad;
} ip_header;

typedef struct udp_header {
    unsigned short sport;
    unsigned short dport;
    unsigned short len;
    unsigned short crc;
} udp_header;

typedef struct icmp_header {
    unsigned char type;
    unsigned char code;
    unsigned short crc;
} icmp_header;

void packet_handler(unsigned char* param, const struct pcap_pkthdr *header, const unsigned char *pkt_data);

#endif

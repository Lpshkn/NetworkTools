#ifndef NETWORKTOOLS_TRACK_H
#define NETWORKTOOLS_TRACK_H
#include <tins/tins.h>
#include "tracker_configurator.h"

void track(std::string& iface1, std::string& iface2, TrackerConfigurator& configurator);
void sniffAB(Tins::Sniffer& sniffer, Tins::PacketSender& sender, TrackerConfigurator& configurator);
void sniffCD(Tins::Sniffer& sniffer, Tins::PacketSender& sender, TrackerConfigurator& configurator);

#endif //NETWORKTOOLS_TRACK_H

//
// Copyright (C) OpenSim Ltd.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see http://www.gnu.org/licenses/.
//

#include "inet/common/ModuleAccess.h"
#include "inet/queueing/LabelsTag_m.h"
#include "inet/queueing/PacketMarker.h"

namespace inet {
namespace queueing {

Define_Module(PacketMarker);

PacketMarker::~PacketMarker()
{
    for (auto filter : filters)
        delete filter;
}

void PacketMarker::initialize(int stage)
{
    PacketMarkerBase::initialize(stage);
    if (stage == INITSTAGE_LOCAL) {
        cStringTokenizer tokenizer(par("filterClasses"));
        while (tokenizer.hasMoreTokens()) {
            auto filterClass = tokenizer.nextToken();
            auto filter = check_and_cast<IPacketFilterFunction *>(createOne(filterClass));
            filters.push_back(filter);
        }
        labels = cStringTokenizer(par("labels")).asVector();
    }
}

void PacketMarker::markPacket(Packet *packet)
{
    auto labelsTag = packet->addTagIfAbsent<LabelsTag>();
    for (int i = 0; i < (int)filters.size(); i++) {
        auto filter = filters[i];
        if (filter->matchesPacket(packet)) {
            EV_INFO << "Marking packet " << packet->getName() << " with " << labels[i] << ".\n";
            labelsTag->insertLabels(labels[i].c_str());
        }
    }
}

} // namespace queueing
} // namespace inet

//
// Copyright (C) 2020 OpenSim Ltd.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//

#ifndef __INET_LINKBREAKOSGVISUALIZER_H
#define __INET_LINKBREAKOSGVISUALIZER_H

#include <osg/ref_ptr>

#include "inet/visualizer/base/LinkBreakVisualizerBase.h"

namespace inet {

namespace visualizer {

class INET_API LinkBreakOsgVisualizer : public LinkBreakVisualizerBase
{
#ifdef WITH_OSG

  protected:
    class INET_API LinkBreakOsgVisualization : public LinkBreakVisualization {
      public:
        osg::ref_ptr<osg::Node> node;

      public:
        LinkBreakOsgVisualization(osg::Node *node, int transmitterModuleId, int receiverModuleId);
    };

  protected:
    virtual void refreshDisplay() const override;

    virtual const LinkBreakVisualization *createLinkBreakVisualization(cModule *transmitter, cModule *receiver) const override;
    virtual void addLinkBreakVisualization(const LinkBreakVisualization *linkBreakVisualization) override;
    virtual void removeLinkBreakVisualization(const LinkBreakVisualization *linkBreakVisualization) override;
    virtual void setAlpha(const LinkBreakVisualization *linkBreakVisualization, double alpha) const override;

#else // ifdef WITH_OSG

  protected:
    virtual void initialize(int stage) override {}

    virtual const LinkBreakVisualization *createLinkBreakVisualization(cModule *transmitter, cModule *receiver) const override { return nullptr; }
    virtual void setAlpha(const LinkBreakVisualization *linkBreakVisualization, double alpha) const override {}

#endif // ifdef WITH_OSG
};

} // namespace visualizer

} // namespace inet

#endif


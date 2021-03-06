//
// Copyright (C) 2011 OpenSim Ltd.
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

package inet.examples.inet.pcaprecorder;

import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.node.inet.StandardHost;
import ned.DatarateChannel;


network PcapRecorderTest
{
    types:
        channel C extends DatarateChannel
        {
            datarate = 10Mbps;
            delay = 0.1us;
        }
    submodules:
        client0: StandardHost {
            parameters:
                @display("p=250,100;i=device/pc3");
        }
        client1: StandardHost {
            parameters:
                @display("p=250,200;i=device/pc3");
        }
        server: StandardHost {
            parameters:
                @display("p=350,150;i=device/pc2");
        }
        configurator: Ipv4NetworkConfigurator {
            parameters:
                @display("p=100,100;is=s");
        }
    connections:
        client0.pppg++ <--> C <--> server.pppg++;
        client1.ethg++ <--> C <--> server.ethg++;
}


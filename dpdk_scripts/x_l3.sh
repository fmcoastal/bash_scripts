#!/bin/bash

/home/misc/dpdk-l3fwd  -c 0x800000 -n 4 -- -p 0x3 --config="(0, 0, 23),(1, 0, 23)"


default XAUI20
src.ip  101.0.0.0
src.port  101
dest.ip  100.10.0.1
dest.port  11

default XAUI30
dest.ip  101.0.0.0
dest.port  101
src.ip  100.10.0.1
src.port  11


# default <port0> <port1> /* For Dual Interface*/
# src.ip.min 192.168.18.1
# src.ip.max 192.168.18.100
# src.ip.inc 1
# tx.size <pkt size>
# tx.percent <tx_rate>
# start


cn96xx-crb

 dpdk-l2fwd -c 0xf -n 4 -- -q 1 -p 3c -T 1

ox3c gets me ports 2,3,4,5

Ports on the board:

   6  4  2
 0 7  5  3 1

dpdk-l3fwd -c 0xf00000 -n 4 -- -P -p 0x3c --config="(2, 0, 20),(3, 0,21),(4, 0,22),(5, 0,23)"







-------------------
dpdk-l3fwd -c 0xf00000 -n 4 -- -P -p 0x3c --config="(2, 0, 20),(3, 0,21),(4, 0,22),(5, 0,23)"

,22),(5, 0,23)" 0xf00000 -n 4 -- -P -p 0x3c --config="(2, 0, 20),(3, 0,21),(4, 0,
EAL: Detected 24 lcore(s)
EAL: Detected 1 NUMA nodes
EAL: Multi-process socket /var/run/dpdk/rte/mp_socket
EAL: Selected IOVA mode 'VA'
EAL: No available hugepages reported in hugepages-2048kB
EAL: Probing VFIO support...
EAL: VFIO support initialized
EAL: PCI device 0002:01:00.1 on NUMA socket 0
EAL:   probe driver: 177d:a0f8 net_octeontx2
EAL: PCI device 0002:01:00.2 on NUMA socket 0
EAL:   probe driver: 177d:a0f8 net_octeontx2
EAL: PCI device 0002:01:00.3 on NUMA socket 0
EAL:   probe driver: 177d:a0f8 net_octeontx2
EAL: PCI device 0002:01:00.4 on NUMA socket 0
EAL:   probe driver: 177d:a0f8 net_octeontx2
EAL: PCI device 0002:01:00.5 on NUMA socket 0
EAL:   probe driver: 177d:a0f8 net_octeontx2
EAL: PCI device 0002:01:00.6 on NUMA socket 0
EAL:   probe driver: 177d:a0f8 net_octeontx2
EAL: PCI device 0002:01:00.7 on NUMA socket 0
EAL:   probe driver: 177d:a0f8 net_octeontx2
EAL: PCI device 0002:01:01.0 on NUMA socket 0
EAL:   probe driver: 177d:a0f8 net_octeontx2
EAL: PCI device 0002:01:01.1 on NUMA socket 0
EAL:   probe driver: 177d:a0f8 net_octeontx2
EAL: PCI device 0002:01:01.2 on NUMA socket 0
EAL:   probe driver: 177d:a0f8 net_octeontx2
EAL: PCI device 0002:01:01.3 on NUMA socket 0
EAL:   probe driver: 177d:a0f8 net_octeontx2
EAL: PCI device 0002:01:01.4 on NUMA sock[  292.457159] vfio_cap_init: 0002:02:00.0 hiding cap 0x14
et 0
EAL:   probe driver: 177d:a0f8 net_octeontx2
EAL: PCI device 0002:01:01.5 on NUMA socket 0
EAL:   probe driver: 177d:a0f8 net_octeontx2
EAL: PCI device 0002:01:01.6 on NUMA socket 0
EAL:   probe driver: 177d:a0f8 net_octeontx2
EAL: PCI device 0002:01:01.7 on NUMA socket 0
EAL:   probe driver: 177d:a0f8 net_octeontx2
EAL: PCI device 0002:01:02.0 on NUMA socket 0
EAL:   probe driver: 177d:a0f8 net_octeontx2
EAL: PCI device 0002:01:02.1 on NUMA socket 0
EAL:   probe driver: 177d:a0f8 net_octeontx2
EAL: PCI device 0002:02:00.0 on NUMA socket 0
EAL:   probe driver: 177d:a063 net_octeontx2
EAL:   using IOMMU type 1 (Type 1)
EAL: PCI device 0002:03:00.0 on NUMA socket 0
EAL:   probe driver: 177d:a063 net_octeontx2
[  292.807936] vfio_cap_init: 0002:03:00.0 hiding cap 0x14
EAL: PCI device 0002:04:00.0 on NUMA socket 0
EAL:   probe driver: 177d:a063 net_octeontx2
[  293.143934] vfio_cap_init: 0002:04:00.0 hiding cap 0x14
EAL: PCI device 0002:05:00.0 on NUMA socket 0
EAL:   probe driver: 177d:a063 net_octeontx2
[  293.486110] vfio_cap_init: 0002:05:00.0 hiding cap 0x14
EAL: PCI device 0002:06:00.0 on NUMA socket 0
EAL:   probe driver: 177d:a063 net_octeontx2
[  293.819924] vfio_cap_init: 0002:06:00.0 hiding cap 0x14
EAL: PCI device 0002:07:00.0 on NUMA socket 0
EAL:   probe driver: 177d:a063 net_octeontx2
[  294.155922] vfio_cap_init: 0002:07:00.0 hiding cap 0x14
EAL: PCI device 0002:08:00.0 on NUMA socket 0
EAL:   probe driver: 177d:a063 net_octeontx2
EAL: PCI device 0002:09:00.0 on NUMA socket 0
EAL:   probe driver: 177d:a063 net_octeontx2
EAL: PCI device 0002:0a:00.0 on NUMA socket 0
EAL:   probe driver: 177d:a0f9 event_octeontx2
EAL: PCI device 0002:0b:00.0 on NUMA socket 0
EAL:   probe driver: 177d:a0f9 event_octeontx2
EAL: PCI device 0002:0c:00.0 on NUMA socket 0
EAL:   probe driver: 177d:a0f9 event_octeontx2
EAL: PCI device 0002:0d:00.0 on NUMA socket 0
EAL:   probe driver: 177d:a0fb mempool_octeontx2
EAL: PCI device 0002:0e:00.0 on NUMA socket 0
EAL:   probe driver: 177d:a0f9 event_octeontx2
EAL: PCI device 0002:0f:00.0 on NUMA socket 0
EAL:   probe driver: 177d:a0fb mempool_octeontx2
LPM or EM none selected, default LPM on

Skipping disabled port 0

Skipping disabled port 1
Initializing port 2 ... Creating queues: nb_rxq=1 nb_txq=4...  Address:00:0F:B7:06:0C:95, Destination:02:00:00:00:00:02, Allocated mbuf pool on socket 0
LPM: Adding route 192.18.2.0 / 24 (2)
LPM: Adding route 192.18.3.0 / 24 (3)
LPM: Adding route 192.18.4.0 / 24 (4)
LPM: Adding route 192.18.5.0 / 24 (5)
LPM: Adding route 2001:200:0:0:2:: / 48 (2)
LPM: Adding route 2001:200:0:0:3:: / 48 (3)
LPM: Adding route 2001:200:0:0:4:: / 48 (4)
LPM: Adding route 2001:200:0:0:5:: / 48 (5)
txq=20,0,0 txq=21,1,0 txq=22,2,0 txq=23,3,0
Initializing port 3 ... Creating queues: nb_rxq=1 nb_txq=4...  Address:00:0F:B7:06:0C:96, Destination:02:00:00:00:00:03, txq=20,0,0 txq=21,1,0 txq=22,2,0 txq=23,3,0
Initializing port 4 ... Creating queues: nb_rxq=1 nb_txq=4...  Address:00:0F:B7:06:0C:97, Destination:02:00:00:00:00:04, txq=20,0,0 txq=21,1,0 txq=22,2,0 txq=23,3,0
Initializing port 5 ... Creating queues: nb_rxq=1 nb_txq=4...  Address:00:0F:B7:06:0C:98, Destination:02:00:00:00:00:05, txq=20,0,0 txq=21,1,0 txq=22,2,0 txq=23,3,0

Initializing rx queues on lcore 20 ... rxq=2,0,0
Initializing rx queues on lcore 21 ... rxq=3,0,0
Initializing rx queues on lcore 22 ... rxq=4,0,0
Initializing rx queues on lcore 23 ... rxq=5,0,0


Checking link statusdone
Port2 Link Up. Speed 10000 Mbps -full-duplex
Port3 Link Up. Speed 10000 Mbps -full-duplex
Port4 Link Up. Speed 10000 Mbps -full-duplex
Port5 Link Up. Speed 10000 Mbps -full-duplex
L3FWD: entering main loop on lcore 21
L3FWD:  -- lcoreid=21 portid=3 rxqueueid=0
L3FWD: entering main loop on lcore 23
L3FWD:  -- lcoreid=23 portid=5 rxqueueid=0
L3FWD: entering main loop on lcore 20
L3FWD:  -- lcoreid=20 portid=2 rxqueueid=0
L3FWD: entering main loop on lcore 22
L3FWD:  -- lcoreid=22 portid=4 rxqueueid=0


cn96xx-crb

 dpdk-l2fwd -c 0xf -n 4 -- -q 1 -p 3c -T 1

ox3c gets me ports 2,3,4,5

Ports on the board:


 /*   output of dpdk-devbind -s for crb96xx
  7 0002:02:00.0 'Device a063' if=eth0 drv=octeontx2-nicpf unused=vfio-pci
  8 0002:03:00.0 'Device a063' if=eth1 drv=octeontx2-nicpf unused=vfio-pci
  9 0002:04:00.0 'Device a063' if=eth2 drv=octeontx2-nicpf unused=vfio-pci
 10 0002:05:00.0 'Device a063' if=eth3 drv=octeontx2-nicpf unused=vfio-pci
 11 0002:06:00.0 'Device a063' if=eth4 drv=octeontx2-nicpf unused=vfio-pci
 12 0002:07:00.0 'Device a063' if=eth5 drv=octeontx2-nicpf unused=vfio-pci
 13 0002:08:00.0 'Device a063' if=eth6 drv=octeontx2-nicpf unused=vfio-pci
 14 0002:09:00.0 'Device a063' if=eth7 drv=octeontx2-nicpf unused=vfio-pci


   7  5  3
 0 6  4  2  1



./l3fwd -c 0xf00000 -w 0002.04.00.0  -w 0002.05.00.0  -w 0002.06.00.0  -w 0002.07.00.0,scalar_enable=1   -n 4 -- -P -p 0x3c --config="(2, 0, 20),(3, 0,21),(4, 0,22),(5, 0,23)"

./l3fwd -c 0x700000 -w 0002:04:00.0 -w 0002:06:00.0 -w 0002:07:00.0 -n 4 -- -P -L -p 0x07 --config="(0,0,20),(1,0,21),(2,0,22)"

./l3fwd -c 0x700000 -w 0002:04:00.0,scalar_enable=1  -w 0002:06:00.0 -w 0002:07:00.0 -n 4 -- -P -L -p 0x07 --config="(0,0,20),(1,0,21),(2,0,22)"






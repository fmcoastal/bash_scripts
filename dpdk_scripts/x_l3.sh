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



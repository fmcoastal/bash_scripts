#!/bin/bash

/home/misc/dpdk-l3fwd  -c 0x800000 -n 4 -- -p 0x3 --config="(0, 0, 23),(1, 0, 23)"


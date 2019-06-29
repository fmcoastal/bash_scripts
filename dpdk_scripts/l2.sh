#!/bin/bash

# Assume dpdk-l2fwd is in $PATH

dpdk-l2fwd -c 0x8 -n 4 -- -q 1 -p 1 -T 1

#
#   Run l2fwd

#	> ./l2fwd -c 0x8 -n 4 -- -q 1 -p 1 -T 1

#   https://dpdk.org/doc/guides/testpmd_app_ug/run_app.html 

# 	-c coremask
#       -n number of memory channels 
#       -q number of queues
#       -p port mask
#	-T time period for updating status

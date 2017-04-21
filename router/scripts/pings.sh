#!/bin/bash

host0net3="192.168.3.8" # adapter 2
host0net0="192.168.0.1" # a1

host1net0="192.168.0.2" # a1
host1net1="192.168.1.3" # a2

host2net1="192.168.1.4" # a2
host2net2="192.168.2.5" # a1

host3net2="192.168.2.6" # a1
host3net3="192.168.3.7" # a2

if [ $1 = 0 ]; then
	a1_ip=$host1net0
	a2_ip=$host3net3
fi

if [ $1 = 1 ]; then
	a1_ip=$host0net0
	a2_ip=$host2net1
fi

if [ $1 = 2 ]; then
	a1_ip=$host1net1
	a2_ip=$host3net2
fi

if [ $1 = 3 ]; then
	a1_ip=$host2net2
	a2_ip=$host0gnet3
fi

ping $a1_ip -c1
echo "#####"
echo "#####"
ping $a2_ip -c1
#!/bin/bash

interface1="enp0s3"
interface2="enp0s8"

host0net3="192.168.3.8/24" # adapter 2
host0net0="192.168.0.1/24" # a1

host1net0="192.168.0.2/24" # a1
host1net1="192.168.1.3/24" # a2

host2net1="192.168.1.4/24" # a2
host2net2="192.168.2.5/24" # a1

host3net2="192.168.2.6/24" # a1
host3net3="192.168.3.7/24" # a2

if [ $1 = 0 ]; then
	a1_ip=$host0net0
	a2_ip=$host0net3
fi

if [ $1 = 1 ]; then
	a1_ip=$host1net0
	a2_ip=$host1net1
fi

if [ $1 = 2 ]; then
	a1_ip=$host2net2
	a2_ip=$host2net1
fi

if [ $1 = 3 ]; then
	a1_ip=$host3net2
	a2_ip=$host3net3
fi

sudo ip addr flush dev $interface1
sudo ip addr flush dev $interface2

sudo ip addr add $a1_ip dev $interface1
sudo ip addr add $a2_ip dev $interface2 

sudo ip link set up dev $interface1
sudo ip link set up dev $interface2
#echo $i1 $i2 "set" $1

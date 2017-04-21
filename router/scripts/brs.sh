#!/bin/bash

# check for privileg es 
if [ [ $EUID -ne 0 ] ]; then
	echo $'\033[1;31mRun as root\033[0m';
	exit 1;
fi

if [ "$1" == "up" ]; then
	for i in $(seq 0 $(($2 - 1)) ); do
		echo "setting br$i";
		ip link add name br$i type bridge;
		ip link set up dev br$i;
	done
fi

if [ $1 == "down" ]; then
	for i in $(seq 0 $(($2 - 1)) ); do
		echo "deleting br$i";
		ip link del dev br$i;
	done
fi
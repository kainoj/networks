#!/bin/bash

sudo ip link add name br0 type bridge;
sudo ip link set up dev br0;
sudo ip link add name br1 type bridge;
sudo ip link set up dev br1
sudo ip link add name br2 type bridge;
sudo ip link set up dev br2
sudo ip link add name br3 type bridge;
sudo ip link set up dev br3
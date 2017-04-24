#Konfiguracja

VirtualBox 5.1 + Ubuntu Server 16.10


Config of VmX (x = 0,1,2,3)
name: srvrX
hostname: ubuntuX
login: przms
pw: dupa


Shared Folders
Devices → Insert Guest Additions ...

https://www.htpcbeginner.com/mount-virtualbox-shared-folder-on-ubuntu-linux/


#Interfejsy
sudo ip link add name br0 type bridge
sudo ip link set up dev br0

ip link
ip addr



#Notatki
ip link
ip addr
ethtool interfejs

sudo ip addr add adres_ip/maska dev interfejs
sudo ip link set up dev interfejs


Inne:
> bind error: address already in use
$ jobs
$ fg %1
ctrl+c
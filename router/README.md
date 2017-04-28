#Co jest ok?
Wszystko z wyjątkiem obsługiwania nieskończonych odległości...

#Konfiguracja
VirtualBox 5.1 + Ubuntu Server 16.10


#Notatki
ip link
ip addr

sudo ip addr add adres_ip/maska dev interfejs
sudo ip link set up dev interfejs

sudo ip link add name br0 type bridge
sudo ip link set up dev br0

Inne:
> bind error: address already in use
$ jobs
$ fg %1
ctrl+c
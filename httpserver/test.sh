#!/bin/bash

#chmod a+rx test.sh
# ip.addr == 127.10.10.1 || ip.addr == 127.10.10.2 || ip.addr == 127.10.10.3 || ip.addr == 127.10.10.4

PORT=$(($RANDOM%5000+40000))

make && firefox --new-tab dom1.abc.pl:$PORT/index.html & ./httpserver $PORT ../www

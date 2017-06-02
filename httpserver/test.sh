#!/bin/bash

#chmod a+rx test.sh

PORT=$(($RANDOM%5000+40000))

make && firefox --new-tab dom1.abc.pl:$PORT/index.html & ./httpserver $PORT ../www

#!/bin/bash

# chmod +x transport-test.sh
echo "> Compare ./transport and tst/transport-slower"
make
echo "---------------------------------------"
/usr/bin/time -v tst/transport-slower $1 $2_mbi $3
echo "---------------------------------------"
/usr/bin/time -v ./transport $1 $2_pjo $3
echo "---------------------------------------"
diff $2_mbi $2_pjo -s
echo "---------------------------------------"
rm $2_mbi $2_pjo
make distclean

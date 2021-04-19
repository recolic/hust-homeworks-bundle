#!/bin/bash

scp main.py root@login.hpc.recolic.org:/root/ || exit $?

if [[ $1 = mini ]]; then
    echo MINI dataset:
    ssh root@login.hpc.recolic.org bash -c '"spark-submit /root/main.py hdfs://login.hpc.recolic.org:54310/prepared-totalCheckins-mini.txt 1 100"'
else
    ssh root@login.hpc.recolic.org bash -c '"spark-submit /root/main.py"'
fi

exit $?


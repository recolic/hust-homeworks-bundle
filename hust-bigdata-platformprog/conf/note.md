# note

just install hadoop+spark on all machines.

no need to modify spark conf file.

modify some minimal hadoop conf file. (refer to `conf/hadoop/*` in this repo)

modify bashrc and start.sh

install java8 and python3 on all machine, set /usr/bin/python pointing to python3.

run start.sh and start everything.

## URL notes

just some notes in my setup:

```
spark web: http://login.hpc-lan.recolic.org:8080/
spark master: spark://login.hpc-lan.recolic.org:7077
       spark://login.hpc.recolic.org:7077

hadoop ports: https://ambari.apache.org/1.2.3/installing-hadoop-using-ambari/content/reference_chap2_1.html
hadoop ResourceManager: http://login.hpc-lan.recolic.org:8088/
hadoop MapReduce JobHistory Server:  http://login.hpc-lan.recolic.org:19888
                                     ?://login.hpc-lan.recolic.org:10020

hdfs://login.hpc-lan.recolic.org:54310/...
```


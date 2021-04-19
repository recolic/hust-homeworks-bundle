eval $HADOOP_HOME/sbin/start-dfs.sh &&
eval $HADOOP_HOME/sbin/start-yarn.sh &&
eval $HADOOP_HOME/bin/mapred --daemon start historyserver &&

cd /root/spark-2.4.4-bin-hadoop2.7/ &&
./sbin/start-master.sh &&
ssh login.hpc-lan.recolic.org "bash -c 'cd spark-2.4.4-bin-hadoop2.7/ && sbin/start-slave.sh spark://login.hpc-lan.recolic.org:7077'" &&
ssh 1.hpc-lan.recolic.org "bash -c 'cd spark-2.4.4-bin-hadoop2.7/ && sbin/start-slave.sh spark://login.hpc-lan.recolic.org:7077'" &&
ssh 2.hpc-lan.recolic.org "bash -c 'cd spark-2.4.4-bin-hadoop2.7/ && sbin/start-slave.sh spark://login.hpc-lan.recolic.org:7077'"


exit $?



set -gx JAVA_HOME "/usr/lib/jvm/java-8-openjdk-amd64"
set -gx HADOOP_HOME "/root/hadoop-3.1.3"
set -gx HDFS_NAMENODE_USER "root"
set -gx HDFS_DATANODE_USER "root"
set -gx HDFS_SECONDARYNAMENODE_USER "root"
set -gx YARN_RESOURCEMANAGER_USER "root"
set -gx YARN_NODEMANAGER_USER "root"
set -gx PATH $PATH /root/hadoop-3.1.3/bin /root/spark-2.4.4-bin-hadoop2.7/bin/

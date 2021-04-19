package net.recolic.hust.bigdata.labx

import org.alitouka.spark.dbscan.spatial.Point
import org.alitouka.spark.dbscan.{Dbscan, DbscanSettings}
import org.alitouka.spark.dbscan.util.io.IOHelper
import org.apache.spark.SparkContext

object Main {
    def main(args: Array[String]): Unit = {
        val sc = new SparkContext("spark://login.hpc-lan.recolic.org:7077", "Recolic+Hust BigData Lab")
        val data = IOHelper.readDataset(sc, "hdfs://login.hpc-lan.recolic.org:54310/dataset/test.in")
        // val data = IOHelper.readDataset(sc, "hdfs://login.hpc-lan.recolic.org:54310/loc-gowalla_totalCheckins.txt")

        val clusteringSettings = new DbscanSettings ().withEpsilon(25).withNumberOfPoints(30)
        val model = Dbscan.train (data, clusteringSettings)
        IOHelper.saveClusteringResult(model, "/root/dataset/test.out")

        // gg
        val predictedClusterId = model.predict(new Point (100, 100))
        println (predictedClusterId)
    }

}

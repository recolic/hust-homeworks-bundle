name := "hust-bigdata-lab"

version := "0.1"

scalaVersion := "2.12.10"

libraryDependencies += "org.alitouka" % "spark_dbscan_2.10" % "0.0.4"
resolvers += ("Aliaksei Litouka's repository" at "http://alitouka-public.s3-website-us-east-1.amazonaws.com/").withAllowInsecureProtocol(true)

libraryDependencies += "org.apache.spark" %% "spark-sql" % "2.4.4"
// libraryDependencies += "org.apache.spark" %% "spark-mllib" % "2.1.0"

enablePlugins(JavaAppPackaging)
// maintainer := "Recolic Keghart <root@recolic.net>"
// packageSummary := "HUST bigdata exp"
// packageDescription := "HUST bigdata exp by recolic"


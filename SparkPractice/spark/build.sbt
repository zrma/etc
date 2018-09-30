name := "spark"

version := "0.1"

scalaVersion := "2.11.12"

val sparkVersion = "2.3.0"

libraryDependencies ++= Seq(
  "org.apache.spark" %% "spark-core" % sparkVersion,
  "org.apache.spark" %% "spark-sql" % sparkVersion,
  "org.apache.spark" %% "spark-hive" % sparkVersion,
  "org.apache.spark" %% "spark-streaming" % sparkVersion,
  "joda-time" % "joda-time" % "2.9.9"
)

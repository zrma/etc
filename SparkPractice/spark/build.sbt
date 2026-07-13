ThisBuild / name := "spark"
ThisBuild / version := "0.1"
ThisBuild / scalaVersion := "2.13.18"

val sparkVersion = "3.5.8"

libraryDependencies ++= Seq(
  "org.apache.spark" %% "spark-core" % sparkVersion,
  "org.apache.spark" %% "spark-sql" % sparkVersion,
  "org.apache.spark" %% "spark-hive" % sparkVersion,
  "org.apache.spark" %% "spark-streaming" % sparkVersion,
  "org.apache.spark" %% "spark-mllib" % sparkVersion,
  "org.apache.spark" %% "spark-mllib-local" % sparkVersion,
  "com.github.scopt" %% "scopt" % "3.7.1",
  "org.openkoreantext" % "open-korean-text" % "2.3.1",
  "joda-time" % "joda-time" % "2.14.2"
)

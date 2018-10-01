name := "spark"

version := "0.1"

scalaVersion := "2.11.12"

val sparkVersion = "2.3.0"

val sparkDependencyScope = "provided"

libraryDependencies ++= Seq(
  "org.apache.spark" %% "spark-core" % sparkVersion % sparkDependencyScope,
  "org.apache.spark" %% "spark-sql" % sparkVersion % sparkDependencyScope,
  "org.apache.spark" %% "spark-hive" % sparkVersion % sparkDependencyScope,
  "org.apache.spark" %% "spark-streaming" % sparkVersion % sparkDependencyScope,
  "org.apache.spark" %% "spark-mllib" % sparkVersion % sparkDependencyScope,
  "org.apache.spark" %% "spark-mllib-local" % sparkVersion % sparkDependencyScope,

  "com.github.scopt" %% "scopt" % "3.6.0",
  "joda-time" % "joda-time" % "2.9.9"
)

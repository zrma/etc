val name = "spark"
val version = "0.1"
val scalaVersion = "2.13.1"
val sparkVersion = "2.4.4"

libraryDependencies ++= Seq(
  "org.apache.spark" %% "spark-core" % sparkVersion,
  "org.apache.spark" %% "spark-sql" % sparkVersion,
  "org.apache.spark" %% "spark-hive" % sparkVersion,
  "org.apache.spark" %% "spark-streaming" % sparkVersion,
  "org.apache.spark" %% "spark-mllib" % sparkVersion,
  "org.apache.spark" %% "spark-mllib-local" % sparkVersion,
  "com.github.scopt" %% "scopt" % "3.6.0",
  "org.openkoreantext" % "open-korean-text" % "2.3.1",
  "joda-time" % "joda-time" % "2.9.9"
)

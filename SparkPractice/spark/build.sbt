val name = "spark"
val version = "0.1"
val scalaVersion = "2.12.8"
val sparkVersion = "2.4.3"
val sparkDependencyScope = "provided"

libraryDependencies ++= Seq(
  "org.apache.spark" %% "spark-core" % sparkVersion % sparkDependencyScope,
  "org.apache.spark" %% "spark-sql" % sparkVersion % sparkDependencyScope,
  "org.apache.spark" %% "spark-hive" % sparkVersion % sparkDependencyScope,
  "org.apache.spark" %% "spark-streaming" % sparkVersion % sparkDependencyScope,
  "org.apache.spark" %% "spark-mllib" % sparkVersion % sparkDependencyScope,
  "org.apache.spark" %% "spark-mllib-local" % sparkVersion % sparkDependencyScope,
  "com.github.scopt" %% "scopt" % "3.6.0",
  "com.twitter.penguin" % "korean-text" % "4.4.4",
  "joda-time" % "joda-time" % "2.9.9"
)
